#include "owl/color/colors.hpp"
#include "owl/color/color_conversion.hpp"
#include "owl/color/color_names.hpp"
#include "owl/color/gamma_correction.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"


namespace test
{
  
  TEST_CASE( "colors", "[color]" )
  {
    using namespace owl::color;
    auto cred = color_names::lookup<unsigned char>("red");
    rgb32f red(1.0f, 0.0f, 0.0f);
    rgb32f green(0.0f, 1.0f, 0.0f);
    rgb32f blue(0.0f, 0.0f, 1.0f);
    rgb32f white(1.0f, 1.0f, 1.0f);
    rgb32f black(0.0f, 0.0f, 0.0f);
    rgb8u x(1,2,3);
  
    CHECK(convert<cmyk32f>(red) == cmyk32f(0.0f,1.0f,1.0f,0.0f));
    auto black2 = convert<cmyk32f>(black);
    CHECK(convert<cmyk32f>(black) == cmyk32f(0.0f, 0.0f, 0.0f, 1.0f));
    CHECK(convert<cmyk32f>(white) == cmyk32f(0.0f,0.0f,0.0f,0.0f));
  
   // CHECK(convert<hsvu8>(rgbu8(86, 84, 3)) == );
  
    auto darkred = 0.5f*red;
    auto red2g = linear_2_gamma_corrected(darkred, gamma_correction_model::s_rgb{});
  }
  
  TEST_CASE("convert", "[color]")
  {
    using namespace owl::color;
    std::vector<rgb32f> rgbs = {
    {1.0000,         0,         0},
    {1.0000,    0.5000,         0},
    {1.0000,    1.0000,         0},
    {     0,    1.0000,         0},
    {     0,         0,    1.0000},
    {0.6667,         0,    1.0000}};
  
    std::vector<hsv32f> hsvs = {
     {0,    1.0000,    1.0000},
    {0.0833,    1.0000,    1.0000},
    {0.1667,    1.0000,    1.0000},
    {0.3333,    1.0000,    1.0000},
    {0.6667,    1.0000,    1.0000},
    {0.7778,    1.0000,    1.0000}
   };
  
   for(std::size_t i = 0; i  < rgbs.size(); ++i)
    CHECK(convert<hsv32f>(rgbs[i]) == hsvs[i]);
  
  }
  
  
}




