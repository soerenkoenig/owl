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
#include <type_traits>
#include "owl/utils/iterator_range.hpp"

namespace owl
{
  namespace utils
  {
    template <typename Predicate, typename Iterator>
    class mapped_iterator
    {
    public:
      using base_iterator_type = Iterator;
    
      using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

      using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    
      using value_type = decltype(std::declval<Predicate>()(*std::declval<Iterator>()));
      
      using pointer = void;
      
      using reference = value_type;
    
      using predicate_type = Predicate;
    
      mapped_iterator() = default;
    
     explicit mapped_iterator( const base_iterator_type &base)
        : _base(base)
      {
      }
    
      explicit mapped_iterator(predicate_type predicate, const base_iterator_type &base)
        : _base(base), _predicate(predicate)
      {
      }
      
      inline const base_iterator_type &base() const
      {
        return _base;
      }
      
      inline const predicate_type &predicate() const
      {
        return _predicate;
      }
      
      inline value_type operator*() const
      {
        return _predicate(*_base);
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
        return mapped_iterator(_predicate, _base + n);
      }
    
      mapped_iterator &operator+=(difference_type n)
      {
        _base += n;
        return *this;
      }
    
      mapped_iterator operator-(difference_type n) const
      {
        return mapped_iterator(_predicate, _base - n);
      }
    
      mapped_iterator &operator-=(difference_type n)
      {
        _base -= n;
        return *this;
      }
    
      value_type operator[](difference_type n) const
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
      predicate_type _predicate;
    };

    template <typename Predicate, typename Iterator>
    inline mapped_iterator<Predicate, Iterator>
    operator+(typename mapped_iterator<Predicate, Iterator>::difference_type n,
              const mapped_iterator<Predicate, Iterator> &rhs)
    {
      return mapped_iterator<Predicate,Iterator>(rhs.predicate(), rhs.base() + n);
    }

    template <typename Predicate, typename Iterator>
    inline mapped_iterator<Predicate,Iterator> make_mapped_iterator(Predicate&& predicate, Iterator&& iter)
    {
      return mapped_iterator<Predicate,Iterator>(std::forward<Predicate>(predicate), std::forward<Iterator>(iter));
    }
  
    template<typename Predicate, typename Iterator>
    auto map_range(Iterator&& first, Iterator&& one_past_last)
    {
      return
        make_iterator_range(make_mapped_iterator<Predicate>(std::forward<Iterator>(first)),
        make_mapped_iterator<Predicate>(std::forward<Iterator>(one_past_last)));
    }
  
    template<typename Predicate, typename Iterator>
    auto map_range(Predicate&& pred, Iterator&& first, Iterator&& one_past_last)
    {
      return
        make_iterator_range(
          make_mapped_iterator(std::forward<Predicate>(pred), std::forward<Iterator>(first)),
          make_mapped_iterator(std::forward<Predicate>(pred), std::forward<Iterator>(one_past_last)));
    }
  
    template<typename Predicate, typename Range, typename = std::enable_if_t<is_container<std::decay_t<Range>>::value>>
    auto map_range(Range&& range)
    {
      return map_range<Predicate>(std::begin(std::forward<Range>(range)),
       std::end(std::forward<Range>(range)));
    }

    template<typename Predicate, typename Range, typename = std::enable_if_t< is_container<std::decay_t<Range>>::value>>
    auto map_range(Predicate &&pred, Range&& range)
    {
      return  map_range(std::forward<Predicate>(pred),
        std::begin(std::forward<Range>(range)),
        std::end(std::forward<Range>(range)));
    }
  }
}

