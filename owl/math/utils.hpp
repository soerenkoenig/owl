//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <type_traits>

namespace owl
{
  namespace math
  {
    template <typename Scalar>
    constexpr Scalar sqr(Scalar s)
    {
      return s * s;
    }
  }
}


