#include "owl/math/interval.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  
  TEST_CASE( "interval", "[math]" )
  {
    using namespace owl::math;
    
    box<float> b;
    b.insert(vector3f(-1,-1,-1));
    b.insert(vector3f(1,1,1));
    CHECK(b.inside(vector3f(0,0,0)));
    
    interval<float> range;
   
  }
}
