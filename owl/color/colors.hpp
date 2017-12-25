
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
  namespace color
  {
    template<typename T> class channel_traits
    {
    public:
      static constexpr bool is_specialized = false;
 
      static constexpr T min() noexcept { return T(); }
      static constexpr T max() noexcept { return T(); }
    };
  
    template<> class channel_traits<unsigned char>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr unsigned char min() noexcept { return 0; }
      static constexpr unsigned char max() noexcept { return 255; }
    };
  
    template<> class channel_traits<float>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr float min() noexcept { return 0.0f; }
      static constexpr float max() noexcept { return 1.0f; }
    };
  
    template<> class channel_traits<double>
    {
    public:
      static constexpr bool is_specialized = true;
 
      static constexpr double min() noexcept { return 0.0; }
      static constexpr double max() noexcept { return 1.0; }
    
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
    
      auto operator*(const color& other)
      {
        return Derived<T>(comp_mult(channels_, other.channels_));
      }
    
      auto operator*(color&& other)
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
  using rgba8u = rgba<unsigned char>;
  using bgra8u = bgra<unsigned char>;
  using cmyk8u = cmyk<unsigned char>;
  
  
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
  
  

  
  
  
  }
}
