
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
#include "owl/math/interval.hpp"


namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class grid : public geometry<Scalar>
    {
    public:
    
      grid(int umin = -10, int vmin = 10, int umax = -10, int vmax = 10,
        std::size_t subdivs = 5, const math::vector<Scalar,3>& u_dir = math::vector<Scalar, 3>::identity_x(), const math::vector<Scalar,3>& v_dir = math::vector<Scalar, 3>::identity_y())
        : rect{math::vector<int,2>(umin, vmin), math::vector<int,2>(umax, vmax)}
        , u_direction{u_dir}
        , v_direction{v_dir}
        , subdivision{subdivs}
      {
      }
    
    
      math::vector<Scalar,3> position(Scalar u, Scalar v) const
      {
        return u * u_direction + v * v_direction;
      }
    
      math::vector<Scalar,3> normal() const
      {
        return cross(u_direction, v_direction);
      }
    
    private:
      math::rectangle<int> rect;
      math::vector<Scalar,3> u_direction;
      math::vector<Scalar,3> v_direction;
      std::size_t subdivision = 5;
    
    };
  }
}
