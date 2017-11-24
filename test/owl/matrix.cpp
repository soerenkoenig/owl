
#include "owl/math/matrix.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  TEST_CASE( "matrix transpose", "[math]" )
  {
    owl::math::matrix33f m;
    m << 1,2,3,
         4,5,6,
         7,8,9;
    
    owl::math::matrix33f mt;
    mt << 1,4,7,
          2,5,8,
          3,6,9;
  
    CHECK(m.transposed() == mt);
    m.transpose();
    CHECK(m == mt);
    
    owl::math::matrix23f m2;
    m2 << 1,2,3,
          4,5,6;

    owl::math::matrix32f m2t;
    m2t << 1,4,
           2,5,
           3,6;
    
    CHECK(m2.transposed() == m2t);

  }

  TEST_CASE( "matrix", "[math]" )
  {
    using namespace owl::math;
    auto tr = translate<float>(vector3f(0,0,0),vector3f(1,2,3));
    CHECK(approx(tr * vector4f(0,0,0,1)) == vector4f(1,2,3,1));
    CHECK(approx(rotateX<float>(0)) == matrix44f::identity());
    CHECK(approx(det(rotateY<double>(4.9))) == 1);
    CHECK(approx(det(rotateZ<double>(4.9))) == 1);
      
    auto trt = rotate<float>(vector3f(1,0,0),vector3f(1,1,0),90*3.14159/180.0);

    CHECK(approx(trt*vector4f(0,0,0,1)) == vector4f(1,0,1,1));
    
    CHECK(approx(rotateX<float>(3.6) * rotateX<float>(-3.6)) == matrix44f::identity());
  
    auto I = matrix44f::identity();
    auto V = vector4f{1,2,3,4};
    CHECK(approx(I*V) == vector4f(1,2,3,4));
    
    auto m = random_matrix<double,4,4>();
    CHECK(approx(invert(m)*m).margin(0.00000001) == matrix44f::identity());
    
  }
}
