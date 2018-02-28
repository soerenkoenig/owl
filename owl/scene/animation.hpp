//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <chrono>
#include "owl/scene/node.hpp"


namespace owl
{
  namespace scene
  {
    template <typename Scalar>
    class animation
    {
    public:
      using clock = std::chrono::steady_clock;
      using duration =  clock::duration;
      using time_point = clock::time_point;
    
      virtual void animate(time_point current_time, duration delta_t, node<Scalar& n)
      {
      }
    };
  }
}

