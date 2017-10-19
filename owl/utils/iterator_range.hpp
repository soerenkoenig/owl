//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <utility>
#include <iterator>
#include "owl/utils/container_utils.hpp"

namespace owl
{
  namespace utils
  {
    template< typename Iterator >
    class iterator_range
    {
    public:
      typedef Iterator   iterator;
      typedef Iterator   const_iterator;
      typedef typename std::iterator_traits<iterator>::difference_type difference_type;
      typedef typename std::iterator_traits<iterator>::value_type value_type;
      typedef typename std::iterator_traits<iterator>::reference reference;
  
      template<typename Iterator2>
      iterator_range( Iterator2 first, Iterator2 one_past_last )
        : _first(first), _one_past_last(one_past_last)
      {
      }
  
      template<typename Range>
      iterator_range(Range& r)
        : _first(std::begin(r)), _one_past_last(std::end(r))
      {
      }
  
      template<typename Range>
      iterator_range(const Range& r)
        : _first(std::begin(r)), _one_past_last(std::end(r))
      {
      }
  
      template<typename Range>
      iterator_range& operator=(Range& r)
      {
        if(this == &r)
          return *this;
        _first = std::begin(r);
        _one_past_last = std::end(r);
        return *this;
      }
  
      template<typename Range>
      iterator_range& operator=(const Range& r)
      {
        if(this == &r)
          return *this;
        _first = std::begin(r);
        _one_past_last = std::end(r);
        return *this;
      }
  
      iterator begin() const
      {
        return _first;
      }
  
      iterator end() const
      {
        return _one_past_last;
      }
  
      explicit operator bool() const
      {
        return !empty();
      }
  
      bool equal(const iterator_range& r) const
      {
        return begin() == std::begin(r) && end() == std::end(r);
      }
  
      auto front() const
      {
        return *_first;
      }
  
      void drop_front()
      {
        ++_first;
      }
  
      void drop_front(difference_type n)
      {
        advance_begin(n);
      }
  
      bool empty() const
      {
        return _first == _one_past_last;
      }
  
      iterator_range& advance_begin(difference_type n)
      {
        std::advance(_first, n);
        return *this;
      }
  
      iterator_range& advance_end(difference_type n)
      {
        std::advance(_one_past_last, n);
        return *this;
      }
  
      auto back() const
      {
        return *(--end());
      }
  
      void drop_back()
      {
        --_one_past_last;
      }
  
      void drop_back(difference_type n)
      {
        advance_end(-n);
      }
  
      reference operator[]( difference_type at ) const
      {
        return _first[at];
      }
  
      value_type operator()(difference_type at ) const
      {
        auto it = _first;
        std::advance(it,at);
        return *it;
      }
  
      difference_type size() const
      {
        return std::distance(_first,_one_past_last);
      }
    
    private:
      iterator _first;
      iterator _one_past_last;
    };
  
    template<typename Iterator, typename Iterator2>
    bool operator==( const iterator_range<Iterator>& l, const iterator_range<Iterator2>& r)
    {
      return l.size() != r.size() ? false : std::equal(std::begin(l), std::end(l), std::begin(r));
    }
  
    template<typename Iterator, typename Range>
    bool operator==( const iterator_range<Iterator>& l, const Range& r)
    {
      return l.size() != r.size() ? false : std::equal(std::begin(l), std::end(l), std::begin(r));
    }
  
    template<typename Iterator, typename Range>
    bool operator==( const Range& l, const iterator_range<Iterator>& r)
    {
      return l.size() != r.size() ? false : std::equal(std::begin(l), std::end(l), std::begin(r));
    }
  
    template<typename Iterator, typename Iterator2>
    bool operator!=(const iterator_range<Iterator>& l, const iterator_range<Iterator2>& r)
    {
      return !(l == r);
    }
  
    template<typename Iterator, typename Range>
    bool operator!=(const iterator_range<Iterator>& l, const Range& r)
    {
      return !(l == r);
    }
  
    template<typename Iterator, typename Range>
    bool operator!=(const Range& l, const iterator_range<Iterator>& r)
    {
      return !(l == r);
    }
  
    template<typename Iterator, typename Iterator2>
    bool operator<(const iterator_range<Iterator>& l, const iterator_range<Iterator2>& r)
    {
      return std::lexicographical_compare(std::begin(l), std::end(l), std::begin(r), std::end(r));
    }
  
    template<typename Iterator, typename Range>
    bool operator<(const iterator_range<Iterator>& l, const Range& r)
    {
      return std::lexicographical_compare(std::begin(l), std::end(l), std::begin(r), std::end(r));
    }
  
    template<typename Iterator, typename Range>
    bool operator<(const Range& l, const iterator_range<Iterator>& r)
    {
      return std::lexicographical_compare(std::begin(l), std::end(l), std::begin(r), std::end(r));
    }
  
    template<typename Iterator>
    iterator_range<Iterator> make_iterator_range(Iterator first, Iterator one_past_last)
    {
      return iterator_range<Iterator>(first, one_past_last);
    }
  
    template<typename Iterator, typename Integer>
    iterator_range<Iterator> make_iterator_range_n(Iterator first, Integer n)
    {
      auto one_past_last = first;
      std::advance(one_past_last, n);
      return iterator_range<Iterator>(first, one_past_last);
    }
  
    template<typename Range>
    iterator_range<typename container_traits<Range>::iterator> make_iterator_range(Range& r)
    {
      return iterator_range<typename container_traits<Range>::iterator>(std::begin(r), std::end(r));
    }
  
    template<typename Range>
    iterator_range<typename container_traits<Range>::const_iterator> make_iterator_range(const Range& r)
    {
      return iterator_range<typename container_traits<Range>::const_iterator>(r);
    }
  
    template<typename Range>
    iterator_range<typename container_traits<Range>::iterator> make_iterator_range(Range& r,
      typename container_traits<Range>::difference_type advance_begin,
      typename container_traits<Range>::difference_type advance_end)
    {
      auto res = iterator_range<typename container_traits<Range>::iterator>(r);
      res.advance_begin(advance_begin);
      res.advance_end(advance_end);
      return res;
    }
  
    template<typename Range>
    iterator_range<typename container_traits<const Range>::const_iterator > make_iterator_range(const Range& r,
      typename container_traits<const Range>::difference_type advance_begin,
      typename container_traits<const Range>::difference_type advance_end)
    {
      auto res = iterator_range<typename container_traits< Range>::const_iterator>(r);
      res.advance_begin(advance_begin);
      res.advacne_end(advance_end);
      return res;
    }
  
    template<typename Sequence, typename Range>
    Sequence copy_range(const Range& r)
    {
      return Sequence(std::begin(r), std::end(r));
    }
  }
}

