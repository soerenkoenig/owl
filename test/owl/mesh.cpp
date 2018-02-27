#include "owl/math/mesh.hpp"
#include "owl/math/physical_properties.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"


namespace test
{
  TEST_CASE( "primitives", "[math]" )
  {
    using namespace owl::math;
    physical_properties<float> prop;
  
  
    mesh<float> b = create_box<float>();
    CHECK(std::size(b.faces()) == 6);
    CHECK(std::size(b.vertices()) == 8);
    CHECK(std::size(b.edges()) == 12);
    CHECK(std::size(b.halfedges()) == 24);
    CHECK(b.is_quad_mesh());
    CHECK(b.is_closed());
  
    mesh<float> tet = create_tetradedron<float>();
    CHECK(std::size(tet.faces()) == 4);
    CHECK(std::size(tet.vertices()) == 4);
    CHECK(std::size(tet.edges()) == 6);
    CHECK(std::size(tet.halfedges()) == 12);
    CHECK(tet.is_triangle_mesh());
    CHECK(tet.is_closed());
  
  
  
    auto geo_sphere = create_geodesic_sphere<float>(2,2);
    CHECK(geo_sphere.num_faces() == 20*4*4);
  
    
  
  
  
    
  }
}
