/* SPDX-FileCopyrightText: 2022-2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/**
 * Deferred lighting evaluation: Lighting is evaluated in a separate pass.
 *
 * Outputs shading parameter per pixel using a randomized set of BSDFs.
 * Some render-pass are written during this pass.
 */

#pragma BLENDER_REQUIRE(draw_view_lib.glsl)
#pragma BLENDER_REQUIRE(eevee_gbuffer_lib.glsl)
#pragma BLENDER_REQUIRE(common_hair_lib.glsl)
#pragma BLENDER_REQUIRE(eevee_ambient_occlusion_lib.glsl)
#pragma BLENDER_REQUIRE(eevee_surf_lib.glsl)
#pragma BLENDER_REQUIRE(eevee_nodetree_lib.glsl)
#pragma BLENDER_REQUIRE(eevee_sampling_lib.glsl)

vec4 closure_to_rgba(Closure cl)
{
  vec4 out_color;
  out_color.rgb = g_emission;
  out_color.a = saturate(1.0 - average(g_transmittance));

  /* Reset for the next closure tree. */
  float noise = utility_tx_fetch(utility_tx, gl_FragCoord.xy, UTIL_BLUE_NOISE_LAYER).r;
  float closure_rand = fract(noise + sampling_rng_1D_get(SAMPLING_CLOSURE));
  closure_weights_reset(closure_rand);

  return out_color;
}

void main()
{
  /* Clear AOVs first. In case the material renders to them. */
  clear_aovs();

  init_globals();

  float noise = utility_tx_fetch(utility_tx, gl_FragCoord.xy, UTIL_BLUE_NOISE_LAYER).r;
  float closure_rand = fract(noise + sampling_rng_1D_get(SAMPLING_CLOSURE));

  fragment_displacement();

  nodetree_surface(closure_rand);

  g_holdout = saturate(g_holdout);

  float thickness = nodetree_thickness() * thickness_mode;

  /** Transparency weight is already applied through dithering, remove it from other closures. */
  float alpha = 1.0 - average(g_transmittance);
  float alpha_rcp = safe_rcp(alpha);

  /* Object holdout. */
  eObjectInfoFlag ob_flag = eObjectInfoFlag(floatBitsToUint(drw_infos[resource_id].infos.w));
  if (flag_test(ob_flag, OBJECT_HOLDOUT)) {
    /* alpha is set from rejected pixels / dithering. */
    g_holdout = 1.0;

    /* Set alpha to 0.0 so that lighting is not computed. */
    alpha_rcp = 0.0;
  }

  g_emission *= alpha_rcp;

  ivec2 out_texel = ivec2(gl_FragCoord.xy);

  /* ----- Render Passes output ----- */

#ifdef MAT_RENDER_PASS_SUPPORT /* Needed because node_tree isn't present in test shaders. */
  /* Some render pass can be written during the gbuffer pass. Light passes are written later. */
  if (imageSize(rp_cryptomatte_img).x > 1) {
    vec4 cryptomatte_output = vec4(
        cryptomatte_object_buf[resource_id], node_tree.crypto_hash, 0.0);
    imageStoreFast(rp_cryptomatte_img, out_texel, cryptomatte_output);
  }
  output_renderpass_color(uniform_buf.render_pass.position_id, vec4(g_data.P, 1.0));
  output_renderpass_color(uniform_buf.render_pass.emission_id, vec4(g_emission, 1.0));
#endif

  /* ----- GBuffer output ----- */

  GBufferData gbuf_data;
  gbuf_data.closure[0] = g_closure_get_resolved(0, alpha_rcp);
#if CLOSURE_BIN_COUNT > 1
  gbuf_data.closure[1] = g_closure_get_resolved(1, alpha_rcp);
#endif
#if CLOSURE_BIN_COUNT > 2
  gbuf_data.closure[2] = g_closure_get_resolved(2, alpha_rcp);
#endif
  gbuf_data.surface_N = g_data.N;
  gbuf_data.thickness = thickness;
  gbuf_data.object_id = resource_id;

  GBufferWriter gbuf = gbuffer_pack(gbuf_data);

  /* Output header and first closure using frame-buffer attachment. */
  out_gbuf_header = gbuf.header;
  out_gbuf_closure1 = gbuf.data[0];
  out_gbuf_closure2 = gbuf.data[1];
  out_gbuf_normal = gbuf.N[0];

  /* Output remaining closures using image store. */
  /* NOTE: The image view start at layer 2 so all destination layer is `layer - 2`. */
  for (int layer = 2; layer < GBUFFER_DATA_MAX && layer < gbuf.data_len; layer++) {
    imageStoreFast(out_gbuf_closure_img, ivec3(out_texel, layer - 2), gbuf.data[layer]);
  }
  /* NOTE: The image view start at layer 1 so all destination layer is `layer - 1`. */
  for (int layer = 1; layer < GBUFFER_NORMAL_MAX && layer < gbuf.normal_len; layer++) {
    imageStoreFast(out_gbuf_normal_img, ivec3(out_texel, layer - 1), gbuf.N[layer].xyyy);
  }

  /* ----- Radiance output ----- */

  /* Only output emission during the gbuffer pass. */
  out_radiance = vec4(g_emission, 0.0);
  out_radiance.rgb *= 1.0 - g_holdout;
  out_radiance.a = g_holdout;
}
