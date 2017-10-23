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

namespace owl
{
  namespace utils
  {
    template <typename Iterator, typename Function>
    class mapped_iterator
    {
    public:
      using base_iterator_type = Iterator;
    
      using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

      using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    
      using value_type = decltype(std::declval<Function>()(*std::declval<Iterator>()));
      
      using pointer = void;
      
      using reference = void;
    
      using function_type = Function;
    
      inline explicit mapped_iterator(const base_iterator_type &base, function_type function)
        : _base(base), _function(function)
      {
      }
      
      inline const base_iterator_type &base() const
      {
        return _base;
      }
      
      inline const function_type &function() const
      {
        return _function;
      }
      
      inline value_type operator*() const
      {
        return _function(*_base);
      }
      
      mapped_iterator &operator++()
      {
        ++_base;
        return *this;
      }
    
      mapped_iterator &operator--()
      {
        --_base;
        return *this;
      }
    
      mapped_iterator operator++(int)
      {
        mapped_iterator tmp = *this;
        ++_base;
        return tmp;
      }
    
      mapped_iterator operator--(int)
      {
        mapped_iterator tmp = *this;
        --_base;
        return tmp;
      }
    
      mapped_iterator operator+(difference_type n) const
      {
        return mapped_iterator(_base + n, _function);
      }
    
      mapped_iterator &operator+=(difference_type n)
      {
        _base += n;
        return *this;
      }
    
      mapped_iterator operator-(difference_type n) const
      {
        return mapped_iterator(_base - n, _function);
      }
    
      mapped_iterator &operator-=(difference_type n)
      {
        _base -= n;
        return *this;
      }
    
      reference operator[](difference_type n) const
      {
        return *(*this + n);
      }
      
      bool operator==(const mapped_iterator &other) const
      {
        return _base == other._base;
      }
    
      bool operator!=(const mapped_iterator &other) const
      {
        return !operator==(other);
      }
    
      bool operator<(const mapped_iterator &other) const
      {
        return _base < other._base;
      }
      
      difference_type operator-(const mapped_iterator &other) const
      {
        return _base - other.base;
      }
    
  private:
      base_iterator_type _base;
      function_type _function;
    };

    template <typename Iterator, typename Func>
    inline mapped_iterator<Iterator, Func>
    operator+(typename mapped_iterator<Iterator, Func>::difference_type n,
              const mapped_iterator<Iterator, Func> &rhs)
    {
      return mapped_iterator<Iterator, Func>(rhs.base() + n, rhs.function());
    }

    template <typename Iterator, typename Function>
    inline mapped_iterator<Iterator, Function> make_mapped_iterator(const Iterator &iter, Function func)
    {
      return mapped_iterator<Iterator, Function>(iter, std::forward<Function>(func));
    }
  }
}

