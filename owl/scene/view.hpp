//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
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
    template <typename Pixel, typename Scalar>
    class view
    {
    public:
      using color = Pixel;
    
      std::shared_ptr<graph<Scalar>> scene;
      std::shared_ptr<camera> point_of_view;
    
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
    
      view(graphics::image<Pixel>& img, std::shared_ptr<graph<Scalar>> g)
        : raw_image_(img.data())
        , step_(img.width())
        , scene(g)
       // , point_of_view(g.first_point_of_view())
      {
        viewport_.lower_bound = math::vector<std::size_t,2>::zero();
        viewport_.upper_bound = math::vector<std::size_t,2>(img.width(), img.height());
      
      }
    
    private:
      math::rectangle<std::size_t> viewport_;
      color* raw_image_;
      std::size_t step_;
    
    };
  
    template<typename P, typename S>
    std::shared_ptr<view<P,S>> make_view(graphics::image<P>& img, std::shared_ptr<graph<S>> graph)
    {
      return std::make_shared<view<P,S>>(img, graph);
    }
  
  }
}
