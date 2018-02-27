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
  
  }
}
