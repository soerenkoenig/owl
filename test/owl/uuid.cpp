#include "owl/utils/uuid.hpp"
#include "catch/catch.hpp"

namespace test
{
  TEST_CASE( "uuid", "[utils]" )
  {
    using namespace owl::utils;
    uuid uid1 = random_uuid();
    uuid uid2 = random_uuid();
    std::cout << uid1 << std::endl;
    std::cout << uid2 << std::endl;
  
    std::cout << uuid{} << std::endl;
    CHECK(uid1 != uid2);
    CHECK(uid1.variant() == uuid::variant_rfc_4122);
    CHECK(uid1.version() == uuid::version_random_number_based);
  }
}
