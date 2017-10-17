//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <cassert>

namespace owl
{
  namespace utils
  {
    //column major first dimension is continous
    template <std::size_t N0>
    constexpr std::size_t linear_index( std::size_t n0)
    {
      assert(n0 < N0);
      return n0;
    }
  
    //column major first dimension is continous
    template <std::size_t N0, std::size_t... Ns, typename... Indices >
    constexpr std::size_t linear_index( std::size_t n0, Indices... ns)
    {
      assert(n0 < N0);
      return n0 + N0 * linear_index<Ns...>(ns...);
    }
  }
}
