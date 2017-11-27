
#include "owl/math/matrix.hpp"
#include "owl/math/trafos.hpp"
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
  
   TEST_CASE( "matrix multiplications", "[math]" )
  {
    owl::math::matrix33f m;
    m << 1,2,3,
         4,5,6,
         7,8,9;
  
    owl::math::vector3f v;
    v << 1,4,7;
  
    auto vt = transpose(v);
  
    owl::math::vector3f v2;
    v2 << 30, 66, 102;
  
   owl::math::row_vector<float,3> v3;
   v3 << 66, 78, 90;
  
    CHECK(m*v == v2);
    CHECK(vt*m == v3);
    CHECK(vt*v == 66);
    CHECK(vt*v == sqr_length(v));
  
     owl::math::matrix33f m2;
    m2 << 1,  4,  7,
          4, 16, 28,
          7, 28, 49;
  
    CHECK( v*vt == m2);
  
  }
  

  TEST_CASE( "matrix", "[math]" )
  {
    using namespace owl::math;
    auto tr = translate<float>(vector3f(0,0,0),vector3f(1,2,3));
    CHECK(approx(tr * vector4f(0,0,0,1)) == vector4f(1,2,3,1));
    CHECK(approx(rotateX(degrees<float>(0))) == matrix44f::identity());
    CHECK(approx(det(rotateY(degrees<float>(4.9)))) == 1);
    CHECK(approx(det(rotateZ(degrees<float>(4.9)))) == 1);
      
    auto trt = rotate(vector3f(1,0,0),vector3f(1,1,0),degrees<float>(90));

    CHECK(approx(trt*vector4f(0,0,0,1)) == vector4f(1,0,1,1));
    
    CHECK(approx(rotateX(degrees<float>(3.6)) * rotateX(degrees<float>(-3.6))) == matrix44f::identity());
  
    auto I = matrix44f::identity();
    auto V = vector4f{1,2,3,4};
    CHECK(approx(I*V) == vector4f(1,2,3,4));
    
    auto m = random_matrix<double,4,4>();
    CHECK(approx(invert(m)*m).margin(0.00000001) == matrix44f::identity());
    
  }
}
