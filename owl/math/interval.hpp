
//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#pragma once
#include "owl/math/matrix.hpp"

namespace owl
{
  namespace math
  {
    namespace detail
    {
      
      template <typename Scalar, std::size_t Dimension>
      struct interval_helper
      {
        using scalar_type = Scalar;
        using bound_type = vector<Scalar, Dimension>;
        
        static constexpr bound_type max()
        {
          return bound_type::max();
        }
        
        static constexpr bound_type lowest()
        {
          return bound_type::lowest();
        }
        
        static bound_type minimum(const bound_type& a, const bound_type& b)
        {
          bound_type bmin;
          for(std::size_t i = 0; i < Dimension; ++i)
            bmin(i) = std::min(a(i), b(i));
          return bmin;
        }
        
        static bound_type maximum(const bound_type& a, const bound_type& b)
        {
          bound_type bmin;
          for(std::size_t i = 0; i < Dimension; ++i)
            bmin(i) = std::max(a(i), b(i));
          return bmin;
        }
        
      };
      
      template <typename Scalar>
      struct interval_helper<Scalar, 1>
      {
        using scalar_type = Scalar;
        using bound_type = Scalar;
        
        static constexpr bound_type max()
        {
          return std::numeric_limits<bound_type>::max();
        }
        
        static constexpr bound_type lowest()
        {
          return std::numeric_limits<bound_type>::lowest();
        }
        
        static bound_type minimum(const bound_type& a, const bound_type& b)
        {
          return std::min(a, b);
        }
        
        static bound_type maximum(const bound_type& a, const bound_type& b)
        {
          return std::max(a, b);
        }
      };
      
    }
    template <typename Scalar, std::size_t Dimension = 1>
    class interval
    {
      using helper_type_ = typename detail::interval_helper<Scalar,Dimension>;
      
    public:
      using scalar_type = Scalar;
      using bound_type = typename helper_type_::bound_type;
      
      interval()
       : bounds{helper_type_::max(), helper_type_::lowest()}
      {
      }
      
      interval(const bound_type& b)
        : bounds{b, b}
      {
      }
      
      interval(const bound_type& lo, const bound_type& hi)
        : bounds{lo, hi}
      {
      }
      
      bool operator==(const interval& other) const
      {
        return bounds == other.bounds;
      }
      
      bool operator!=(const interval& other) const
      {
        return bounds != other.bounds;
      }
      
      bool inside(const bound_type& p) const
      {
        return lower_bound <= p && upper_bound > p;
      }
      
      bool inside(const interval& other) const
      {
        return inside(other.lower_bound) && inside(other.upper_bound);
      }
      
      void insert(const bound_type& p)
      {
        lower_bound = helper_type_::minimum(lower_bound, p);
        upper_bound = helper_type_::maximum(upper_bound, p);
      }
    
      union
      {
        std::array<bound_type, 2> bounds;
        struct
        {
          bound_type lower_bound;
          bound_type upper_bound;
        };
      };
    };
    
    template <typename Scalar>
    using rectangle = interval<Scalar, 2>;
    
    template <typename Scalar>
    using box = interval<Scalar, 3>;
  }
}

