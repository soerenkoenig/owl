#include "owl/math/plane.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  
  TEST_CASE( "plane", "[math]" )
  {
    using namespace owl::math;
  
    ray3f r1(vector3f(0,0,0),vector3f(1,1,1));
    plane3f pl(vector3f(0,1,0),vector3f(1,0,0) );
    CHECK(distance(pl,r1(*intersect(r1, pl))) == 0);
  
  
  }
}

