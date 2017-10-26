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

#include "owl/utils/container_utils.hpp"

namespace owl
{
  namespace utils
  {
  
    bool file_exists(const std::string& path);
  
    std::streamsize file_size(const std::string& path);
  
    template<typename Container>
    bool read_file(const std::string& path, Container& container)
    {
      static_assert(is_continuous_container<Container>::value, "container is not continous");
      static_assert(sizeof(container_traits<Container>::value_type) == 1,  "size of value type is not 1 byte");
      static_assert(has_resize<Container>::value,  "container is not resizeable");
      std::streampos size;
      std::ifstream file(path, std::ios::binary);

      file.seekg(0, std::ios::end);
      size = file.tellg();
      file.seekg(0, std::ios::beg);
    
      container.resize(size);
      return (bool)file.read((char*) container.data(), size);
    }
  
    template<typename Container>
    bool write_file(const std::string& path, Container& container)
    {
      static_assert(is_continuous_container<Container>::value, "container is not continous");
      static_assert(sizeof(container_traits<Container>::value_type) == 1,  "size of value type is not 1 byte");
      std::ofstream file(path, std::ios::out | std::ios::binary);
      return (bool)file.write((char*) container.data(), container.size());
    }
  }
}
