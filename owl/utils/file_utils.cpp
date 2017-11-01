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
  
    std::string file_extension(const std::string& path)
    {
      std::size_t i = path.rfind('.', path.length());
      if (i != std::string::npos)
        return(path.substr(i+1, path.length() - i));
      return("");
    }
  
    std::streamsize file_size(const std::string& path)
    {
      std::ifstream file(path, std::ios::binary | std::ios::ate);
      std::streamsize size = file.tellg();
      return size;
    }
  
    std::string parent_path(const std::string& path)
    {
      size_t found = path.find_last_of("/\\");
      if(found == std::string::npos)
        return "";
  
      return path.substr(0,found);
    }
  }
}
