
//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

namespace owl
{
  namespace utils
  {
    struct non_copyable
    {
    protected:
      non_copyable() = default;
      ~non_copyable() = default;

      non_copyable(const non_copyable&) = delete;
      non_copyable& operator=(const non_copyable&) = delete;
    };
  }
}
