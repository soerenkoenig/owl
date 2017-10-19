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

namespace owl
{
  namespace utils
  {
    template<typename Iterator, std::size_t Step>
    class step_iterator
      : public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
          typename std::iterator_traits<Iterator>::value_type,
          typename std::iterator_traits<Iterator>::difference_type,
          typename std::iterator_traits<Iterator>::pointer,
          typename std::iterator_traits<Iterator>::reference>
    {
    public:
        typedef Iterator iterator_type;
        typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;
        typedef typename std::iterator_traits<Iterator>::reference reference;
        using size_type = std::size_t;
    
        constexpr static size_type step_size()
        {
          return Step;
        }
    
        step_iterator()
        {
        }
    
        explicit step_iterator( Iterator it)
          : _current(it)
        {
        
        }
    
        template< typename U, std::size_t S2>
        step_iterator( const step_iterator<U, S2>& other)
          : _current(other._current)
        {
        }
    
        template< typename U, std::size_t S2>
        step_iterator& operator=(const step_iterator<U, S2>& other)
        {
          if(this == &other)
            return *this;
          _current = other._current;
          return *this;
        }
    
        template< typename U, std::size_t S2>
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
    
      Iterator _current;
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
