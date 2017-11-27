//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <utility>
#include "owl/utils/template_utils.hpp"
#include "owl/math/constants.hpp"

namespace owl
{
  namespace math
  {
    template <typename Scalar>
    class angle
    {
    public:
      using scalar_type = Scalar;
    
      template <typename S1, typename S2 = Scalar>
      using enable_if_scalar_t = std::enable_if_t<std::is_convertible<S1, S2>::value>;
  
      struct degree_tag {};
      struct radian_tag {};
      struct gon_tag {};
  
      constexpr angle() = default;
  
      template <typename S, typename = enable_if_scalar_t<S>>
      constexpr angle(const S& value, degree_tag)
        : value_(value * constants::pi<scalar_type> / 180)
      {
      }
  
      template <typename S, typename = enable_if_scalar_t<S>>
      constexpr angle(const S& value, radian_tag)
        : value_(value)
      {
      }
  
      template <typename S, typename = enable_if_scalar_t<S>>
      constexpr angle(const S& value, gon_tag)
        : value_(value * constants::pi<scalar_type> / 200)
      {
      }
    
      operator scalar_type() const
      {
        return value_;
      }
  
      scalar_type degrees() const
      {
        return scalar_type(value_ * 180 / constants::pi<scalar_type>);
      }
  
      scalar_type gons() const
      {
        return scalar_type(value_ * 200 / constants::pi<scalar_type>);
      }
  
      scalar_type radians() const
      {
        return value_;
      }
    
    private:
      scalar_type value_;
    };
  
    template<typename Scalar>
    angle<Scalar> degrees(const typename utils::identity<Scalar>::type& value)
    {
      return angle<Scalar>(value, typename angle<Scalar>::degree_tag());
    }
  
    template<typename Scalar>
    angle<Scalar> radians(const typename utils::identity<Scalar>::type& value)
    {
      return angle<Scalar>(value, typename angle<Scalar>::radian_tag());
    }
  
    template<typename Scalar>
    angle<Scalar> gons(const typename utils::identity<Scalar>::type& value)
    {
      return angle<Scalar>(value, typename angle<Scalar>::gon_tag());
    }
  
    template <typename Scalar>
    bool is_acute(const angle<Scalar>& a)
    {
      return a < degrees<Scalar>(90);
    }
  
    template <typename Scalar>
    bool is_obtuse(const angle<Scalar>& a)
    {
      return a > degrees<Scalar>(90) && a < degrees<Scalar>(180);
    }
  
    template <typename Scalar>
    bool is_reflex(const angle<Scalar>& a)
    {
      return a > degrees<Scalar>(180) && a < degrees<Scalar>(360);
    }
  }
}
