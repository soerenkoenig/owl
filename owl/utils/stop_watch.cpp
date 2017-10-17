#include "owl/stop_watch.hpp"

namespace owl
{
  namespace utils
  {
    stop_watch::stop_watch(bool verbose /* = true */)
      : _begin(clock_type::now()), _verbose(verbose) {}
    
    stop_watch::~stop_watch()
    {
      stop();
    }
    
    void stop_watch::start()
    {
        _begin = clock_type::now();
    }
    
    double stop_watch::stop(std::ostream& out /* = std::cout */) const
    {
      using second_type = std::chrono::duration<double, std::ratio<1>>;
    
      double elapsed = std::chrono::duration_cast<second_type>(clock_type::now() - _begin).count();
  
      if(_verbose)
          out << "elapsed time: "<< elapsed << "s" << std::endl;
        
      return elapsed;
    }
  }
}
