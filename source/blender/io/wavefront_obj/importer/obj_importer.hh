/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup obj
 */

#pragma once

#include "IO_wavefront_obj.hh"

namespace blender::io::obj {

void importer_geometry(const OBJImportParams &import_params,
                       Vector<bke::GeometrySet> &geometries,
                       size_t read_buffer_size = 256 * 1024);

/* Main import function used from within Blender. */
void importer_main(bContext *C, const OBJImportParams &import_params);

/* Used from tests, where full bContext does not exist. */
void importer_main(Main *bmain,
                   Scene *scene,
                   ViewLayer *view_layer,
                   const OBJImportParams &import_params,
                   size_t read_buffer_size = 256 * 1024);

}  // namespace blender::io::obj
