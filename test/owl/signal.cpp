#include "owl/utils/signal.hpp"
#include "catch/catch.hpp"


namespace test
{
/*  class button
  {
  public:
    void press()
    {
        pressed(*this);
    }
  
    owl::utils::signal<void(const button& b)> pressed;
  
  };
  
  void logbutton(const button& b)
  {
  
  }
  TEST_CASE("signal", "[utils]")
  {
   button b;
 //  b.pressed.connect(logbutton);
  
  }

  */
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
  }
}



