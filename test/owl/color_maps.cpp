#include "owl/color/color_maps.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"

namespace test
{
  
  TEST_CASE( "color_maps", "[math]" )
  {
    using namespace owl::color;
  
    auto colors1 = create_color_map<std::uint8_t>(100, colormap::gray);
    REQUIRE(colors1->size() == 100);
    REQUIRE(colors1->front() == owl::math::vector<unsigned char,3>(0,0,0));
    REQUIRE(colors1->back() == owl::math::vector<unsigned char,3>(255,255,255));
  }
}



