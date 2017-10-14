//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <valarray>
#include <array>
#include <set>
#include <unordered_set>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <deque>
#include <string>




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
  DEFINE_HAS_MEMBER(has_const_iterator, T::const_iterator, typename T::const_iterator)
  DEFINE_HAS_SIGNATURE(has_begin, T::begin, typename T::const_iterator (T::*)() const);
  DEFINE_HAS_SIGNATURE(has_end, T::end, typename T::const_iterator (T::*)() const);
  DEFINE_HAS_SIGNATURE(has_resize, T::resize, void (T::*)(typename T::size_type));
  
  template <typename T>
  struct is_basic_string :  std::false_type {};

  template <typename... Ts>
  struct is_basic_string<std::basic_string<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_array :  std::false_type {};

  template <typename... Ts>
  struct is_array<std::array<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_vector :  std::false_type {};

  template <typename... Ts>
  struct is_vector<std::vector<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_list :  std::false_type {};

  template <typename... Ts>
  struct is_list<std::list<Ts...>> : std::true_type {};

  template <typename T>
  struct is_forward_list : std::false_type {};

  template <typename... Ts>
  struct is_forward_list<std::forward_list<Ts...>> : std::true_type {};

  template <typename T>
  struct is_deque : public std::false_type {};

  template <typename... Ts>
  struct is_deque<std::deque<Ts...>> : std::true_type {};

  template <typename T>
  struct is_map : public std::false_type {};

  template <typename... Ts>
  struct is_map<std::map<Ts...>> : std::true_type {};

  template <typename T>
  struct is_multimap : std::false_type {};

  template <typename... Ts>
  struct is_multimap<std::multimap<Ts...>> : std::true_type {};

  template <typename T>
  struct is_unordered_map : std::false_type {};

  template <typename... Ts>
  struct is_unordered_map<std::unordered_map<Ts...>> : std::true_type {};

  template <typename T>
  struct is_unordered_multimap : std::false_type {};

  template <typename... Ts>
  struct is_unordered_multimap<std::unordered_multimap<Ts...>>
  : public std::true_type {};

  template <typename T>
  struct is_set :  std::false_type {};

  template <typename... Ts>
  struct is_set<std::set<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_multiset :  std::false_type {};

  template <typename... Ts>
  struct is_multiset<std::multiset<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_unordered_set :  std::false_type {};

  template <typename... Ts>
  struct is_unordered_set<std::unordered_set<Ts...>> :  std::true_type {};

  template <typename T>
  struct is_unordered_multiset :  std::false_type {};

  template <typename... Ts>
  struct is_unordered_multiset<std::unordered_multiset<Ts...>>
  : std::true_type {};



  template <typename T>
  using is_continuous_container =
  std::conditional_t< is_array<T>::value || is_vector<T>::value || is_basic_string<T>::value,
  std::true_type, std::false_type>;


  template <typename T>
  using is_sequence_container =
  std::conditional_t<is_deque<T>::value || is_forward_list<T>::value || is_list<T>::value ||
  is_continuous_container<T>::value, std::true_type, std::false_type>;

  template <typename T>
  using is_unordered_associative_container = std::conditional_t<
  is_unordered_map<T>::value || is_unordered_multimap<T>::value ||
  is_unordered_set<T>::value || is_unordered_multiset<T>::value,
  std::true_type, std::false_type>;

  template <typename T>
  using is_ordered_associative_container =
  std::conditional_t<is_map<T>::value || is_multimap<T>::value ||
  is_set<T>::value || is_multiset<T>::value,
  std::true_type, std::false_type>;

  template <typename T>
  using is_associative_container =
  std::conditional_t<is_ordered_associative_container<T>::value ||
  is_unordered_associative_container<T>::value,
  std::true_type, std::false_type>;

  template <typename T>
  struct is_container : std::integral_constant<bool, has_begin<T>::value && has_end<T>::value> {};
  
  template <typename T, std::size_t N>
  struct is_container<T[N]> : std::true_type {};

  template <std::size_t N>
  struct is_container<char[N]> : std::false_type {};

  template <typename T>
  struct is_container<std::valarray<T>> : std::true_type {};
}
