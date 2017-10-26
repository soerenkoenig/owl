#include "file_utils.hpp"

namespace owl
{
  namespace utils
  {
    bool file_exists(const std::string& path)
    {
      std::ifstream file(path);
      return static_cast<bool>(file);
    }
  
    std::streamsize file_size(const std::string& path)
    {
      std::ifstream file(path, std::ios::binary | std::ios::ate);
      std::streamsize size = file.tellg();
      return size;
    }
  }
}
