#include "owl/utils/progress.hpp"
#include "catch/catch.hpp"
#include <thread>
#include <iostream>

namespace test
{

  void workload1()
  {
    using namespace std::chrono_literals;
    owl::utils::progress p(10);
    for(std::size_t i = 0; i < 10; ++i)
    {
      p.step();
    }
  }
  void workload2()
  {
    using namespace std::chrono_literals;
    owl::utils::progress p(100);
    for(std::size_t i = 0; i < 100; ++i)
    {
      p.step();
    }
  }
  
  void workload3()
  {
    using namespace owl::utils;
    progress sub_progress(20);
    sub_progress.make_current(10);
    workload1();
    sub_progress.resign_current();
    sub_progress.make_current(10);
    workload2();
    sub_progress.resign_current();
  }


   TEST_CASE( "progress", "[utils]" )
   {
     using namespace owl::utils;
   
     progress overall_progress(10);
   
     overall_progress.on_changed = [&]()
     {
      std::cout << overall_progress.fraction_completed() << " ";
     };

     overall_progress.make_current(2);
     workload1();
     overall_progress.resign_current();
     overall_progress.make_current(5);
     workload2();
     overall_progress.resign_current();
     overall_progress.make_current(3);
     workload3();
     overall_progress.resign_current();
 
   }
  
}
