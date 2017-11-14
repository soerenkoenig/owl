
#include "owl/utils/buffer.hpp"


//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//


namespace owl
{
  namespace utils
  {
    
    buffer::buffer()
      : data_(nullptr) , size_(0), is_owner_(false)
    {
    }
      
    buffer::buffer(void *data, size_t n)
    : data_(static_cast<std::uint8_t*>(data)), size_(n), is_owner_(false)
    {
    }
             
    buffer::buffer(size_t n)
      : data_(static_cast<std::uint8_t*>(malloc(n))), size_(n), is_owner_(true)
    {
    }
             
    buffer::buffer(const buffer &other)
      : data_(static_cast<std::uint8_t*>(malloc(other.size_))), size_(other.size_), is_owner_(true)
    {
      memcpy(data_, other.data_, other.size_);
    }
    
    buffer::buffer(buffer &&other)
      : data_(other.data_), size_(other.size_), is_owner_(other.is_owner_)
    {
      other.is_owner_ = false;
    }
             
    buffer&  buffer::operator=(const buffer &other)
    {
      size_ = other.size_;
      data_ = static_cast<std::uint8_t*>(malloc(size_));
      memcpy( data_, other.data_, size_ );

      is_owner_ = true;

      return *this;
    }
             
    buffer&  buffer::operator=(buffer &&other)
    {
      data_ = other.data_;
      size_ = other.size_;
      is_owner_ = other.is_owner_;
      other.is_owner_ = false;

      return *this;
    }
      
    buffer::~buffer()
    {
      if(is_owner_)
        free(data_);
    }
    
    void buffer::resize(size_t new_size)
    {
      if(is_owner_)
        data_ = static_cast<std::uint8_t*>(realloc(data_, new_size));
      else
      {
        std::uint8_t *data_new = static_cast<std::uint8_t*>(malloc(new_size));
        memcpy(data_new, data_, size_);
        data_ = data_new;
        is_owner_ = true;
      }
      
      size_ = new_size;
    }
    
  }
}


