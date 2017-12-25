#include "owl/color/colors.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  TEST_CASE( "colors", "[math]" )
  {
    using namespace owl::color;
    rgb32f red(1.0f, 0.0f, 0.0f);
    rgb32f green(0.0f, 1.0f, 0.0f);
    rgb32f blue(0.0f, 0.0f, 1.0f);
    rgb32f white(1.0f, 1.0f, 1.0f);
    rgb32f black(0.0f, 0.0f, 0.0f);
  
    CHECK(convert<cmyk32f>(red) == cmyk32f(0.0f,1.0f,1.0f,0.0f));
    auto black2 = convert<cmyk32f>(black);
    CHECK(convert<cmyk32f>(black) == cmyk32f(0.0f,0.0f,0.0f,1.0f));
    CHECK(convert<cmyk32f>(white) == cmyk32f(0.0f,0.0f,0.0f,0.0f));
  
    auto darkred = 0.5f*red;
  
  
  
  
  
  }
}




