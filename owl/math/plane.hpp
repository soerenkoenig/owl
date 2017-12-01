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
  
    template <typename T, std::size_t N>
    class plane
    {
    public:
      using scalar_type = T;
      using vector_type = vector<T,N>;
      using homogenous_vector_type = vector<T,N>;
    
      plane() = default;
    
      plane(const vector<T,N+1>& arr, bool auto_normalize = true)
        : data_(arr)
      {
        if(auto_normalize)
          normalize();
      }
    
      plane(const vector_type& point, const vector_type& normal, bool auto_normalize = true)
      {
        auto it = std::copy(normal.begin(), normal.end(), data_.begin());
        *it = -dot(normal, point);
        if(auto_normalize)
          normalize();
      }
    
      plane(const vector_type& normal, scalar_type distance)
      {
        auto it = std::copy(normal.begin(), normal.end(), data_.begin());
        *it = -distance;
      }
    
      const vector_type& normal() const
      {
        return reinterpret_cast<const vector_type&>(data_);
      }
    
      vector_type& normal()
      {
        return reinterpret_cast<vector_type&>(data_);
      }
    
      scalar_type distance() const
      {
        return -data_[3];
      }
    
      void set_distance(const scalar_type& dist)
      {
        return data_[3] = -dist;
      }
    
      void normalize()
      {
        auto len = normal().length();
        if(len != 0)
          data_ /= len;
      }
    
    private:
    
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
    
      T t =  dot( pl.normal(), r.origin) - pl.distance() / denom;
      if (t < 0)
        return std::nullopt;
      return t;
    }
  }
}
