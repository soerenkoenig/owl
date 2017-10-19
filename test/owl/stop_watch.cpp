#include <sstream>
#include <thread>

#include "owl/utils/stop_watch.hpp"
#include "catch/catch.hpp"

namespace test
{

  TEST_CASE( "stop_watch", "[]" )
  {
    using namespace owl::utils;
    using namespace std::chrono_literals;
    stop_watch s;
    CHECK_FALSE(s.is_running());
    
    s.start();
    CHECK(s.is_running());
    std::this_thread::sleep_for(1s);

    CHECK(Approx(s.elapsed_time()).epsilon(0.01) == 1.0);
    std::this_thread::sleep_for(1s);
    s.stop();
    CHECK_FALSE(s.is_running());
    
    CHECK(Approx(s.elapsed_time()).epsilon(0.01) == 2.0);
    CHECK(Approx(s.elapsed_time()*1000) == s.elapsed_time(std::milli{}));
  }
}


