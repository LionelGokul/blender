/* SPDX-FileCopyrightText: 2011 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "COM_MultiThreadedOperation.h"
#include "DNA_movieclip_types.h"
#include "MEM_guardedalloc.h"

#include "BKE_tracking.h"

namespace blender::compositor {

class MovieDistortionOperation : public MultiThreadedOperation {
 private:
  MovieClip *movie_clip_;
  int margin_[2];

 protected:
  bool apply_;
  int framenumber_;

  struct MovieDistortion *distortion_;
  int calibration_width_, calibration_height_;
  float pixel_aspect_;

 public:
  MovieDistortionOperation(bool distortion);

  void init_data() override;
  void init_execution() override;
  void deinit_execution() override;

  void set_movie_clip(MovieClip *clip)
  {
    movie_clip_ = clip;
  }
  void set_framenumber(int framenumber)
  {
    framenumber_ = framenumber;
  }

  void get_area_of_interest(int input_idx, const rcti &output_area, rcti &r_input_area) override;
  void update_memory_buffer_partial(MemoryBuffer *output,
                                    const rcti &area,
                                    Span<MemoryBuffer *> inputs) override;
};

}  // namespace blender::compositor
