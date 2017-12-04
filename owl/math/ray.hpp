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

namespace owl
{
  namespace math
  {
    template<typename Scalar, std::size_t Dimension>
    class ray
    {
    public:
      static_assert(Dimension > 1, "invalid parameter Dimension");
      
      using scalar_type = Scalar;
      using vector_type = vector<Scalar, Dimension>;
      
      ray() = default;
      
      ray(const vector_type &origin, const vector_type& direction)
        : origin(origin)
      {
        set_direction(direction);
      }
      
      void set_direction(const vector_type& direction)
      {
        direction_ = direction;
        inv_direction_ = vector_type( Scalar(1) / direction.x(), Scalar(1) / direction.y(), Scalar(1) / direction.z());
      }
      
      vector_type operator()(const scalar_type& t) const
      {
        return origin + direction_ * t;
      }
      
      const vector_type& direction() const
      {
        return direction_;
      }
      
      const vector_type& inv_direction() const
      {
        return inv_direction_;
      }
      
      vector_type origin;
      
    private:
      vector_type inv_direction_;
      vector_type direction_;
    };
    
    using ray3f = ray<float, 3>;
    using ray3d = ray<double, 3>;
    using ray2f = ray<float, 2>;
    using ray2d = ray<double, 2>;
  }
}
