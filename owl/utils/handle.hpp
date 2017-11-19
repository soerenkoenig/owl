//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <limits>

namespace owl
{
  namespace utils
  {
    template <typename Tag, typename Index = std::size_t>
    class handle
    {
    public:
      using index_type = Index;
      
      constexpr explicit handle(const index_type& index = invalid())
        : index_{index}
      {
      }
      
      handle(const handle&) = default;
      handle(handle&&) = default;
      
      handle& operator=(const handle&) = default;
      handle& operator=(handle&&) = default;
      
      const std::size_t& index() const
      {
        return index_;
      }
      
      bool is_valid() const
      {
        return index_ != invalid();
      }
      
      void invalidate()
      {
        index_ = invalid();
      }
      
      bool operator==(const handle& other) const
      {
        return index_ == other._index;
      }
      
      bool operator!=(const handle& other) const
      {
        return index_ != other._index;
      }
      
      bool operator<(const handle& other) const
      {
        return index_ < other._index;
      }
      
      bool operator>(const handle& other) const
      {
        return  index_ > other._index;
      }
      
      bool operator<=(const handle& other) const
      {
        return index_ <= other._index;
      }
      
      bool operator>=(const handle& other) const
      {
        return  index_ >= other._index ;
      }
      
    private:
      constexpr static index_type invalid()
      {
        return std::numeric_limits<index_type>::max();
      }
      
      index_type index_;
    };

  }
}


namespace std
{
  template<typename Tag, typename Index>
  struct hash<owl::utils::handle<Tag,Index>>
  {
    std::size_t operator()(const owl::utils::handle<Tag, Index>& value) const
    {
      static hash<Index> hasher;
      return hasher(value.index());
    }
  };
}
