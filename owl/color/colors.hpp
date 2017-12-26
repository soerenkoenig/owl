
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

namespace owl
{
  namespace color
  {
    template<typename T> class channel_traits
    {
    public:
      static constexpr bool is_specialized = false;
 
      static constexpr T min() noexcept { return T(); }
      static constexpr T max() noexcept { return T(); }
    
    };
  
    template<> class channel_traits<std::uint8_t>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr std::uint8_t min() noexcept { return 0; }
      static constexpr std::uint8_t max() noexcept { return 255; }
      static constexpr std::uint8_t convert(std::uint8_t v) { return v; }
      static constexpr std::uint8_t convert(std::uint16_t v) { return static_cast<std::uint8_t>( v / 257 ); }
      static constexpr std::uint8_t convert(float v){ return std::clamp(v, 0.0f, 1.0f) * 255; }
      static constexpr std::uint8_t convert(double v){ return std::clamp(v, 0.0, 1.0) * 255; }
    };
  
    template<> class channel_traits<std::uint16_t>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr std::uint16_t min() noexcept { return 0; }
      static constexpr std::uint16_t max() noexcept { return 65535; }
      static constexpr std::uint16_t convert(std::uint8_t v) { return static_cast<std::uint16_t>( ( v << 8 ) | v ); }
      static constexpr std::uint16_t convert(std::uint16_t v) { return v; }
      static constexpr std::uint16_t convert(float v){ return std::clamp(v, 0.0f, 1.0f) * 65535; }
      static constexpr std::uint16_t convert(double v){ return std::clamp(v, 0.0, 1.0) * 65535; }
    };
  
    template<> class channel_traits<float>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr float min() noexcept { return 0.0f; }
      static constexpr float max() noexcept { return 1.0f; }
      static constexpr float convert(std::uint8_t v) { return v / 255.0f; }
      static constexpr float convert(std::uint16_t v) { return v / 65535.0f; }
      static constexpr float convert(float v){ return v; }
      static constexpr float convert(double v){ return static_cast<float>(v); }
    };
  
    template<> class channel_traits<double>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr double min() noexcept { return 0.0; }
      static constexpr double max() noexcept { return 1.0; }
      static constexpr double convert(std::uint8_t v) { return v / 255.0; }
      static constexpr double convert(std::uint16_t v) { return v / 65535.0; }
      static constexpr double convert(float v){ return static_cast<double>(v); }
      static constexpr double convert(double v){ return v; }
    };
  
  
  
  
    template <typename T, std::size_t N, template <typename> typename Derived>
    class color
    {
    public:
      using vector_type = math::vector<T,N>;
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
    
      explicit color(const math::vector<T,N>& other)
        : channels_{other}
      {
      }
    
      explicit color(vector_type&& other)
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
    
      explicit operator const vector_type&() const
      {
        return channels_;
      }
    
      explicit operator vector_type&()
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
    
      auto operator/(const color& other) const
      {
        return Derived<T>(comp_div(channels_, other.channels_));
      }
    
      auto operator*(color&& other) const
      {
        return Derived<T>(comp_mult(channels_, other.channels_));
      }
    
      template <typename Scalar, typename = typename vector_type::template enable_if_scalar_t<Scalar> >
      auto operator*(Scalar s)
      {
        return Derived<decltype(std::declval<T>()*std::declval<Scalar>())>(channels_ * s);
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
  
  
  
  using rgb8u = rgb<unsigned char>;
  using bgr8u = bgr<unsigned char>;
  using rgba8u = rgba<unsigned char>;
  using bgra8u = bgra<unsigned char>;
  using cmyk8u = cmyk<unsigned char>;
  
  using rgb16u = rgb<unsigned short>;
  using bgr16u = bgr<unsigned short>;
  using rgba16u = rgba<unsigned short>;
  using bgra16u = bgra<unsigned short>;
  using cmyk16u = cmyk<unsigned short>;
  
  
  using rgb32f = rgb<float>;
  using rgba32f = rgba<float>;
  using bgra32f = bgra<float>;
  using cmyk32f = cmyk<float>;
  using hsv32f = hsv<float>;
  
  using rgb64f = rgb<double>;
  using rgba64f = rgba<double>;
  using bgra64f = bgra<double>;
  using cmyk64f = cmyk<double>;
  using hsv64f = hsv<double>;
  
  namespace detail
  {
    template <typename ColorDestination, typename ColorSource>
    struct color_conversion;
  
    template <typename T>
    struct color_conversion<rgb<T>, cmyk<T>>
    {
      static rgb<T> convert(const cmyk<T>& col)
      {
        constexpr T one = channel_traits<T>::max();
        constexpr T one_minus_k = one - col.k();
      
         return { (one - col.c()) * one_minus_k,
          (one - col.m()) * one_minus_k,
          (one - col.y()) * one_minus_k };
      }
    };
  
    template <typename T>
    struct color_conversion<cmyk<T>, rgb<T>>
    {
      static cmyk<T> convert(const rgb<T>& col)
      {
        constexpr T one = channel_traits<T>::max();
        constexpr T zero = channel_traits<T>::min();
        T one_minus_k = std::max({ col.r(), col.g(), col.b() });
        if(one_minus_k == zero)
          return {zero, zero, zero, one};
      
        T K  = one - one_minus_k;
        return {(one_minus_k - col.r())/one_minus_k,
                (one_minus_k - col.g())/one_minus_k,
                (one_minus_k - col.b())/one_minus_k, K};
      }
    };

    template <typename T>
    struct color_conversion<rgb<T>, hsv<T>>
    {
      static rgb<T> convert(const hsv<T>& col)
      {
        T hue = col.h;
        T sat = col.s;
        T val = col.v;

        float x = 0.0f, y = 0.0f, z = 0.0f;
      
        if(hue == 1)
          hue = 0;
        else
          hue *= 6;

        int i = static_cast<int>( floorf( hue ) );
        T f = hue - i;
        T p = val * ( 1 - sat );
        T q = val * ( 1 - ( sat * f ) );
        T t = val * ( 1 - ( sat * ( 1 - f ) ) );

        switch(i)
        {
        case 0:
          x = val; y = t; z = p;
          break;
        case 1:
          x = q; y = val; z = p;
          break;
        case 2:
          x = p; y = val; z = t;
          break;
        case 3:
          x = p; y = q; z = val;
          break;
        case 4:
          x = t; y = p; z = val;
          break;
        case 5:
          x = val; y = p; z = q;
          break;
        }
        return rgb<T>(x, y, z);
      }
    };
  
    template <typename T>
    struct color_conversion<hsv<T>, rgb<T>>
    {
      static hsv<T> convert(const rgb<T>& col)
      {
      const T &x = col.r();
      const T &y = col.g();
      const T &z = col.b();

      T max = (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);
      T min = (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z);
      T range = max - min;
      T val = max;
      T sat = 0;
      T hue = 0;
  
      if( max != 0 )
        sat = range/max;
    
      if( sat != 0 )
      {
        T h;

        if( x == max )
          h = (y - z) / range;
        else if( y == max )
          h = 2 + ( z - x ) / range;
        else
          h = 4 + ( x - y ) / range;

        hue = h / 6.0f;

        if( hue < 0.0f )
          hue += 1.0f;
      }
      return {hue, sat, val};
      }
    };
  
    template <typename T>
    struct color_conversion<rgb<T>, bgr<T>>
    {
      static rgb<T> convert(const bgr<T>& col)
      {
        return {col.r(), col.g(), col.b()};
      }
    };
  
    template <typename T>
    struct color_conversion<bgr<T>, rgb<T>>
    {
      static bgr<T> convert(const rgb<T>& col)
      {
      return {col.b(), col.g(), col.r()};
      }
    };
  
    template <typename T>
    struct color_conversion<rgba<T>, bgra<T>>
    {
      static rgba<T> convert(const bgra<T>& col)
      {
        return {col.r(), col.g(), col.b(), col.a()};
      }
    };
  
    template <typename T>
    struct color_conversion<bgra<T>, rgba<T>>
    {
      static bgra<T> convert(const rgba<T>& col)
      {
      return {col.b(), col.g(), col.r(), col.a()};
      }
    };

  }
  
  //strait rgba <-> premultiplied rgba
  //(r,g,b,a) <-> (ar, ag, ab, a);
  template <typename ColorDestination, typename ColorSource>
  ColorDestination convert(const ColorSource& col)
  {
    return detail::color_conversion<ColorDestination, ColorSource>::convert(col);
  }
  
  
  //rgb to gray
  template <typename T>
  T rgb_2_gray(const rgb<T>& col)
  {
    return 0.2989 * col.r() + 0.5870 * col.g() + 0.1140 * col.b();
  }
  
  template <typename T>
  T rgb_2_gray(const bgr<T>& col)
  {
    return 0.2989 * col.r() + 0.5870 * col.g() + 0.1140 * col.b();
  }
  
  struct svg_colors
  {
    static std::vector<std::string> color_names;
    static std::vector<rgb8u> color_values;

    static std::optional<rgb8u> lookup(const std::string& name)
    {
      auto it = std::lower_bound(color_names.begin(), color_names.end(), name);
      if(*it != name)
        return std::nullopt;
      return *std::next(color_values.begin(),std::distance(color_names.begin(), it));
    }

    };
  
  }
}
