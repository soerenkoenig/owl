
#include "owl/math/matrix.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
    
   

  TEST_CASE( "matrix", "[math]" )
  {
    using namespace owl::math;
    auto tr = translate<float>(vector3f(0,0,0),vector3f(1,2,3));
    CHECK(approx(tr * vector4f(0,0,0,1)) == vector4f(1,2,3,1));
    CHECK(approx(rotateX<float>(0)) == matrix44f::identity());
    CHECK(approx(det(rotateY<double>(4.9))) == 1);
    CHECK(approx(det(rotateZ<double>(4.9))) == 1);
  
    auto I = matrix44f::identity();
    auto V = vector4f{1,2,3,4};
    V = I*V;
    CHECK(V == vector4f(1,2,3,4));
    auto M = invert(I)*I;
    std::cout << M << std::endl;
  }
}
