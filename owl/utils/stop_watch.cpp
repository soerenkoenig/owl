#include "owl/stop_watch.hpp"

namespace owl {
  namespace utils {
    stop_watch::stop_watch(bool verbose /* = true */)
      : _begin(clock_type::now()), _verbose(verbose) {}
    
    stop_watch::~stop_watch()
    {
      toc();
    }
    
    void stop_watch::tic()
    {
        _begin = clock_type::now();
    }
    
    double stop_watch::toc(std::ostream& out /* = std::cout */) const
    {
      double elapsed = std::chrono::duration_cast<second_type>(clock_type::now() - _begin).count();
  
      if(_verbose)
          out << "elapsed time: "<< elapsed << "s" << std::endl;
        
      return elapsed;
    }
  }
}
