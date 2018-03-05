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
#include <stack>

#include "owl/scene/node.hpp"

namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class graph
    {
    public:
    
      node<Scalar>* first_point_of_view()
      {
        std::stack<node<Scalar>*> nodes;
        nodes.push(&root);
        while(!nodes.empty())
        {
          auto* current = nodes.top();
        
          if(current->camera)
            return current;
          nodes.pop();
        
          for(auto& child : current->children)
            nodes.push(&child);
        }
        return nullptr;
      }
    
      node<Scalar> root;
    };

  }
}

