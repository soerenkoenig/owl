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
    
  
    template<typename Scalar, typename Color>
    class node
    {
    public:
    
    
        math::matrix<Scalar,4,4> local_to_parent() const
        {
           return math::translate<Scalar>(position) * math::square_matrix<Scalar,4>(orientation) * math::scale<Scalar,4>(scale);
        }
    
        math::matrix<Scalar,4,4> local_to_world() const
        {
          if(is_root())
            return local_to_parent();
          else
            return parent_->local_to_world() * local_to_parent();
        }
    
        math::matrix<Scalar,4,4> world_to_local() const
        {
          return math::invert(local_to_world());
        }
    
        math::vector4<Scalar> convert(const math::vector4<Scalar>& v,
          const node* to = nullptr) const
        {
          if(!to)
           return local_to_world() * v;
          return to->world_to_local() * local_to_world() * v;
        }
    
        math::vector3<Scalar> convert_position(const math::vector3<Scalar>& pos,
          const node* to = nullptr) const
        {
          math::vector4<Scalar> pos_h;
          pos_h << pos, 1;
          pos_h = convert(pos_h);
          return math::vector3<Scalar>(pos_h.x(), pos_h.y(), pos_h.z());
        }
    
        math::vector3<Scalar> convert_direction(const math::vector3<Scalar>& dir,
          const node* to = nullptr) const
        {
          math::vector4<Scalar> dir_h;
          dir_h << dir, 0;
          dir_h = convert(dir_h);
          return math::vector3<Scalar>(dir_h.x(),dir_h.y(), dir_h.z());
        }
    
    
        template <typename... Args>
        node& add_child(Args&&... args)
        {
          children.emplace_back(std::forward<Args>(args)...);
          auto& child = children.back();
          child.parent_ = this;
          return child;
        }
    
        bool is_root() const
        {
          return parent_;
        }
    
        const node* parent() const
        {
          return parent_;
        }
    
    
    
        std::string name;
        std::shared_ptr<light<Scalar,Color>> light;
        std::shared_ptr<camera<Scalar>> camera;
        std::shared_ptr<geometry<Scalar>> geometry;
        std::shared_ptr<material<Scalar>> material;
  
        math::quaternion<Scalar> orientation;
        math::vector<Scalar,3>   position;
        math::vector<Scalar,3>   scale;
        std::vector<node<Scalar,Color>> children;
    
        std::vector<std::function<void(node&)>> constraints;
    
    private:
        node* parent_ = nullptr;
    
        std::vector<animation<Scalar>> animations_;
    };
  
  
  }
}
