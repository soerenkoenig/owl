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
#include <cassert>
#include <algorithm>
#include <numeric>
#include "owl/export.hpp"
#include "owl/utils/handle.hpp"
#include "owl/utils/count_iterator.hpp"


namespace owl
{
  namespace utils
  {

    class connected_components
    {
      struct node
      {
        std::size_t id;
        std::size_t count;
      };
    
    public:
    
      struct component_tag{};
      using component_handle = owl::utils::handle<component_tag>;
   
      struct element_tag{};
      using element_handle = owl::utils::handle<element_tag>;
    
      struct const_iterator
      {
        // these typedefs are needed if you want to be STL compatible
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::size_t;
        using pointer = void;
        using reference = void;
        using size_type =  std::size_t;
        using difference_type = std::ptrdiff_t ;

        const_iterator() = default;
      
        const_iterator(const connected_components* comp, std::size_t current)
          : connected_components_(comp)
          , current_(current)
        {}
      
        component_handle operator*() const
        {
          return current_;
        }
  
        const_iterator& operator++()
        {
          current_++;
          while(current_.index() < connected_components_->num_elements() &&
                current_.index() != connected_components_->id(current_.index()))
            current_++;

          return *this;
        }
      
        const_iterator operator++(int)
        {
          const_iterator temp = *this;
          ++*this;
          return temp;
        }
      
        bool operator==(const const_iterator& other) const
        {
          return current_ == other.current_ && connected_components_ == other.connected_components_;
        }
     
        bool operator!=(const const_iterator& other) const
        {
          return current_ != other.current_ || connected_components_ != other.connected_components_;
        }

      private:
        const connected_components* connected_components_ = nullptr;
        component_handle current_;
      };
    
    
      connected_components() = default;
   
      ///N number of all elements
      connected_components(std::size_t N) : nodes_(N), num_components_(N)
      {
        for(std::size_t i = 0; i < N; ++i)
        {
          nodes_[i].id = i;
          nodes_[i].count = 1;
        }
      }
    
      ///number of components (initially number of all elements)
      std::size_t num_components() const
      {
        return num_components_;
      }

      std::size_t num_elements() const
      {
        return nodes_.size();
      }
    
      //return the number of elements in the component containing c
      std::size_t num_elements(component_handle c) const
      {
       assert(c.index() < num_elements());
       return find(c).count;
      }

      const_iterator begin() const
      {
       std::size_t x = 0;
       while(x != id(x))
         x++;
       return const_iterator(this, x);
      }
    
      const_iterator cbegin() const
      {
         return begin();
      }
    
      const_iterator end() const
      {
       return const_iterator(this, num_elements());
      }
    
      const_iterator cend() const
      {
       return end();
      }
    
      element_handle element(std::size_t index) const
      {
        return index < num_elements() ? element_handle(index) : element_handle();
      }
    
      component_handle component(element_handle e) const
      {
        std::size_t x = e.index();
        while(x != id(x))
        {
          nodes_[x].id = id(id(x));
          x = id(x);
        }
        return component_handle(x);
      }

      bool same_component(element_handle p, element_handle q) const
      {
        return find(p).id == find(q).id;
      }
    
      component_handle unite(element_handle p, element_handle q)
      {
        return unite(component(p), component(q));
      }
    
      component_handle unite(element_handle p, component_handle q)
      {
        return unite(component(p), q);
      }
    
      component_handle unite(component_handle p, element_handle q)
      {
        return unite(p, component(q));
      }
    
      component_handle unite(component_handle p, component_handle q)
      {
        auto& ni = find(p);
        auto& nj = find(q);
        if (ni.id == nj.id)
          return component_handle(ni.id);

        if(ni.count < nj.count)
        {
          ni.id = nj.id;
          nj.count += ni.count;
        }
        else
        {
          nj.id = ni.id;
          ni.count += nj.count;
        }
        num_components_--;
        return component_handle(ni.id);
      }

    
  private:
      node& find(element_handle e)
      {
        return find(component(e));
      }
    
      node& find(component_handle c)
      {
        return nodes_[c.index()];
      }
    
      const node& find(element_handle e) const
      {
        return find(component(e));
      }
    
      const node& find(component_handle c) const
      {
        return nodes_[c.index()];
      }
    
      inline std::size_t& id(std::size_t x)
      {
        return nodes_[x].id;
      }
    
      inline const std::size_t& id(std::size_t x) const
      {
        return nodes_[x].id;
      }
    
      mutable std::vector<node> nodes_;
      std::size_t num_components_; // number of components
    };
  }
}
