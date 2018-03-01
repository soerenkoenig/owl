//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include "owl/scene/node.hpp"

namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class look_at_constraint
    {
    public:
      look_at_constraint(std::shared_ptr<node<Scalar>> target)
        : target_(target)
      {
      }
    
      void operator()(std::shared_ptr<node<Scalar>> n)
      {
       
        //n->orientation = math::lookat(<#const vector<S, 3> &eye#>, <#const vector<S, 3> &target#>, <#vector<S, 3> up#>)
      }
    
    private:
      std::shared_ptr<node<Scalar>> target_;
   
    };
  
    template <typename Scalar, typename... Args>
    auto make_look_at_constraint(Args&&... args)
    {
      return std::make_shared<look_at_constraint<Scalar>>(std::forward<Args>(args)...);
    }
  }
}
