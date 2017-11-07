#include "owl/graphics/image.hpp"
#include "catch/catch.hpp"


namespace test
{

void writer(void *context, void *data, int size)
{
  std::vector<unsigned char>& buffer = *reinterpret_cast<std::vector<unsigned char>*>(context);
  unsigned char* beg = static_cast<unsigned char*>(data);
  unsigned char* end = static_cast<unsigned char*>(data)+size;
  buffer.insert(buffer.end(), beg, end);
}

  TEST_CASE( "image", "[graphics]" )
  {
    using namespace owl::graphics;
    using namespace owl::utils;
    std::string path = "images/owl.png";
  
  
    image<unsigned char> img(path);
    
    
    CHECK(img.width() == 512);
    CHECK(img.height() == 512);
    CHECK(img.depth() == 3);
  /*
  
    std::vector<unsigned char> buffer2;
    stbi_write_jpg_to_func(&writer,&buffer2,w,h,comp,image,96);
    CHECK(write_file("images/owl.jpg",buffer2));
    stbi_image_free(image);*/
  
  }
}


