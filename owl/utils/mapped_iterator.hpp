//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

namespace owl
{
  namespace utils
  {
    template <class Iterator, class Function>
    class mapped_iterator
    {
      
    public:
      using iterator_category = typename std::iterator_traits<RootIt>::iterator_category;

      using difference_type = typename std::iterator_traits<RootIt>::difference_type
    
      using value_type = decltype(std::declval<Func>()(*std::declval<RootIt>()));
      
      using pointer = void;
      
      using reference = void;
      
      using iterator_type = Iterator;
      
      inline const iterator_type &base() const
      {
        return base;
      }
      
      inline const function_type &function() const
      {
        return function;
      }
      
      inline explicit mapped_iterator(const iterator_type &I, function_type func)
        : current(I), _func(func) {}
      
      inline value_type operator*() const
      {
        return Fn(*base);         
      }
      
      mapped_iterator &operator++() {
        ++current;
        return *this;
      }
      mapped_iterator &operator--() {
        --current;
        return *this;
      }
      mapped_iterator operator++(int) {
        mapped_iterator __tmp = *this;
        ++current;
        return __tmp;
      }
      mapped_iterator operator--(int) {
        mapped_iterator __tmp = *this;
        --current;
        return __tmp;
      }
      mapped_iterator operator+(difference_type n) const {
        return mapped_iterator(current + n, Fn);
      }
      mapped_iterator &operator+=(difference_type n) {
        current += n;
        return *this;
      }
      mapped_iterator operator-(difference_type n) const {
        return mapped_iterator(current - n, Fn);
      }
      mapped_iterator &operator-=(difference_type n) {
        current -= n;
        return *this;
      }
      reference operator[](difference_type n) const { return *(*this + n); }
      
      bool operator!=(const mapped_iterator &X) const
      {
        return !operator==(X);
        
      }
      
      bool operator==(const mapped_iterator &X) const
      {
        return current == X.current;
      }
      bool operator<(const mapped_iterator &X) const
      {
        return current < X.current;
        
      }
      
      difference_type operator-(const mapped_iterator &X) const
      {
        return base - X.current;
      }
      
      iterator_tye base;
      func_type func;
    };

    template <class Iterator, class Func>
    inline mapped_iterator<Iterator, Func>
    operator+(typename mapped_iterator<Iterator, Func>::difference_type N,
              const mapped_iterator<Iterator, Func> &X)
    {
      return mapped_iterator<Iterator, Func>(X.getCurrent() - N, X.getFunc());
    }


    // map_iterator - Provide a convenient way to create mapped_iterators, just like
    // make_pair is useful for creating pairs...
    //
    template <class ItTy, class FuncTy>
    inline mapped_iterator<ItTy, FuncTy> map_iterator(const ItTy &I, FuncTy F)
    {
      return mapped_iterator<ItTy, FuncTy>(I, F);
    }
    }
}

