#include "owl/utils/uuid.hpp"

namespace owl
{
  namespace utils
  {
    std::ostream& operator<<(std::ostream& os,const uuid& guid)
    {
      
      os << std::uppercase;
      os.width(8);
      os << std::hex << guid.data1 << '-';
      
      os.width(4);
      os << std::hex << guid.data2 << '-';
      
      os.width(4);
      os << std::hex << guid.data3 << '-';
      
      os.width(2);
      os << std::hex
      << static_cast<short>(guid.data4[0])
      << static_cast<short>(guid.data4[1])
      << '-'
      << static_cast<short>(guid.data4[2])
      << static_cast<short>(guid.data4[3])
      << static_cast<short>(guid.data4[4])
      << static_cast<short>(guid.data4[5])
      << static_cast<short>(guid.data4[6])
      << static_cast<short>(guid.data4[7]);
      os << std::nouppercase;
      return os;
    }
  }
}
