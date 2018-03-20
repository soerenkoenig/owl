#include "owl/math/mesh.hpp"
#include "owl/io/ply.hpp"
#include "owl/math/physical_properties.hpp"
#include "owl/math/approx.hpp"
#include "catch/catch.hpp"


namespace test
{


TEST_CASE( "add_face_s", "[math]" )
  {
    using namespace owl::math;
    mesh<float> m;
    auto verts = m.add_vertices(7);
    auto f0 = m.add_face(verts[1], verts[2], verts[0]);
    auto f1 = m.add_face(verts[6], verts[0], verts[5]);
    auto f2 = m.add_face(verts[0], verts[3], verts[4]);
  
    auto f3 = m.add_face(verts[5], verts[0], verts[4]);
  
    auto f4 = m.add_face(verts[2], verts[3], verts[0]);
    CHECK(check_mesh(m) == 0);
 /*  for(auto he : m.halfedges())
    {
      std::cout << "he: "<<he << ": target(he) = " << m.target(he) <<", origin(he) = "<<m.origin(he) << ", next(he) = "<<((const mesh<float>&)m).next(he)<<std::endl;
    }*/
  }

  TEST_CASE( "add_face3", "[math]" )
  {
    using namespace owl::math;
    mesh<float> m;
    owl::io::read_ply(m,"/Users/skoenig/Downloads/bun_zipper.ply");
    CHECK(check_mesh(m) == 0);
  }
  
  TEST_CASE( "add_face4", "[math]" )
  {
    using namespace owl::math;
    mesh<float> m;
  
    owl::io::read_ply(m,"test.ply");
    CHECK(m.num_faces() == 6);
    check_mesh(m);
  }
  
  TEST_CASE( "add_face", "[math]" )
  {
    using namespace owl::math;
    mesh<float> m;
    auto verts = m.add_vertices(10);
    auto f0 = m.add_face(verts[0], verts[1], verts[2]);
    auto f1 = m.add_face(verts[3], verts[4], verts[5]);
    auto f2 = m.add_face(verts[6], verts[7], verts[8]);
    auto f3 = m.add_face(verts[0], verts[3], verts[6]);
    auto f4 = m.add_face(verts[0], verts[6], verts[8]);
    auto f5 = m.add_face(verts[2], verts[4], verts[3], verts[0]);
    CHECK(m.num_faces() == 6);
    check_mesh(m);
  }
  
  
  TEST_CASE( "add_face2", "[math]" )
  {
    using namespace owl::math;
    mesh<float> m;
    auto verts = m.add_vertices(6);
    auto f0 = m.add_face(verts[0], verts[1], verts[2]);
    auto f1 = m.add_face(verts[1], verts[3], verts[4]);
    auto f2 = m.add_face(verts[2], verts[4], verts[5]);
    auto f3 = m.add_face(verts[1], verts[4], verts[2]);
 
    CHECK(m.num_faces() == 4);
    check_mesh(m);
  }
  

  TEST_CASE( "primitives", "[math]" )
  {
    using namespace owl::math;
    physical_properties<float> prop;
  
  
    mesh<float> b = create_box<float>();
    mesh<float> b2 = b;
    CHECK(b.num_faces() == 6);
    CHECK(b.num_vertices() == 8);
    CHECK(b.num_edges() == 12);
    CHECK(b.num_halfedges() == 24);
    CHECK(b.is_quad_mesh());
    CHECK(b.is_closed());
  
    mesh<float> tet = create_tetradedron<float>();
    CHECK(tet.num_faces() == 4);
    CHECK(tet.num_vertices() == 4);
    CHECK(tet.num_edges() == 6);
    CHECK(tet.is_triangle_mesh());
    CHECK(tet.is_closed());
  
    auto ico = create_icosaeder<float>();
    CHECK(check_mesh(ico) == 0);
    CHECK(ico.num_vertices() == 12);
    CHECK(ico.num_faces() == 20);
    CHECK(ico.num_edges() == 30);
    CHECK(ico.is_closed());
  
    auto geo_sphere = create_geodesic_sphere<float>(2, 2);
    CHECK(geo_sphere.num_faces() == 20 * 4 * 4);
    CHECK(geo_sphere.is_closed());
  
    auto sph = create_sphere<float>(2);
    CHECK(sph.num_faces() == 48 * 48);
    CHECK(sph.num_vertices() == 2258);
    CHECK(sph.num_edges() == 4560);
    CHECK(sph.is_closed());
  
    auto cylinder = create_cylinder<float>(1, 2, 48, 48);
    CHECK(cylinder.num_faces() == 2400);
    CHECK(cylinder.num_vertices() == 2354);
    CHECK(cylinder.num_edges() == 4752);
    CHECK(cylinder.is_closed());
  
    auto torus = create_torus<float>(1, 2, 48, 48);
    CHECK(torus.num_faces() == 48 * 48);
    CHECK(torus.num_vertices() == 48 * 48);
    CHECK(torus.num_edges() == 4608);
    CHECK(torus.is_closed());
    CHECK(torus.is_quad_mesh());
   
    auto octaeder = create_octaeder<float>(1);
    CHECK(octaeder.num_faces() == 8);
    CHECK(octaeder.num_vertices() == 6);
    CHECK(octaeder.num_edges() == 12);
    CHECK(octaeder.is_closed());
    CHECK(octaeder.is_triangle_mesh());
  
    auto disc = create_disk<float>(1, 48);
    CHECK(disc.num_faces() == 48);
    CHECK(disc.num_vertices() == 48 + 1);
    CHECK(disc.num_edges() == 2 * 48);
    CHECK(disc.is_open());
    CHECK(disc.is_triangle_mesh());
  
  
  
  }
}
