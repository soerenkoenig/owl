#include "owl/utils/signal.hpp"
#include "catch/catch.hpp"


namespace test
{

  TEST_CASE( "combiner", "[utils]" )
  {
    using namespace owl::utils;
    {
      combiner_last<int> c;
      CHECK(c(3));
      CHECK(c.get() == 3);
      CHECK(c(4));
      CHECK(c.get() == 4);
    }
  
    {
      combiner_vector<int> c;
      CHECK(c(3));
      CHECK(c.get().size() == 1);
      CHECK(c.get()[0] == 3);
      CHECK(c(4));
      CHECK(c.get().size() == 2);
      CHECK(c.get()[1] == 4);
    }
    
    signal<int(int x, int y)> sig;
    {
      scoped_connection con = sig.connect([](int x, int y){ std::cout << "xy" << std::endl; return x;});
      CHECK(sig(1,2) == 1);
      CHECK(sig(2,2) == 2);
    }
    sig(3,4);
    
  }
}



