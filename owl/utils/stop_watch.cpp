#include "owl/stop_watch.hpp"

namespace owl
{
  namespace utils
  {
    stop_watch::stop_watch()
    {
      reset();
    }
    
    void stop_watch::reset()
    {
      _elapsed_time = duration::zero();
      _running = false;
    }
    
    void stop_watch::restart()
    {
      _elapsed_time = duration::zero();
      start();
    }
    
    double stop_watch::current_elapsed_time() const
    {
      return current_elapsed_time(std::ratio<1>{});
    }
    
    double stop_watch::elapsed_time() const
    {
      return elapsed_time(std::ratio<1>{});
    }
    
    stop_watch::duration stop_watch::current_elapsed_duration() const
    {
      return is_running() ? clock_type::now() - _last_start : duration::zero();
    }
    
    stop_watch::duration stop_watch::elapsed_duration() const
    {
      return is_running() ? _elapsed_time + current_elapsed_duration() : _elapsed_time;
    }
    
    void stop_watch::start()
    {
      _running = true;
      _last_start = clock_type::now();
    }
    
    void stop_watch::stop()
    {
      _elapsed_time += clock_type::now() - _last_start;
      _running = false;
    }
    
    bool stop_watch::is_running() const
    {
      return _running;
    }

  }
}
