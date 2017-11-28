//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <vector>
#include <algorithm>

#include "owl/utils/handle.hpp"

namespace owl
{
  namespace utils
  {
    class connected_components
    {
    public:
      ///N number of all elements
      connected_components(std::size_t N)
        : num_elems_(N), id(N), sz(N, 1), num_components_(N)
      {
        std::iota(id.begin(), id.end(), 0);
      
      }

      ///number of sets (initially number of all elements)
       std::size_t num_connected_components()
       {
         return num_components_;
       }

       //return the number of elements in the set which contains x
       std::size_t num_in_set(int x)
       {
        int l = find(x);
        return sz[l];
       }

       //returns label of the first set this can be used in combination with next_set to iterate over all sets
       int first_set()
       {
         int x =0;
         while(x < num_elems_ && x != id[x])
           x++;
         return x;
       }
    
       //returns the next set of x or -1 if x is the last one
       int next_set(int x)
       {
       
         x++;
         while(x <num_elems_ && x != id[x])
           x++;
         if(x == num_elems_)
           x= -1;
         return x;

       }

       ///return label number of element x
      std::size_t find(std::size_t x)
      {
        while(x != id[x])
        {
          id[x] = id[id[x]];
          x=id[x];
        }
        return x;
      }

    

      ///unite the set containing p with the set containing q (if p and q are in the same set, nothing is done)
      void unite(int p, int q)
      {
        auto i = find(p);
        auto j = find(q);
        if (i == j) return;
        if   (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
        else                 { id[j] = i; sz[i] += sz[j]; }
        num_components_--;
      }

      ///check wether p and q are in the same set
      bool find(std::size_t p, std::size_t q)
      {
        return find(p) == find(q);
      }
    
      std::vector<std::size_t> sz;
      std::vector<istd::size_t> id;
      std::size_t num_components_;
      std::size_t num_elems_;

    };
  }
}
