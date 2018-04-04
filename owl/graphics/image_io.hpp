//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include "owl/graphics/image.hpp"

namespace owl
{
  namespace graphics
  {
    bool write_ppm(const rgb8u_image& img, const std::string& path);
    bool write_jpg(const rgb8u_image& img, const std::string& path, int quality = 96);
    bool write_bmp(const rgb8u_image& img, const std::string& path);
    bool write_png(const rgb8u_image& img, const std::string& path);
  
    bool read_image(rgb8u_image& img, const std::string& path);
  }
}
