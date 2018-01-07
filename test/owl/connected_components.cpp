#include "owl/utils/connected_components.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"
#include <iostream>

namespace test
{
  
  TEST_CASE( "connected_compenents", "[math]" )
  {
    using namespace owl::utils;
    struct element_tag {};
    using element_handle = handle<element_tag>;
  
    connected_components<element_handle> comps(10);
    CHECK(comps.num_components() == 10);
    CHECK(comps.num_elements() == 10);
    auto e1 = comps.element(1);
    auto e2 = comps.element(6);
    CHECK_FALSE(comps.same_component(e1,e2));
    auto c = comps.unite(e1, e2);
    CHECK(comps.same_component(e1,e2));
    CHECK(comps.num_components() == 9);
    CHECK(comps.num_elements(c) == 2);
  }
}
