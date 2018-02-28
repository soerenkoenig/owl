//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <memory>

#include "owl/scene/view.hpp"

namespace owl
{
  namespace render
  {
      class raytracer
      {
      public:
        template <typename Color, typename Scalar>
        void render(std::shared_ptr<scene::view<Color, Scalar>> view)
        {
        
        }
      };
  
  }
}


