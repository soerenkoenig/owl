//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <type_traits>

#include "owl/utils/container_utils.hpp"

namespace owl
{
  namespace math
  {
    namespace detail
    {
      inline bool compare_margin(double lhs, double rhs, double margin)
      {
        return (lhs + margin >= rhs) && (rhs + margin >= lhs);
      }
    }
  
    inline bool compare_equal(double lhs, double rhs, double margin, double epsilon, double scale)
    {
      return detail::compare_margin(lhs, rhs, margin) ||
        detail::compare_margin(lhs, rhs, epsilon * (scale + std::fabs(lhs)));
    }
  
    template <typename Container, typename = std::enable_if_t<owl::utils::is_container<Container>::value> >
    bool compare_equal(const Container& lhs, const Container& rhs, double margin, double epsilon, double scale)
    {
      return std::equal(lhs.begin(),lhs.end(),rhs.begin(),
        [&](const double& l, const double& r)
        {
          return compare_equal(l, r, margin, epsilon, scale);
        });
    }
 
    template <typename T>
    class approximately
    {
    public:
        explicit approximately(T value)
          : epsilon_(std::numeric_limits<float>::epsilon() * 100 )
          , margin_(0.0)
          , scale_(0.0)
          , value_(value)
        {}
    
        static approximately custom()
        {
          return approximately(0);
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        approximately operator()(const T2& value)
        {
            approximately approximately(static_cast<T>(value));
            approximately.epsilon(epsilon_);
            approximately.margin(margin_);
            approximately.scale(scale_);
            return approximately;
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        explicit approximately(const T2& value)
          : approximately(static_cast<T>(value))
        {
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator==(const T2& lhs, const approximately& rhs)
        {
          auto lhs_v = static_cast<T>(lhs);
          auto rhs_v = rhs.value_;
          return compare_equal(rhs_v, lhs_v, rhs.margin_, rhs.epsilon_ ,rhs.scale_);
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator==(const approximately& lhs, const T2& rhs)
        {
          return operator==(rhs, lhs);
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator!=(const T2& lhs, const approximately& rhs)
        {
          return !operator==(lhs, rhs);
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator!=(approximately const& lhs, const T2& rhs)
        {
          return !operator==(rhs, lhs);
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator<=(const T2& lhs, const approximately& rhs)
        {
          return static_cast<double>(lhs) < rhs.value_ || lhs == rhs;
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator<=(const approximately& lhs, const T2& rhs)
        {
          return lhs.value_ < static_cast<T>(rhs) || lhs == rhs;
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator>=(const T2& lhs, const approximately& rhs)
        {
          return static_cast<T>(lhs) > rhs.value_ || lhs == rhs;
        }

        template <typename T2, typename = typename std::enable_if<std::is_constructible<T, T2>::value>::type>
        friend bool operator>=(const approximately& lhs, const T2& rhs)
        {
          return lhs.value_ > static_cast<T>(rhs) || lhs == rhs;
        }

        template <typename Scalar,
          typename = typename std::enable_if<std::is_constructible<double, Scalar>::value>::type>
        approximately& epsilon(const Scalar& newEpsilon)
        {
          double epsilonAsDouble = static_cast<double>(newEpsilon);
          if(epsilonAsDouble < 0 || epsilonAsDouble > 1.0)
          {
            throw std::domain_error("Invalid parameter, epsilon has to be between 0 and 1" );
          }
          epsilon_ = epsilonAsDouble;
          return *this;
        }

        template <typename Scalar,
          typename = typename std::enable_if<std::is_constructible<double, Scalar>::value>::type>
        approximately& margin(const Scalar& newMargin)
        {
          double marginAsDouble = static_cast<double>(newMargin);
          if(marginAsDouble < 0)
          {
            throw std::domain_error("Invalid parameter, margin has to be non-negative." );
          }
          margin_ = marginAsDouble;
          return *this;
        }

        template <typename Scalar,
          typename = typename std::enable_if<std::is_constructible<double, Scalar>::value>::type>
        approximately& scale(const Scalar& newScale)
        {
            scale_ = static_cast<double>(newScale);
            return *this;
        }
    
        const T& value() const { return value_; }
    
     private:
        double epsilon_;
        double margin_;
        double scale_;
        T value_;
    };
  
    template <typename T>
    auto approx(T&& val)
    {
     return approximately<std::decay_t<T>>(std::forward<T>(val));
    }
  
    template <typename T>
    std::ostream& operator<<(std::ostream& out, const approximately<T>& a)
    {
        return out << a.value();
    }
  
  }
}



