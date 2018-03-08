//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include <chrono>

namespace owl
{
  namespace scene
  {
    enum class light_type
    {
      ambient, directional, spot, point
    };
  
    template<typename Scalar, typename Color>
    class light
    {
    public:
      light_type type;
      Scalar intensity;
      Scalar temperature;
      Color color;
    
    
    
    
    };
  }
}


