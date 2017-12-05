
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
        
        static bound_type prev(const bound_type& p)
        {
          bound_type p_prev;
          for(std::size_t i = 0; i < Dimension; ++i)
            p_prev(i) = interval_helper<Scalar,1>::prev(p(i));
          return p_prev;
        }
        
        static bound_type next(const bound_type& p)
        {
          bound_type p_next;
          for(std::size_t i = 0; i < Dimension; ++i)
            p_next(i) = interval_helper<Scalar,1>::next(p(i));
          return p_next;
        }
        
        static bound_type minimum(const bound_type& a, const bound_type& b)
        {
          bound_type bmin;
          for(std::size_t i = 0; i < Dimension; ++i)
            bmin(i) = interval_helper<Scalar,1>::minimum(a(i), b(i));
          return bmin;
        }
        
        static bound_type maximum(const bound_type& a, const bound_type& b)
        {
          bound_type bmax;
          for(std::size_t i = 0; i < Dimension; ++i)
            bmax(i) = interval_helper<Scalar,1>::maximum(a(i), b(i));
          return bmax;
        }
        
        template<bool LowerBoundOpen, bool UpperBoundOpen>
        static bool inside(const bound_type& lo, const bound_type& hi, const bound_type& p)
        {
          for(std::size_t i = 0; i < Dimension; ++i)
              if(!interval_helper<Scalar,1>::template inside<LowerBoundOpen, UpperBoundOpen>(lo(i), hi(i), p(i)))
                return false;
          return true;
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
        
        static bound_type next(const bound_type& p)
        {
          if constexpr(std::is_floating_point_v<bound_type>)
            return std::nextafter(p,max());
          if constexpr(std::is_integral_v<bound_type>)
            return p == max() ? p : ++p;
        }
        
        static bound_type prev(const bound_type& p)
        {
          if constexpr(std::is_floating_point_v<bound_type>)
            return std::nextafter(p, lowest());
          if constexpr(std::is_integral_v<bound_type>)
            return p == lowest() ? p : --p;
        }
        
        template<bool LowerBoundOpen, bool UpperBoundOpen>
        static bool inside(const bound_type& lo, const bound_type& hi, const bound_type& p)
        {
          if constexpr(LowerBoundOpen)
          {
           if(p <= lo)
            return false;
          }
          else
          {
            if(p < lo)
              return false;
          }
          if constexpr(UpperBoundOpen)
          {
            if(p >= hi)
              return false;
          }
          else
          {
            if(p > hi)
              return false;
          }
          return true;
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
    template <typename Scalar, std::size_t Dimension = 1, bool LowerBoundOpen = false, bool UpperBoundOpen = true>
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
      
      void clear()
      {
        *this = interval();
      }
      
      bool overlaps(const interval& other) const
      {
        return is_inside(other.lower_bound) || is_inside(other.upper_bound);
      }
      
      bool inside(const bound_type& p) const
      {
        return helper_type_::template inside<LowerBoundOpen,UpperBoundOpen>(lower_bound, upper_bound, p);
      }
      
      bool inside(const interval& other) const
      {
        return inside(other.lower_bound) && inside(other.upper_bound);
      }
      
      
      //ensures p is inside the interval
      void insert(const bound_type& p)
      {
        if constexpr(LowerBoundOpen)
          lower_bound = helper_type_::minimum(lower_bound, helper_type_::prev(p));
        else
          lower_bound = helper_type_::minimum(lower_bound, p);
          
        if constexpr(UpperBoundOpen)
          upper_bound = helper_type_::maximum(upper_bound, helper_type_::next(p));
        else
          upper_bound = helper_type_::maximum(upper_bound, p);
      }
      
      bool operator==(const interval& other) const
      {
        return bounds == other.bounds;
      }
      
      bool operator!=(const interval& other) const
      {
        return bounds != other.bounds;
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

