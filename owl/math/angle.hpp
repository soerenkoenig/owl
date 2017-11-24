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
  
      struct degree_tag {};
      struct radian_tag {};
      struct gon_tag {};
  
      constexpr angle() = default;
  
      constexpr angle(const scalar_type& value, degree_tag)
        : value_(value * constants::pi<scalar_type> / 180)
      {
      }
  
      constexpr angle(const scalar_type& value, radian_tag)
        : value_(value)
      {
      }
  
      constexpr angle(const scalar_type& value, gon_tag)
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
