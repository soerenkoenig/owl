
#include "owl/math/matrix.hpp"
#include "catch/catch.hpp"

namespace test
{

  TEST_CASE( "matrix", "[math]" )
  {
    using namespace owl::math;
  
    matrix44f::identity();
    auto I = matrix44f::identity();
    auto V = vector4f{1,2,3,4};
    V = I*V;
    CHECK(V == vector4f(1,2,3,4));
   auto M = invert(I)*I;
   std::cout << M << std::endl;
  }
}
