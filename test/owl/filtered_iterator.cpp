#include "owl/utils/filtered_iterator.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "filtered_iterator", "[utils]" )
  {
    using namespace owl::utils;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7};
  
    auto it = make_filtered_iterator(numbers.begin(), numbers.end(),
      [](int x){ return x% 2 == 0; });
  }
}
