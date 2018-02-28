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

#include "owl/math/matrix.hpp"
#include "owl/math/euler_angles.hpp"
#include "owl/math/trafos.hpp"
#include "owl/math/quaternion.hpp"


namespace owl
{
  namespace scene
  {
    template <typename Scalar>
    class animation;
  
    template<typename Scalar>
    class node : std::enable_shared_from_this<node<Scalar>>
    {
    public:
        std::string name;
        std::shared_ptr<node> light;
        std::shared_ptr<node> camera;
        std::shared_ptr<node> geometry;
    
  
        math::quaternion<Scalar> orientation;
        math::vector<Scalar,3>   position;
        math::vector<Scalar,3>   scale;
    
        math::matrix<Scalar,4,4> local_to_parent()
        {
           return math::translate<Scalar>(position) * math::rotate<Scalar,4>(orientation) * math::scale<Scalar,4>(scale);
        }
    
        math::matrix44f local_to_world()
        {
          if(is_root())
            return local_to_parent();
          else
            return parent_.lock()->local_to_world() * local_to_parent();
        }
    
        void add_child(std::shared_ptr<node>& n)
        {
          n.parent_ = this->shared_from_this();
          children_push_back(n);
        }
    
    
        bool is_root() const
        {
          return !parent_.lock();
        }
    
    
    private:
        std::weak_ptr<node> parent_;
        std::vector<std::shared_ptr<node>> children_;
    
        std::vector<animation<Scalar>> animations_;
    };  
  }
}
