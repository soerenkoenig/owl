//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include "owl/optional.hpp"
#include "owl/math/matrix.hpp"
#include "owl/math/ray.hpp"

namespace owl
{
  namespace math
  {
  
    template <typename Scalar, std::size_t Dimension>
    class plane
    {
    public:
      using scalar_type = Scalar;
      using vector_type = vector<Scalar, Dimension>;
      using homogenous_vector_type = vector<Scalar, Dimension + 1>;
   
      template <typename S1>
      using enable_if_scalar_t = typename vector_type::template enable_if_scalar_t<S1>;
    
      plane() = default;
    
      plane(const vector<Scalar, Dimension + 1>& arr)
        : data_(arr)
      {
        normalize();
      }
    
      plane(const vector_type& point, const vector_type& normal)
      {
        auto it = std::copy(normal.begin(), normal.end(), data_.begin());
        *it = -dot(normal, point);
      
        normalize();
      }
    
      template<typename S, typename... Args, typename = enable_if_scalar_t<S> >
      plane(S&& nx, Args&&... args)
        : data_{std::forward<S>(nx), std::forward<Args>(args)...}
      {
        normalize();
      }
    
      const vector_type& normal() const
      {
        return reinterpret_cast<const vector_type&>(data_);
      }
    
      scalar_type distance() const
      {
        return -data_[3];
      }
    
  
    
    
      scalar_type operator()(const vector_type& vec)
      {
        return dot(normal(), vec) + data_[3];
      }
    
      scalar_type operator()(const homogenous_vector_type& hvec)
      {
        return dot(data_, hvec);
      }
    
    private:
      void normalize()
      {
        auto len = normal().length();
        if(len != 0)
          data_ /= len;
      }
    
      homogenous_vector_type data_;
    };
  
    using plane3f = plane<float,3>;
    using plane3d = plane<double,3>;
    
    template<typename T, std::size_t N>
    T distance(const plane<T,N>& pl, const vector<T,N>& pnt)
    {
      return dot(pl.normal(), pnt) - pl.distance();
    }
  
    template<typename T, std::size_t N>
    std::optional<T> intersect(const ray<T,N> r, const plane<T,N>& pl)
    {
      T denom = dot( pl.normal(), r.direction());
      if( denom == 0)
        return std::nullopt;
    
      T t = distance(pl, r.origin) / denom;
      if (t < 0)
        return std::nullopt;
      return t;
    }
  }
}
