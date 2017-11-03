#include "owl/utils/map_iterator.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "map_iterator", "[utils]" )
  {
    using namespace owl::utils;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7};
  
    auto sqr = [](int x){ return x*x; };
    auto it = make_map_iterator(sqr, numbers.begin());
  
    CHECK(*it == 0);
    CHECK(*(++it) == 1);
    CHECK(*(++it) == 4);
  
    auto squared_numbers = map_range(sqr, numbers);
    int  x = squared_numbers[3];
    CHECK(squared_numbers[3] == 9);
  }
}

