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
      
      using reference = void;
    
      using function_type = Predicate;
    
      mapped_iterator() = default;
    
     explicit mapped_iterator( const base_iterator_type &base)
        : base_(base)
      {
      }
    
      explicit mapped_iterator(function_type predicate, const base_iterator_type &base)
        : base_(base), function_(predicate)
      {
      }
      
      const base_iterator_type &base() const
      {
        return base_;
      }
      
      const function_type &predicate() const
      {
        return function_;
      }
      
      auto operator*() const
      {
        return function_(*base_);
      }
      
      mapped_iterator &operator++()
      {
        ++base_;
        return *this;
      }
    
      mapped_iterator &operator--()
      {
        --base_;
        return *this;
      }
    
      mapped_iterator operator++(int)
      {
        mapped_iterator tmp = *this;
        ++base_;
        return tmp;
      }
    
      mapped_iterator operator--(int)
      {
        mapped_iterator tmp = *this;
        --base_;
        return tmp;
      }
    
      mapped_iterator operator+(difference_type n) const
      {
        return mapped_iterator(function_, base_ + n);
      }
    
      mapped_iterator &operator+=(difference_type n)
      {
        base_ += n;
        return *this;
      }
    
      mapped_iterator operator-(difference_type n) const
      {
        return mapped_iterator(function_, base_ - n);
      }
    
      mapped_iterator &operator-=(difference_type n)
      {
        base_ -= n;
        return *this;
      }
    
      auto operator[](difference_type n) const
      {
        return *(*this + n);
      }
      
      bool operator==(const mapped_iterator &other) const
      {
        return base_ == other._base;
      }
    
      bool operator!=(const mapped_iterator &other) const
      {
        return !operator==(other);
      }
    
      bool operator<(const mapped_iterator &other) const
      {
        return base_ < other._base;
      }
      
      difference_type operator-(const mapped_iterator &other) const
      {
        return base_ - other.base;
      }
    
  private:
      base_iterator_type base_;
      function_type function_;
    };

    template <typename Predicate, typename Iterator>
    mapped_iterator<Predicate, Iterator>
    operator+(typename mapped_iterator<Predicate, Iterator>::difference_type n,
              const mapped_iterator<Predicate, Iterator> &rhs)
    {
      return mapped_iterator<Predicate,Iterator>(rhs.predicate(), rhs.base() + n);
    }

    template <typename Predicate, typename Iterator>
    mapped_iterator<Predicate,Iterator> make_mapped_iterator(Predicate&& predicate, Iterator&& iter)
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

