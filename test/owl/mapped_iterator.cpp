#include "owl/utils/mapped_iterator.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "mapped_iterator", "[utils]" )
  {
    using namespace owl::utils;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7};
  
    auto it = make_mapped_iterator(numbers.begin(),[](int x){ return x*x;});
  
    CHECK(*it == 0);
    CHECK(*(++it) == 1);
    CHECK(*(++it) == 4);
  }
}

