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
  
    template <typename T, std::size_t N>
    class plane
    {
    public:
    
      using vector_type = vector<T,N>;
    
      plane(const vector<T,N+1>& arr, bool auto_normalize = true)
        : data_(arr)
      {
        if(auto_normalize)
          normalize();
      }
    
      plane(const vector_type& point, const vector_type& normal, bool auto_normalize = true)
      {
        if(auto_normalize)
          normalize();
      }
    
      plane(const normal_type& normal, scalar_type distance)
      {
        auto it = std::copy(normal.begin(), normal.end(), data_.begin());
        *it = -distance;
      }
    
      const normal_type& normal() const
      {
        return reinterpret_cast<const normal_type&>(data_);
      }
    
      normal_type& normal()
      {
        return reinterpret_cast<normal_type&>(data_);
      }
    
      void normalize()
      {
        auto len = normal().length();
        if(len != 0)
          data_ /= len;
      }
    
    private:
    
      vector<T, N+1> data_;
    };
  }
}
