//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <fstream>

#include "owl/utils/buffer.hpp"

namespace owl
{
  namespace utils
  {
  
    bool file_exists(const std::string& path);
  
    std::streamsize file_size(const std::string& path);
  
    std::string parent_path(const std::string& path);
  
    std::string file_extension(const std::string& path);
  
    bool read_file(const std::string& path, buffer& buf);
    
    bool write_file(const std::string& path, buffer& buf);
  }
}
