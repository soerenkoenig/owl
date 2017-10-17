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
    
        void tic();
    
        double toc(std::ostream& out = std::cout) const;

    private:
        using clock_type = std::chrono::high_resolution_clock ;
        using second_type = std::chrono::duration<double, std::ratio<1> >;
        using milli_second_type = std::chrono::duration<double, std::milli >;
    
        std::chrono::time_point<clock_type> _begin;
        bool _verbose;
    };
  }
}
