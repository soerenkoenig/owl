#include "owl/math/quaternion.hpp"
#include "owl/math/trafos.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{

  TEST_CASE( "quaternion", "[math]" )
  {
    using namespace owl::math;
    matrix33f R = rotate_x<float,3>(degrees<float>(30));
    quaternionf q = R;
    matrix33f R2 = q;
    CHECK(approx(R2) == R);
  
    quaternionf q2;
    q2.set_from_axis_angle(vector3f(1,0,0), degrees<float>(30));
    matrix33f R3 = q2;
    CHECK(approx(R3) == R);
  }
  
}

