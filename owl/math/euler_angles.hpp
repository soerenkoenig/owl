//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/math/matrix.hpp"
#include "owl/math/angle.hpp"
#include "owl/math/utils.hpp"

namespace owl
{
  namespace math
  {
  
    template<typename Scalar>
    class euler_angles
    {
    public:
    
      euler_angles() = default;
    
      euler_angles(const angle<Scalar>& pitch, const angle<Scalar>& yaw, const angle<Scalar>& roll)
        : pitch(pitch), yaw(yaw), roll(roll)
      {
      }
    
      euler_angles(const square_matrix<Scalar,3>& R)
      {
        pitch = radians<Scalar>(atan2(-R(1, 2), R(2, 2)));
        Scalar c2 = sqrt(sqr(R(0, 0)) + sqr(R(0, 1)));
        yaw = radians<Scalar>(atan2(R(0, 2), c2));
        Scalar s1 = sin(pitch);
        Scalar c1 = cos(pitch);
        roll = radians<Scalar>(atan2(s1 * R(2, 0) + c1 * R(1, 0), c1 * R(1, 1) + s1 * R(2, 1)));
      }
    
      operator square_matrix<Scalar,3>() const
      {
        Scalar c1 = cos(pitch);
        Scalar s1 = sin(pitch);
        Scalar c2 = cos(yaw);
        Scalar s2 = sin(yaw);
        Scalar c3 = cos(roll);
        Scalar s3 = sin(roll);
    
        square_matrix<Scalar,3> m;
        m <<                c2 * c3,               -c2 * s3,       s2,
             s1 * s2 * c3 + c1 * s3, c1 * c3 - s1 * s2 * s3, -s1 * c2,
             s1 * s3 - c1 * c3 * s2, c1 * s2 * s3 + s1 * c3,  c1 * c2;
        return m;
      }
    
      operator square_matrix<Scalar,4>() const
      {
        Scalar c1 = cos(pitch);
        Scalar s1 = sin(pitch);
        Scalar c2 = cos(yaw);
        Scalar s2 = sin(yaw);
        Scalar c3 = cos(roll);
        Scalar s3 = sin(roll);
    
        square_matrix<Scalar,4> m;
        m <<                c2 * c3,               -c2 * s3,       s2, 0,
             s1 * s2 * c3 + c1 * s3, c1 * c3 - s1 * s2 * s3, -s1 * c2, 0,
             s1 * s3 - c1 * c3 * s2, c1 * s2 * s3 + s1 * c3,  c1 * c2, 0,
                                  0,                      0,        0, 1;
        return m;
      }
    
      angle<Scalar> pitch; //X
      angle<Scalar> yaw; //Y
      angle<Scalar> roll; //Z
    };
  
  }
}

