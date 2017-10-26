//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <vector>

#define STBI_NO_STDIO

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_INLINE
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#define STB_IMAGE_RESIZE_INLINE
#include "stb/stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_INLINE
#include "stb/stb_image_write.h"

namespace owl
{
  namespace graphics
  {
    template<typename Pixel>
    class image
    {
    public:
      using pixel_type = Pixel;
    
    
    
    private:
      std::size_t width_ = 0;
      std::size_t height_ = 0;
      std::size_t channels_ = 1;
      std::vector<Pixel>  data_;
    };
  }
}

