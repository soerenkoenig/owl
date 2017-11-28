#pragma once
#include "owl/math/matrix.hpp"

namespace owl
{
  namespace math
  {
    template<typename Scalar, std::size_t N>
    class ray
    {
    public:
      using scalar_type = Scalar;
      using vector_type = vector<Scalar,N>;
      
      ray() {}
      
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
    
    using ray3f = ray<float,3>;
    using ray3d = ray<double,3>;
    using ray2f = ray<float,2>;
    using ray2d = ray<double,2>;
  }
}
