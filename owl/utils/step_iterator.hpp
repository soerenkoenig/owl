//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <iterator>
#include <algorithm>
#include <type_traits>

namespace owl
{
  namespace utils
  {
    template <typename Iterator>
    using is_random_access_iterator = std::conditional_t<std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value,
      std::true_type, std::false_type>;
    
    /**
     An iterator adapter class which modifies the step length of its internal iterator.
     Step is the number of steps applied to the internal iterator
     */
    template<typename Iterator, std::size_t StepSize>
    class step_iterator
    {
      static_assert(is_random_access_iterator<Iterator>::value, "step_iterator only supports random access iterators");

    public:
      using base_iterator_type = Iterator;
      using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
      using value_type = typename std::iterator_traits<Iterator>::value_type;
      using difference_type = typename std::iterator_traits<Iterator>::difference_type;
      using pointer = typename std::iterator_traits<Iterator>::pointer;
      using reference = typename std::iterator_traits<Iterator>::reference;
      using size_type = std::size_t;
  
      constexpr static size_type step_size()
      {
        return StepSize;
      }
    
      step_iterator() = default;
    
      explicit step_iterator(base_iterator_type it)
        : _current(it)
      {
      }
  
      template< typename U, std::size_t Step2>
      step_iterator( const step_iterator<U, Step2>& other)
        : _current(other._current)
      {
      }
  
      template< typename U, std::size_t Step2>
      step_iterator& operator=(const step_iterator<U, Step2>& other)
      {
        if(this == &other)
          return *this;
        _current = other._current;
        return *this;
      }
    
      template< typename U, std::size_t Step2>
      step_iterator& operator=(Iterator it)
      {
        _current = it;
        return *this;
      }
  
      Iterator base() const
      {
        return _current;
      }
  
      reference operator*() const
      {
        return *_current;
      }
  
      pointer operator->() const
      {
        std::addressof(operator*());
      }
  
      reference operator[](difference_type n) const
      {
        auto it = *this;
        std::advance(it, n);
        return *it;
      }
  
      step_iterator& operator++()
      {
        std::advance(_current, step_size());
        return *this;
      }
    
      step_iterator& operator--()
      {
        std::advance(_current, -step_size());
        return *this;
      }
  
      step_iterator operator++(int)
      {
        auto tmp = *this;
        operator++();
        return tmp;
      }
  
      step_iterator operator--(int)
      {
        auto tmp = *this;
        operator--();
        return tmp;
      }
    
      step_iterator& operator+=(difference_type n)
      {
        std::advance(_current, step_size()*n);
        return *this;
      }
  
      step_iterator& operator-=(difference_type n)
      {
        std::advance(_current, -step_size()*n);
        return *this;
      }
  
      step_iterator operator+(difference_type n) const
      {
        auto it = *this;
        it += n;
        return it;
      }
  
      step_iterator operator-(difference_type n) const
      {
        auto it = *this;
        it -= n;
        return it;
      }
    
    private:
      iterator_type _current;
    };
  
    template< typename Iterator, std::size_t Step >
    step_iterator<Iterator,Step> operator+(typename step_iterator<Iterator, Step>::difference_type n,
      const step_iterator<Iterator, Step>& it)
    {
      auto ret = it;
      ret += n;
      return ret;
    }
  
    template< typename Iterator, std::size_t Step >
    typename step_iterator<Iterator,Step>::difference_type operator-(const step_iterator<Iterator, Step>& lhs,
       const step_iterator<Iterator,Step>& rhs)
    {
      return std::distance(lhs.base(),rhs.base()) / lhs.stepsize();
    }
  
    template< typename Iterator1, typename Iterator2, std::size_t Step >
    bool operator==(const step_iterator<Iterator1,Step>& lhs, const step_iterator<Iterator2,Step>& rhs)
    {
      return lhs.base() == rhs.base();
    }
  
    template< typename Iterator1, typename Iterator2, std::size_t Step >
    bool operator!=(const step_iterator<Iterator1, Step>& lhs, const step_iterator<Iterator2, Step>& rhs)
    {
      return lhs.base() != rhs.base();
    }
  
    template<typename Iterator1, typename Iterator2, std::size_t Step >
    bool operator<( const step_iterator<Iterator1, Step>& lhs, const step_iterator<Iterator2, Step>& rhs )
    {
      if(Step > 0)
        return lhs.base() < rhs.base();
      else
        return lhs.base() > rhs.base();
    }
  
    template<typename Iterator1, typename Iterator2, std::size_t Step>
    bool operator<=( const step_iterator<Iterator1,Step>& lhs, const step_iterator<Iterator2,Step>& rhs )
    {
      if(Step > 0)
        return lhs.base() <= rhs.base();
      else
        return lhs.base() >= rhs.base();
    }
  
    template<typename Iterator1, typename Iterator2, std::size_t Step>
    bool operator>( const step_iterator<Iterator1,Step>& lhs, const step_iterator<Iterator2,Step>& rhs )
    {
      if(Step > 0)
        return lhs.base() > rhs.base();
      else
        return lhs.base() < rhs.base();
    }
  
    template<typename Iterator1, typename Iterator2, std::size_t Step>
    bool operator>=( const step_iterator<Iterator1,Step>& lhs, const step_iterator<Iterator2,Step>& rhs )
    {
      if(Step > 0)
        return lhs.base() >= rhs.base();
      else
        return lhs.base() <= rhs.base();
    }
  }
}
