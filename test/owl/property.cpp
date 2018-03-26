#include "owl/utils/property.hpp"
#include "catch/catch.hpp"

#include <iostream>


namespace test
{
  class sphere
  {
   public:
     float radius = 1;
  
     auto diameter()
     {
       return owl::utils::make_property<float>(
        [&](){ return 2 * radius; },
        [&](float v){ radius = v/2;}
       );
     }
  
     auto diameter() const
     {
       return owl::utils::make_property<float>(
        [&](){ return 2 * radius; }
       );
     }
  };

  TEST_CASE( "property", "[utils]" )
  {
    using namespace owl::utils;
  
    sphere s;
  
    sphere s2 = s;
  
    s.diameter() = 4;
    CHECK(s.diameter() == 4);
    CHECK(s2.diameter() == 2);
  }
}

