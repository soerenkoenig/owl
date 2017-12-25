//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/export.hpp"

namespace owl
{
  namespace utils
  {
    template<typename ForwardIterator, typename T>
    void lin_space(ForwardIterator first, ForwardIterator last, T first_val, T last_val)
    {
      auto N = std::distance(first,last);
      if(N == 1)
      {
        *first = last_val;
        return ;
      }
      auto diff = last_val - first_val;

      for(std::size_t i = 0; i < N; i++)
      {
        *first++ = first_val + i * diff / (static_cast<T>(N) - static_cast<T>(1));
      }
    }
  }
}


