//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#define DEFINE_HAS_SIGNATURE(traitsName, funcName, signature)                   \
template <typename U>                                                           \
class traitsName                                                                \
{                                                                               \
private:                                                                        \
  template<typename T, T> struct helper;                                        \
  template<typename T> static std::uint8_t check(helper<signature, &funcName>*);\
  template<typename> static std::uint16_t check(...);                           \
public:                                                                         \
  static constexpr bool value = sizeof(check<U>(0)) == 1;                       \
}


#define DEFINE_HAS_MEMBER(traitsName, memberName, signature)                    \
template <typename U>                                                           \
struct traitsName                                                               \
{                                                                               \
private:                                                                        \
  template <typename T> static signature check(int);                            \
  template <typename> static void check(...);                                   \
public:                                                                         \
  enum { value = !std::is_void<decltype(check<U>(0))>::value };                 \
};


/*
 class test
 {
   using bar = int;
   void foo1(int i, bar b);
   static foo2(int i, bar b);
 };
 
 / static signature (*)
 DEFINE_HAS_SIGNATURE(has_static_foo, T::foo, void (*)(int, typename T::bar));
 
 // member signature (T::*)
 DEFINE_HAS_SIGNATURE(has_member_foo, T::foo, void (T::*)(int, typename T::bar));
 */


namespace owl
{
  template<typename T>
  struct identity
  {
    typedef T type;
  };
}
