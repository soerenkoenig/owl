#pragma once

#include "owl/math/matrix.hpp"
#include "owl/color/colors.hpp"
#include "owl/utils/lin_space.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace owl
{
  namespace color
  {
  
    ///create a linearly spaced vector with N values starting at first_val and ending ant last_val
  
    namespace colormaps
    {
      /// possible colormaps are
      /// "gray" black .. white
      /// "bone" grayscale colormap with a higher blue component (looks like xray images)
      /// "jet" blue .. cyan .. yellow .. orange .. red
      /// "hot" black .. red .. yellow .. white
      /// "thermo" black .. magenta .. blue.. cyan..green .. yellow ..red.. white
      /// "hsv" red .. yellow .. green .. cyan .. blue .. magenta .. red
    
      //a linear grayscale colormap.
      template <typename T>
      rgb<T> gray(float x)
      {
        return rgb<T>( x, x, x);
      }
    
      //bone
      //is a grayscale colormap with a higher value for the blue component.
      //This colormap is useful for adding an "electronic" look to grayscale images.
      template <typename T>
      rgb<T> bone(float x)
      {
        rgb<T> col(0,0,0);
        if(x < 3.0f / 4.0f)
          col(0) = (7.0f / 8.0f * x);
        else
          col(0) = (11.0f / 8.0f * x - 3.0f / 8.0f);
      
        if(x < 3.0f / 8.0f)
          col(1) = (7.0f / 8.0f * x);
        else if(x < 3.0f / 4.0f)
          col(1) = (29.0f / 24.0f * x - 1.0f / 8.0f);
        else
          col(1) = (7.0f / 8.0f * x + 1.0f / 8.0f);

        if(x < 3.0f / 8.0f)
          col(2) = (29.0f / 24.0f * x);
        else
          col(2) = (7.0f / 8.0f * x + 1.0f / 8.0f);
      
        return col;
      }
    
      template <typename T>
      rgb<T> jet(float x)
      {
        rgb<T> col;
        col(0) = col(1) = col(2) = 0.0f;

        if((x >= 3.0f / 8.0f) && (x < 5.0f / 8.0f))
          col(0) = (4.0f * x - 3.0f / 2.0f);
      
        if((x >= 5.0f / 8.0f) && (x < 7.0f / 8.0f))
        {
          col(0) = 1.0f;
        }
        if(x >= 7.0f / 8.0f)
          col(0) += -4.0f * x + 9.0f / 2.0f;
      
        if(x >= 1.0f/8.0f && x < 3.0f / 8.0f)
          col(1)= (4.0f * x - 1.0f / 2.0f);

        if(x >= 3.0f/8.0f && x < 5.0f / 8.0f)
        {
          col(1)=1;
        }
        if(x >= 5.0f / 8.0f && x < 7.0f / 8.0f)
            col(1) += (-4.0f * x + 7.0f / 2.0f);
      
        if(x < 1.0f / 8.0f)
          col(2) = (4.0f * x + 1.0f / 2.0f);

        if(x >= 1.0f / 8.0f && x < 3.0f / 8.0f)
        {
          col(2) = 1.0;
        }
        if(x >= 3.0f / 8.0f && x < 5.0f / 8.0f)
          col(2) += -4.0f * x + 5.0f / 2.0f;
          return col;
      }
    
      template <typename T>
      rgb<T> hot(float x)
      {
        rgb<T> col;
        col(0) = col(1) = col(2) = 0.0f;

        if(x <= 1.0f/3.0f)
          col(0) = 3.0f * x;
        else
          col(0) = 1.0f;
      
      
        if(x > 1.0f/3.0f && x < 2.0f/3.0f)
          col(1)= 3.0f*x -1.0f;
        if(x >=2.0/3.0f)
          col(1)=1.0f;
      
      
        if(x >= 2.0f/3.0f)
          col(2)=3.0f*x-2.0f;
          return col;
      }
    
    
      template <typename T>
      rgb<T> hsv(float x)
      {
        rgb<T> col;
        col(0) = col(1) = col(2) = 0.0f;

        if(x <= 1.0f/5.0f)
          col(0) =  1.0f;
        if(x > 1.0f/5.0f && x <=2.0f/5.0f)
          col(0) =  -5.0f*x + 2.0f;
        if(x > 4.0f/5.0f)
          col(0) = 5.0f*x - 4.0f;

        if(x <= 1.0f/5.0f)
          col(1) =  5.0f*x;
        if(x > 1.0f/5.0f && x <=3.0f/5.0f)
          col(1) =  1.0f;
        if(x > 3.0f/5.0f && x <= 4.0f/5.0f)
          col(1) = -5.0f*x+4.0f;

        if(x > 2.0f/5.0f && x <=3.0f/5.0f)
          col(2) =  5.0f*x-2.0f;
        if(x > 3.0f/5.0f && x <= 4.0f / 5.0f)
          col(2) = 1.0f;
        if(x >4.0f/5.0f)
          col(2) =  -5.0f*x + 5.0f;
        return col;
      }
    
      template <typename T>
      rgb<T> thermo(float x)
      {
        rgb<T> col;
        col(0) = col(1) = col(2) = 0.0f;
    
        if(x <= 1.0f/7.0f)
          col(0) =  7.0f*x;
        if(x > 1.0f/7.0f && x <=2.0f/7.0f)
          col(0) =  -7.0f*x + 2.0f;
        if(x > 4.0f/7.0f && x <=5.0f/7.0f)
          col(0) = 7.0f*x-4.0f;
        if(x >5.0f/7.0f)
          col(0) = 1.0f;

        if(x >=2.0f/7.0f && x <= 3.0f/7.0f)
          col(1) =  7.0f*x-2.0f;
        else if(x > 3.0f/7.0f && x <=5.0f/7.0f)
          col(1) =  1.0f;
        else if(x > 5.0f/7.0f && x <=6.0f/7.0f)
          col(1) = -7.0f*x+6.0f;
        else if(x > 6.0f/7.0f)
          col(1) = 7.0f*x-6.0f;

        if(x <= 1.0f/7.0f)
          col(2) = 7.0f*x;
        if(x > 1.0f/7.0f && x <=3.0f / 7.0f)
          col(2) =  1.0f;
        if(x > 3.0f/7.0f && x <=4.0f / 7.0f)
          col(2) = -7.0f*x + 4.0f;
        if(x > 6.0f/7.0f)
          col(2) = 7.0f* - 6.0f;
        return col;
      }
    }

  
   enum class colormap
   {
     gray, bone, jet, hot, hsv, thermo
   };
  
  
    template <typename T>
    std::vector<rgb<T>> create_color_map(std::size_t steps = 256, colormap name = colormap::jet)
    {
      using color_type = rgb<T>;
    
      std::vector<color_type> map;
      map.resize(steps);
    
      std::vector<T> x(steps);
      utils::lin_space(x.begin(),x.end(), 0, 1);
    
        for(std::size_t i = 0; i < steps; i++)
        {
        switch(name)
        {
        case colormap::gray:
          map[i] = colormaps::gray<T>(x[i]);
          break;
        case colormap::bone:
          map[i] = colormaps::bone<T>(x[i]);
          break;
        case colormap::jet:
          map[i] = colormaps::jet<T>(x[i]);
          break;
        case colormap::hot:
          map[i] = colormaps::hot<T>(x[i]);
          break;
        case colormap::hsv:
          map[i] = colormaps::hsv<T>(x[i]);
          break;
        case colormap::thermo:
          map[i] = colormaps::thermo<T>(x[i]);
          break;
        default:
          assert(false);//colormap not found
          break;
        }
      }
      return map;
    }
    
    std::vector<rgb8u> create_color_map_u8(std::size_t steps, colormap name)
    {
      auto colmap = create_color_map<float>(steps, name);
    
      std::vector<rgb8u> colmap2;
      colmap2.resize(colmap.size());
    
      std::transform(colmap.begin(), colmap.end(),
        colmap2.begin(), [](const auto& v){ return rgb8u(v[0]*255, v[1]*255, v[2]*255);});
    
      return colmap2;
    }

  }
}




