
//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <vector>
#include <string>

namespace owl
{
  namespace utils
  {
    class buffer
    {
     
      buffer();
     
      buffer(size_t size);
     
      buffer(void *data, size_t size);
  
      buffer(const buffer &other);
  
      buffer(buffer &&other);

      buffer& operator=(const buffer &rhs);

      buffer&  operator=(buffer &&rhs);

      ~buffer();
      
      size_t  size() const { return size_; }
      
      void* data() { return data_; }
   
      const void* data() const { return data_; }

      void resize(std::size_t new_size);
      
      buffer sub_buffer(size_t offset, size_t length)
      {
        return buffer(data_ + offset, length);
      }
      
      bool is_owner() const
      {
        return is_owner_;
      }
  
   private:
    
      std::uint8_t*  data_;
      size_t size_;
      bool   is_owner_;
    };
  }
}

