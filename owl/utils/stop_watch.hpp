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
#include <ratio>
#include <iostream>

namespace owl
{
  namespace utils
  {
    /**
     A stop watch class to make time measurements using std::chrono_high_resolution_clock as internal clock.
     */
    class stop_watch
    {
    public:
      /*!
        clock type of internal clock used to do time measurements
       */
      using clock_type = std::chrono::high_resolution_clock;
      /*!
       duration type of internal clock
       */
      using duration = clock_type::duration;
      /*!
       timepoint type of internal clock
       */
      using time_point = clock_type::time_point;
      
      /**
       constructs a stop_watch by calling reset
       */
      stop_watch();
      
      /**
       starts time measurement.
       */
      void start();
      
      /**
       Stops time measurement.
       */
      void stop();
      
      /**
       returns true if time measurement is currently running.
       */
      bool is_running() const;
      
      /**
       stops time measurement and set elapsed time to 0.
       */
      void reset();
      
      /**
       equivalent to a call to reset and start
       */
      void restart();
      
      /**
       returns elapsed time in seconds since last call of start or restart, 0.0 otherwise
       */
      double current_elapsed_time() const;
      
      /**
       returns (accumulated) elapsed measured time in seconds
       */
      double elapsed_time() const;
      
      /**
       returns elapsed measured time in given ratio of seconds since last call of start or restart,
       0.0 otherwise. e.g. current_elapsed_time(std::milli{}) would return result in milli seconds
       */
      template<typename Ratio>
      double current_elapsed_time(Ratio) const
      {
        return std::chrono::duration_cast<std::chrono::duration<double, Ratio>>(current_elapsed_duration()).count();
      }
      
      /**
       returns (accumulated) elapsed measured time in given ratio of seconds
       e.g. elapsed_time(std::milli{}) would return result in milli seconds
       */
      template<typename Ratio>
      double elapsed_time(Ratio) const
      {
        return std::chrono::duration_cast<std::chrono::duration<double, Ratio>>(elapsed_duration()).count();
      }
      
    private:
      duration current_elapsed_duration() const;
      
      duration elapsed_duration() const;
      
      time_point _last_start;
     
      duration _elapsed_time;
      
      bool _running;
    };
  }
}
