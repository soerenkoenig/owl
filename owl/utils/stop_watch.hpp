//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <chrono>
#include <iostream>

namespace owl
{
  namespace utils
  {
    class stop_watch
    {
    public:
      stop_watch(bool verbose = true);
    
      ~stop_watch();
    
      void start();
    
      double stop(std::ostream& out = std::cout) const;

    private:
      using clock_type = std::chrono::high_resolution_clock;
     
      using time_point = std::chrono::time_point<clock_type>;
    
      time_point _begin;
       
      bool _verbose;
    };
  }
}
