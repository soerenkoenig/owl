#include "owl/graphics/obj.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "obj", "[graphics]" )
  {
    owl::graphics::obj reader;
    CHECK(reader.read_obj("meshes/cube.obj"));
  }
}
