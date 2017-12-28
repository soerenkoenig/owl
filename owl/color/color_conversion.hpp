
//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/color/colors.hpp"

namespace owl
{
  namespace color
  {
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

        T x = 0.0f, y = 0.0f, z = 0.0f;
      
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
    struct color_conversion<rgb<T>, gray<T>>
    {
      static rgb<T> convert(const gray<T>& col)
      {
        return {col, col, col};
      }
    };
  
    template <typename T>
    struct color_conversion<bgr<T>, gray<T>>
    {
      static bgr<T> convert(const gray<T>& col)
      {
        return {col, col, col};
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
    struct color_conversion<gray<T>, rgb<T>>
    {
      static gray<T> convert(const rgb<T>& col)
      {
        return 0.2989 * col.r() + 0.5870 * col.g() + 0.1140 * col.b();
      }
    };
  
    template <typename T>
    struct color_conversion<gray<T>, bgr<T>>
    {
      static gray<T> convert(const bgr<T>& col)
      {
        return 0.2989 * col.r() + 0.5870 * col.g() + 0.1140 * col.b();
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
