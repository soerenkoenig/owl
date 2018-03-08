
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
        std::size_t subdivs = 5, Scalar grid_spacing = 1, const math::vector<Scalar,3>& u_dir = math::vector<Scalar, 3>::identity_x(), const math::vector<Scalar,3>& v_dir = math::vector<Scalar, 3>::identity_y())
        : rect{math::vector<int,2>(umin, vmin), math::vector<int,2>(umax, vmax)}
        , u_direction_{u_dir}
        , v_direction_{v_dir}
        , subdivision_{subdivs}
      {
      }
    
      
    
      math::vector<Scalar,3> position(Scalar u, Scalar v) const
      {
        return grid_spacing_ * (u * u_direction_ + v * v_direction_);
      }
    
      math::vector<Scalar,3> normal() const
      {
        return normalize(cross(u_direction_, v_direction_));
      }
    
    private:
      math::rectangle<int> rect;
      math::vector<Scalar,3> u_direction_;
      math::vector<Scalar,3> v_direction_;
      Scalar grid_spacing_ = 1;
      std::size_t subdivision_ = 5;
    
    };
  }
}
