#include "owl/utils/base64.hpp"
#include "catch/catch.hpp"


namespace test
{
  
  TEST_CASE( "utils", "[base64]" )
  {
    using namespace owl::utils;
    
    std::vector<unsigned char> bytes = {1,2,3,4,5,6,7,8,9};
        
    std::string encoded_string = base64_encode(bytes);
    CHECK(base64_decode(encoded_string) == bytes);
    
  }
}



