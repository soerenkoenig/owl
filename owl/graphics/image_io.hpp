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
    inline bool write_ppm(rgb8_image& img, const std::string& p)
    {
      std::ofstream ofs;
      ofs.open(p);
      if(!ofs.is_open)
        return false;
    
      ofs << "P6\n" << img.width() << " " << img.height() << "\n255\n";
      ofs.write(img.data(), img.width() * img.height() * 3);
      return true;
    }
  }
}
