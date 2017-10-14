#include <sstream>

#include "owl/binary_serialization.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE("template_utils", "[]" )
  {
    CHECK((owl::is_one_of<int, float, double, int>()));
    CHECK_FALSE((owl::is_one_of<int, float, double>()));
  }
}
