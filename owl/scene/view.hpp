//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include <memory>

#include "owl/scene/graph.hpp"
#include "owl/scene/camera.hpp"
#include "owl/math/interval.hpp"
#include "owl/graphics/image.hpp"

namespace owl
{
  namespace scene
  {
    template <typename Color, typename Scalar>
    class view
    {
    public:
      using color = Color;
    
      view(graphics::image<color>& img, graph<Scalar>& g)
        : raw_image_(img.data())
        , step_(img.width())
        , scene_(&g)
        , point_of_view_(g.first_point_of_view())
      {
        viewport_.lower_bound = math::vector<std::size_t,2>::zero();
        viewport_.upper_bound = math::vector<std::size_t,2>(img.width(), img.height());
      }
    
    
      std::size_t width() const
      {
        return viewport_.width();
      }
    
      std::size_t height() const
      {
        return viewport_.height();
      }
    
      inline const color& operator()(std::size_t x, std::size_t y) const
      {
        return *(raw_image_ + y * step_ + x + viewport_.left());
      }
    
      inline color& operator()(std::size_t x, std::size_t y)
      {
        return *(raw_image_ + y * step_ + x + viewport_.left());
      }
    
  
    private:
      graph<Scalar>* scene_ = nullptr;
      node<Scalar>* point_of_view_ = nullptr;
      math::rectangle<std::size_t> viewport_;
      color* raw_image_ = nullptr;
      std::size_t step_ = 0;
    
    };
  
  
  }
}
