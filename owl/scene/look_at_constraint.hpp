//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include "owl/scene/node.hpp"
#include "owl/math/trafos.hpp"

namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class look_at_constraint
    {
    public:
    
      look_at_constraint(node<Scalar>& target)
        : target_(&target)
      {
      }
    
      void operator()(node<Scalar>& n)
      {
        math::vector3<Scalar> center = target_->convert_position(math::vector<Scalar,3>::zero(),n.parent());
        math::vector3<Scalar> eye = n.convert_position(math::vector<Scalar,3>::zero(),n.parent());
        math::vector3<Scalar> up = n.convert_direction(math::vector<Scalar,3>::identity_y(), n.parent());
        n.orientation = math::lookat<Scalar>(eye, center, up);
      }
    
    private:
      node<Scalar>* target_;
   
    };
  
  }
}
