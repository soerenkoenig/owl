//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include "owl/scene/geometry.hpp"
#include "owl/math/mesh.hpp"

namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class mesh : public geometry<Scalar>
    {
    public:
      mesh(const math::mesh<Scalar>& m)
        : mesh_(m)
        , bounds_(m.bounds())
      {
      
      }
    
      math::box<Scalar> bounds() const
      {
        return bounds_;
      }
    
      
    private:
      math::mesh<Scalar> mesh_;
      math::box<Scalar> bounds_;
    };
  }
}
