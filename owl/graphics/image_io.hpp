//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "owl/graphics/image.hpp"

namespace owl
{
  namespace graphics
  {
    inline bool write_ppm(rgb8_image& img, const boost::filesystem::path& p)
    {
      boost::ofstream ofs;
      ofs.open(p);
      if(!ofs.is_open)
        return false;
    
      ofs << "P6\n" << img.width() << " " << img.height() << "\n255\n";
      ofs.write(img.data(), img.width() * img.height() * 3);
      return true;
    }
  }
}
