#include "owl/utils/counting_iterator.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "counting_iterator", "[utils]" )
  {
    using namespace owl::utils;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7};
    auto numbers2 = make_counting_range(0, 8);
    CHECK(std::equal(numbers.begin(),numbers.end(), numbers2.begin(), numbers2.end()));
  }
}

