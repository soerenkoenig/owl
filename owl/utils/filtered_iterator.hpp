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

#include "owl/utils/iterator_range.hpp"

namespace owl
{
  namespace utils
  {
    template <typename Predicate, typename Iterator>
    class filtered_iterator
    {
    public:
      using base_iterator_type = Iterator;
      using predicate_type = Predicate;
      using iterator_category = typename std::forward_iterator_tag;
      using value_type = typename std::iterator_traits<Iterator>::value_type;
      using difference_type = typename std::iterator_traits<Iterator>::difference_type;
      using pointer = typename std::iterator_traits<Iterator>::pointer;
      using reference = typename std::iterator_traits<Iterator>::reference;
      using size_type = std::size_t;
    
      filtered_iterator() = default;
    
      explicit filtered_iterator(predicate_type predicate,
        const base_iterator_type &iter, const base_iterator_type& end)
        : _base(iter), _end(end), _predicate(predicate)
      {
        ensure_predicate();
      }
    
      filtered_iterator(base_iterator_type base, base_iterator_type end)
        : _base(base), _end(end)
      {
        ensure_predicate();
      }
  
      template<typename Predicate2, typename Iterator2>
      filtered_iterator(const filtered_iterator<Predicate2, Iterator2>& other)
        : _base(other._base), _end(other._end), _predicate(other._predicate)
      {
      }
  
      template<typename Predicate2, typename Iterator2>
      filtered_iterator& operator=(const filtered_iterator<Predicate2, Iterator2>& other)
      {
        if(this == &other)
          return *this;
        _base = other._base;
        _end = other._end;
        _predicate = other._predicate;
        return *this;
      }
    
      inline const predicate_type& predicate() const
      {
        return _predicate;
      }
  
      inline const base_iterator_type& base() const
      {
        return _base;
      }
    
      filtered_iterator end() const
      {
        return filtered_iterator(_predicate, _end, _end);
      }
  
      auto operator*() const
      {
        return *_base;
      }
  
      auto operator->() const
      {
        std::addressof(operator*());
      }
    
      filtered_iterator& operator++()
      {
        if (_base == _end)
          return *this;
        ++_base;
        ensure_predicate();
        return *this;
      }

      filtered_iterator operator++(int)
      {
        filtered_iterator temp(*this);
        this->operator++();
        return temp;
      }

      bool operator==(const filtered_iterator& rhs) const
      {
        return _base == rhs._base;
      }

      bool operator!=(const filtered_iterator& rhs) const
      {
        return _base != rhs._base;
      }
  
    private:
      void ensure_predicate()
      {
        while (_base != _end && !_predicate(*_base))
          ++_base;
      }
    
      predicate_type _predicate;
      base_iterator_type _base;
      base_iterator_type _end;
    };
  
  
    template <class Predicate, class Iterator>
    filtered_iterator<Predicate, Iterator>
    make_filtered_iterator(Predicate&& f, Iterator&& x, Iterator&& end)
    {
      return filtered_iterator<Predicate, Iterator>(std::forward<Predicate>(f),
        std::forward<Iterator>(x),std::forward<Iterator>(end));
    }

    template<typename Predicate, typename Iterator>
    auto filter(Iterator&& first, Iterator&& one_past_last)
    {
      auto f = make_filtered_iterator<Predicate>(std::forward<Iterator>(first),
        std::forward<Iterator>(one_past_last));
      return make_iterator_range(f,f.end());
    }
  
    template<typename Predicate, typename Range, typename = std::enable_if_t<is_container<std::decay_t<Range>>::value>>
    auto filter(Range&& range)
    {
      auto f = make_filtered_iterator<Predicate>(std::begin(range), std::end(range));
      return make_iterator_range(f, f.end());
    }

    template<typename Predicate, typename Range, typename = std::enable_if_t< is_container<std::decay_t<Range>>::value>>
    auto filter(Predicate &&pred, Range&& range)
    {
      auto f = make_filtered_iterator(std::forward<Predicate>(pred),
        std::begin(range), std::end(range));
      return make_iterator_range(f, f.end());
    }

  /*
    template<typename Iterator1, typename Iterator2, std::size_t StepSize>
    bool operator==(const filtered_iterator<Iterator1, StepSize>& lhs,
      const step_iterator<Iterator2, StepSize>& rhs)
    {
      return lhs.base() == rhs.base();
    }
  
    template<typename Iterator1, typename Iterator2, std::size_t StepSize>
    bool operator!=(const step_iterator<Iterator1, StepSize>& lhs,
      const step_iterator<Iterator2, StepSize>& rhs)
    {
      return lhs.base() != rhs.base();
    }
 
    template<typename Iterator, std::size_t StepSize>
    bool operator==(const Iterator& lhs, const step_iterator<Iterator, StepSize>& rhs)
    {
      return lhs == rhs.base();
    }
  
    template<typename Iterator, std::size_t StepSize>
    bool operator!=(const Iterator& lhs, const step_iterator<Iterator, StepSize>& rhs)
    {
      return lhs != rhs.base();
    }
  
    template<typename Iterator, std::size_t StepSize>
    bool operator==(const step_iterator<Iterator, StepSize>& lhs,
      const Iterator& rhs)
    {
      return lhs.base() == rhs;
    }
  
    template<typename Iterator, std::size_t StepSize>
    bool operator!=(const step_iterator<Iterator, StepSize>& lhs,
      const Iterator& rhs)
    {
      return lhs.base() != rhs;
    }
   
  */
  }
}
