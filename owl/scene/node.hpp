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
#include <functional>
#include "owl/optional.hpp"
#include "owl/math/matrix.hpp"
#include "owl/math/euler_angles.hpp"
#include "owl/math/trafos.hpp"
#include "owl/math/quaternion.hpp"

#include "owl/scene/light.hpp"
#include "owl/scene/camera.hpp"
#include "owl/scene/material.hpp"
#include "owl/scene/geometry.hpp"
#include "owl/scene/animation.hpp"

namespace owl
{
  namespace scene
  {
    
  
    template<typename Scalar>
    class node : public std::enable_shared_from_this<node<Scalar>>
    {
    public:
        std::string name;
        std::optional<light<Scalar>> light;
        std::optional<camera<Scalar>> camera;
        std::optional<geometry<Scalar>> geometry;
  
        math::quaternion<Scalar> orientation;
        math::vector<Scalar,3>   position;
        math::vector<Scalar,3>   scale;
    
        math::matrix<Scalar,4,4> local_to_parent() const
        {
           return math::translate<Scalar>(position) * math::rotate<Scalar,4>(orientation) * math::scale<Scalar,4>(scale);
        }
    
        math::matrix<Scalar,4,4> local_to_world() const
        {
          if(is_root())
            return local_to_parent();
          else
            return parent_.lock()->local_to_world() * local_to_parent();
        }
    
        math::matrix<Scalar,4,4> world_to_local() const
        {
          return math::invert(local_to_world());
        }
    
        math::vector<Scalar,4> convert_position(const math::vector<Scalar,4>& pos,
          std::shared_ptr<node<Scalar>> to = nullptr) const
        {
          if(to)
            return to->world_to_local()*local_to_world() * pos;
          else
            return local_to_world() * pos;
        }
    
    
        void add_child(std::shared_ptr<node>& n)
        {
          n->parent_ = this->shared_from_this();
          children_.push_back(n);
        }
    
        bool is_root() const
        {
          return !parent_.lock();
        }
    
        std::vector<std::function<void(std::shared_ptr<node<Scalar>>)>> constraints;
    
    private:
        std::weak_ptr<node> parent_;
        std::vector<std::shared_ptr<node>> children_;
    
        std::vector<animation<Scalar>> animations_;
    };
  
    template<typename Scalar, typename... Args>
    std::shared_ptr<node<Scalar>> make_node(Args&&... args)
    {
      return std::make_shared<node<Scalar>>(std::forward<Args>(args)...);
    }
  }
}
