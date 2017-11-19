#include "owl/utils/handle.hpp"
#include "catch/catch.hpp"

#include <unordered_map>


namespace test
{
  class test_handle : public owl::utils::handle<> { using handle<>::handle; };
  
  TEST_CASE( "handle", "[utils]" )
  {
    using namespace owl::utils;
    
    test_handle h;
    CHECK_FALSE(h.is_valid());
    std::hash<test_handle> hasher;
    
   // std::unordered_map<test_handle,int> mymap;
    
  }
}




