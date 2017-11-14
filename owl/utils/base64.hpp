
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
#include <string>

#include "owl/utils/container_utils.hpp"

namespace owl
{
  namespace utils
  {
    std::string base64_encode(const unsigned char* buf, std::size_t bufLen);
    
    template <typename Container>
    std::string base64_encode(const Container& encoded_bytes)
    {
      static_assert(is_continuous_container<Container>::value, "container is not continous");
      static_assert(sizeof(typename container_traits<Container>::value_type) == 1, "size of value type is not 1 byte");
      return base64_encode(encoded_bytes.data(), encoded_bytes.size());
    }
  
    std::vector<unsigned char> base64_decode(const std::string& encoded_string);
  }
}
