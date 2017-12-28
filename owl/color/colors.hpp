//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <cstdint>
#include <algorithm>
#include <array>
#include "owl/math/matrix.hpp"
#include "owl/optional.hpp"
#include "owl/color/channel_traits.hpp"

namespace owl
{
  namespace color
  {
    template <typename T, std::size_t N, template <typename> typename Derived>
    class color
    {
    public:
      using vector_type = math::vector<T, N>;
      using value_type = T;
      using reference = T&;
      using pointer = T*;
      using const_reference = const T&;
      using const_pointer = const T*;
      using size_type = typename vector_type::size_type;
      using iterator = typename vector_type::iterator;
      using const_iterator = typename vector_type::const_iterator;
    
      color() = default;
      color(const color&) = default;
      color(color&&) = default;
      color& operator=(const color&) = default;
      color& operator=(color&&) = default;
    
      color(const math::vector<T,N>& other)
        : channels_{other}
      {
      }
    
      color(vector_type&& other)
        : channels_{std::forward<vector_type>(other)}
      {
      }
    
      template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
      color(Args&&... args)
        : channels_{static_cast<value_type>(std::forward<Args>(args))...}
      {
      
      }
    
      color& operator=(vector_type&& other)
      {
        channels_ = std::forward<vector_type>(other);
        return *this;
      }
    
      color& operator=(const vector_type& other)
      {
        channels_ = other;
        return *this;
      }
    
      operator const vector_type&() const
      {
        return channels_;
      }
    
      operator vector_type&()
      {
        return channels_;
      }
    
      size_type size()
      {
        return channels_.size();
      }
    
      iterator begin()
      {
        return channels_.begin();
      }
    
      const_iterator begin() const
      {
        return channels_.begin();
      }
    
      const_iterator cbegin() const
      {
        return channels_.begin();
      }
    
      iterator end()
      {
        return channels_.end();
      }
    
      const_iterator end() const
      {
        return channels_.end();
      }
    
      const_iterator cend() const
      {
        return channels_.end();
      }
    
      reference operator[](size_type i)
      {
        return channels_[i];
      }
    
      const_reference operator[](size_type i) const
      {
        return channels_[i];
      }
    
      reference operator()(size_type i)
      {
        return channels_[i];
      }
    
      const_reference operator()(size_type i) const
      {
        return channels_[i];
      }
    
      bool operator==(const color& other) const
      {
        return channels_ == other.channels_;
      }
    
      bool operator!=(const color& other) const
      {
        return channels_ != other.channels_;
      }
    
      auto operator+(const color& other) const
      {
       return Derived<T>(channels_ + other.channels_);
      }
    
      auto operator-(const color& other) const
      {
       return Derived<T>(channels_ - other.channels_);
      }
    
      auto operator*(const color& other) const
      {
        return Derived<T>(comp_mult(channels_, other.channels_));
      }
    
      auto operator*(color&& other) const
      {
        return Derived<T>(comp_mult(channels_, other.channels_));
      }
    
      auto operator/(const color& other) const
      {
        return Derived<T>(comp_div(channels_, other.channels_));
      }
    
      auto operator/(color&& other) const
      {
        return Derived<T>(comp_div(channels_, other.channels_));
      }
    
      template <typename Scalar, typename = typename vector_type::template enable_if_scalar_t<Scalar> >
      auto operator*(Scalar s)
      {
        return Derived<decltype(std::declval<T>() * std::declval<Scalar>())>(channels_ * s);
      }
    
    private:
      vector_type channels_;
    };
  
    template <typename Scalar,typename T, std::size_t N, template <typename> typename Derived, typename = typename math::vector<T,N>::template enable_if_scalar_t<Scalar> >
    auto operator*(Scalar s, color<T, N, Derived>& col)
    {
      return col * s;
    }
  
    template <typename T, std::size_t N, template <typename> typename Derived>
    std::ostream& operator<<(std::ostream& out, const color<T,N,Derived>& col)
    {
      return out << static_cast<const math::vector<T,N>&>(col);
    }
  
    template<typename T>
    class cmyk : public color<T, 4, cmyk>
    {
    public:
      using base_type = color<T, 4, owl::color::cmyk>;
      using color<T, 4, owl::color::cmyk>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference c() const { return (*this)[0];}
      reference c() { return (*this)[0]; }
      const_reference m() const { return (*this)[1];}
      reference m() { return (*this)[1]; }
      const_reference y() const { return (*this)[2];}
      reference y() { return (*this)[2]; }
      const_reference k() const { return (*this)[3];}
      reference k() { return (*this)[3]; }
    };
  
    template<typename T>
    class rgb : public color<T, 3, rgb>
    {
    public:
      using base_type = color<T, 3, owl::color::rgb>;
      using color<T, 3, owl::color::rgb>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference r() const { return (*this)[0];}
      reference r() { return (*this)[0]; }
      const_reference g() const { return (*this)[1];}
      reference g() { return (*this)[1]; }
      const_reference b() const { return (*this)[2];}
      reference b() { return (*this)[2]; }
    };
  
    template<typename T>
    class bgr : public color<T, 3, bgr>
    {
    public:
      using base_type = color<T, 3, owl::color::rgb>;
      using color<T, 3, owl::color::rgb>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference b() const { return (*this)[0];}
      reference b() { return (*this)[0]; }
      const_reference g() const { return (*this)[1];}
      reference g() { return (*this)[1]; }
      const_reference r() const { return (*this)[2];}
      reference r() { return (*this)[2]; }
    };
  
    template<typename T>
    class hsv : public color<T, 3, hsv>
    {
    public:
      using base_type = color<T, 3, owl::color::hsv>;
      using color<T, 3, owl::color::hsv>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference h() const { return (*this)[0];}
      reference h() { return (*this)[0]; }
      const_reference s() const { return (*this)[1];}
      reference s() { return (*this)[1]; }
      const_reference v() const { return (*this)[2];}
      reference v() { return (*this)[2]; }
    };

  /*
    template<typename T>
    class rgba : public color<T, 4, rgba>
    {
    public:
      using base_type = color<T, 4, owl::color::rgba>;
      using color<T, 4, owl::color::rgba>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference r() const { return (*this)[0];}
      reference r() { return (*this)[0]; }
      const_reference g() const { return (*this)[1];}
      reference g() { return (*this)[1]; }
      const_reference b() const { return (*this)[2];}
      reference b() { return (*this)[2]; }
      const_reference a() const { return (*this)[3];}
      reference a() { return (*this)[3]; }
    };
  
    template<typename T>
    class bgra : public color<T, 4, bgra>
    {
    public:
      using base_type = color<T, 4, owl::color::bgra>;
      using color<T, 4, owl::color::bgra>::color;
      using typename base_type::value_type;
      using typename base_type::reference;
      using typename base_type::const_reference;
   
      const_reference b() const { return (*this)[0];}
      reference b() { return (*this)[0]; }
      const_reference g() const { return (*this)[1];}
      reference g() { return (*this)[1]; }
      const_reference r() const { return (*this)[2];}
      reference r() { return (*this)[2]; }
      const_reference a() const { return (*this)[3];}
      reference a() { return (*this)[3]; }
    };
  */
    template <typename T>
    using gray = T;
  
    using gray8u = gray<std::uint8_t>;
    using rgb8u = rgb<std::uint8_t>;
    using bgr8u = bgr<std::uint8_t>;
    using cmyk8u = cmyk<std::uint8_t>;
    //using rgba8u = rgba<std::uint8_t>;
    //using bgra8u = bgra<std::uint8_t>;
  
    using gray16u = gray<std::uint16_t>;
    using rgb16u = rgb<std::uint16_t>;
    using bgr16u = bgr<std::uint16_t>;
    using cmyk16u = cmyk<std::uint16_t>;
    //using rgba16u = rgba<std::uint16_t>;
    //using bgra16u = bgra<std::uint16_t>;

    using gray32f = gray<float>;
    using rgb32f = rgb<float>;
    using cmyk32f = cmyk<float>;
    using hsv32f = hsv<float>;
   // using rgba32f = rgba<float>;
   // using bgra32f = bgra<float>;

    using gray64f = gray<double>;
    using rgb64f = rgb<double>;
    using cmyk64f = cmyk<double>;
    using hsv64f = hsv<double>;
    //using rgba64f = rgba<double>;
    //using bgra64f = bgra<double>;
  
    
  }
}
