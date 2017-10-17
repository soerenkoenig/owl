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
    stop_watch s(false);
    std::this_thread::sleep_for(2s);
    double duration = s.toc();
  
    CHECK(Approx(duration).epsilon(0.01) == 2.0);
  }
}


