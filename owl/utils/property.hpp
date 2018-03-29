//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include <functional>

namespace owl
{
  namespace utils
  {
    struct empty {};
  
    template<typename T, typename Get, typename Set = empty>
    class property
    {
      static constexpr bool readonly = std::is_same<Set,empty>::value;
    
    public:
      operator T() const
      {
        return get_();
      }
    
      property(const property&) = delete;
  
      template <typename T1,bool Dummy = true, typename = std::enable_if_t<Dummy && !readonly>>
      property& operator=(T1&& v)
      {
        set_(std::forward<T1>(v));
        return *this;
      }
    
      template <bool Dummy = true, typename = std::enable_if_t<Dummy && !readonly>>
      property(Get&& g, Set&& s)
        : get_(std::forward<Get>(g))
        , set_(std::forward<Set>(s))
      {}
    
      property(Get&& g)
        : get_(std::forward<Get>(g))
      {}
    
    private:
      Get get_;
      Set set_;
    };
  
    template<typename T, typename Get, typename Set>
    property<T, Get, Set> make_property(Get&& g, Set&& s)
    {
      return {std::forward<Get>(g), std::forward<Set>(s)};
    }
  
    template<typename T, typename Get>
    property<T,Get> make_property(Get&& g)
    {
      return {std::forward<Get>(g)};
    }
  }
}
