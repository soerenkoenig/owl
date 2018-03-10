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
#include <algorithm>
#include "owl/utils/iterator_range.hpp"

namespace owl
{
  namespace utils
  {
    template<typename Range, typename OutputIterator>
    inline OutputIterator copy(const Range& rng, OutputIterator out)
    {
      return std::copy(std::begin(rng),std::end(rng), out);
    }
  
    template<typename Range>
    inline Range& sort(Range& rng)
    {
      std::sort(std::begin(rng), std::end(rng));
      return rng;
    }
  
    template<typename Range, typename Pred>
    inline Range& sort(Range& rng, Pred&& less)
    {
      std::sort(std::begin(rng), std::end(rng), std::forward<Pred>(less));
      return rng;
    }
  
    template<typename Range, typename T>
    inline auto find(Range&& rng, const T& value)
    {
      return std::find(std::begin(std::forward<Range>(rng)), std::end(std::forward<Range>(rng)), value);
    }
  
    template<typename InputRange, typename OutIter, typename BinaryOperation>
    inline auto transform(InputRange&& rng, OutIter&& it, BinaryOperation&& binary_op)
    {
      return std::transform(std::begin(std::forward<InputRange>(rng)),
        std::end(std::forward<InputRange>(rng)),std::forward<OutIter>(it),
        std::forward<BinaryOperation>(binary_op));
    }
  
  }
}
