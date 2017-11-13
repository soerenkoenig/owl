
#include "owl/math/matrix.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{

  TEST_CASE( "matrix", "[math]" )
  {
    using namespace owl::math;
    
    CHECK(approx(rotateX<float>(0)) == matrix44f::identity());
    
    CHECK(approx(rotateX<float>(3.6) * rotateX<float>(-3.6)) == matrix44f::identity());
  
    auto I = matrix44f::identity();
    auto V = vector4f{1,2,3,4};
    CHECK(approx(I*V) == vector4f(1,2,3,4));
    
    auto m = random_matrix<double,4,4>();
    CHECK(approx(invert(m)*m).margin(0.00000001) == matrix44f::identity());
    
  }
}
