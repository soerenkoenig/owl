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

#include "owl/scene/node.hpp"

namespace owl
{
  namespace scene
  {
    template<typename Scalar>
    class graph
    {
    public:
      std::shared_ptr<node<Scalar>> root;
    };
  
    template<typename S, typename...Args>
    std::shared_ptr<graph<S>> make_graph(Args&&... args)
    {
      return std::make_shared<graph<S>>(std::forward<Args>(args)...);
    }
  
  
  }
}

