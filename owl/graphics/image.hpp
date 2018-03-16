//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include <vector>

#include "owl/color/color.hpp"

namespace owl
{
  namespace graphics
  {
    template <typename Color>
    class image
    {
    public:
      using color_type = Color;
      using iterator = typename std::vector<color_type>::iterator;
      using const_iterator = typename std::vector<color_type>::const_iterator;
      using size_type = typename std::vector<color_type>::size_type;
      using pointer = Color*;
      using const_pointer = const Color*;
      using value_type = Color;
      using reference = Color&;
    
      image() = default;
    
      image(size_type w, size_type h, color_type c = {})
        : data_{w * h, c}
        , width_{w}
        , height_{h}
      {
      }
    
      void resize(size_type w, size_type h, color_type c = {})
      {
        width_ = w;
        height_ = h;
        data_.resize(w * h, c);
      }
    
      pointer data()
      {
        return data_.data();
      }
    
      const_pointer data() const
      {
        return data_.data();
      }

      iterator begin()
      {
        return data_.begin();
      }
    
      iterator end()
      {
        return data_.end();
      }
    
      const_iterator cbegin() const
      {
        return data_.cbegin();
      }
    
      const_iterator cend() const
      {
        return data_.cend();
      }
    
      const_iterator begin() const
      {
        return data_.begin();
      }
    
      const_iterator end() const
      {
        return data_.end();
      }
    
      size_type size() const
      {
        return data_.size();
      }
    
      const size_type& width() const
      {
        return width_;
      }
    
      const size_type& height() const
      {
        return height_;
      }
    
      color_type& operator()(size_type x, size_type y)
      {
        return data_[y * width_ + x];
      }

      const color_type& operator()(size_type x, size_type y) const
      {
        return data_[y * width_ + x];
      }
    
      color_type& operator()(size_type i)
      {
        return data_[i];
      }

      const color_type& operator()(size_type i) const
      {
        return data_[i];
      }
    
      bool is_inside(size_type x, size_type y) const
      {
        return (x < width_ && y < height_);
      }
    
    private:
      size_type width_;
      size_type height_;
      std::vector<color_type> data_;
    };
    
    using rgb8u_image = image<owl::color::rgb8u>;
  
  
    inline rgb8u_image create_grid(std::size_t n_x, std::size_t n_y, std::size_t spacing = 4)
    {
      std::size_t w = n_x + (n_x-1)*spacing;
      std::size_t h = n_y + (n_y-1)*spacing;
      rgb8u_image img(w,h);
      for(std::size_t y = 0; y < h; ++y)
        for(std::size_t x = 0; x < w; ++x)
        {
          bool on_horz_line = x % (spacing+1) == 0;
          bool on_vert_line = y % (spacing+1) == 0;
          img(x,y) = on_horz_line || on_vert_line ? color::rgb8u(50,50,50) : color::rgb8u(255,255,255);
          bool on_boundary = (x < 2 || y < 2 || x >= w-2 || y >= h-2);
          bool on_vert_center_line = std::abs((int)(x - (w/2))) < 2;
          bool on_horz_center_line = std::abs((int)(y - (h/2))) < 2;
          if(on_vert_center_line || on_horz_center_line || on_boundary)
            img(x,y) = color::rgb8u(50,50,50);
        }

      return img;
    }
  
  
    inline rgb8u_image create_grid_color(std::size_t n_x, std::size_t n_y, std::size_t spacing = 4)
    {
      std::size_t w = n_x + (n_x-1)*spacing;
      std::size_t h = n_y + (n_y-1)*spacing;
      rgb8u_image img(w,h);
      for(std::size_t y = 0; y < h; ++y)
        for(std::size_t x = 0; x < w; ++x)
        {
          bool on_horz_line = x % (spacing+1) == 0;
          bool on_vert_line = y % (spacing+1) == 0;
    
          bool on_vert_center_line = std::abs((int)(x - (w/2))) < 2;
          bool on_horz_center_line = std::abs((int)(y - (h/2))) < 2;
          bool on_boundary = (x < 2 || y < 2 || x >= w-2 || y >= h-2);
          img(x,y) = on_horz_line || on_vert_line ? color::rgb8u(155,155,155) : color::rgb8u(0,0,0);
           if(on_boundary)
            img(x,y) = color::rgb8u(155,155,155);
          if(on_horz_center_line)
            img(x,y) = color::rgb8u(255,100,100);
          if(on_vert_center_line)
            img(x,y) = color::rgb8u(100,100,255);
        
        }

      return img;
    }
  }
}

