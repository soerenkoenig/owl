#include "owl/utils/filtered_iterator.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "filtered_iterator", "[utils]" )
  {
    using namespace owl::utils;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7};
  
    auto is_even = [](int x){ return x % 2 == 0;};
    auto even_numbers = filter(is_even, numbers);
    CHECK(even_numbers.size() == 4);
    CHECK(std::all_of(even_numbers.begin(),even_numbers.end(), is_even));
  }
}
