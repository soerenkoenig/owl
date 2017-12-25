#include "owl/color/color_maps.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  TEST_CASE( "color_maps", "[math]" )
  {
    using namespace owl::color;
    rgba8u col;
    cmyk8u col2;
  
  
   auto x = col * col;
   bool b = col == col;
  /*  auto colors1 = create_color_map_u8(100, "gray");
    REQUIRE(colors1.size() == 100);
    REQUIRE(colors1.front() == vector<unsigned char,3>(0,0,0));
    REQUIRE(colors1.back() == vector<unsigned char,3>(255,255,255));*/
  }
}



