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
    template <typename Iterator, typename Predicate>
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
    
      explicit filtered_iterator(const base_iterator_type &iter, const base_iterator_type& one_past_last,  predicate_type predicate)
        : _base(iter), _end(one_past_last), _predicate(predicate)
      {
        ensure_predicate();
      }
    
      filtered_iterator(base_iterator_type x, base_iterator_type end)
        : _base(x), _end(end)
      {
        ensure_predicate();
      }
  
      template<typename Iterator2, typename Predicate2>
      filtered_iterator(const filtered_iterator<Iterator2, Predicate2>& other)
        : _base(other._base), _end(other._end), _predicate(other._predicate)
      {
      }
  
      template<typename Iterator2, typename Predicate2>
      filtered_iterator& operator=(const filtered_iterator<Iterator, Predicate2>& other)
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
        return filtered_iterator(_end, _end, _predicate);
      }
  
      reference operator*() const
      {
        return *_base;
      }
  
      pointer operator->() const
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
  
    template <typename Iterator, typename Function>
    auto make_filtered_iterator(Iterator&& base, Iterator&& one_past_last, Function&& func)
    {
      return filtered_iterator<std::remove_reference_t<Iterator>, Function>(std::forward<Iterator>(base), std::forward<Iterator>(one_past_last), std::forward<Function>(func));
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

