//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include <functional>
#include <stack>
#include <cassert>
#include <vector>
#include <chrono>
#include "owl/utils/range_algorithm.hpp"

namespace owl
{
  namespace utils
  {
    class progress
    {
    public:
    
      progress(std::uint64_t num_steps)
        : num_steps_(num_steps)
      {
        start_ = std::chrono::steady_clock::now();
        if(current())
          add_child_to_current(this);
      }
    
      void cancel()
      {
        assert(is_cancellable());
        for(auto& c: children_)
          c->cancel();
        is_canceled_ = true;
      }
  
      void pause()
      {
        assert(is_pausable());
        for(auto& c: children_)
          c->pause();
        is_paused_ = true;
      }
  
      void resume()
      {
        assert(is_pausable());
        for(auto& c: children_)
          c->pause();
        is_paused_ = false;
      }
  
      bool is_indeterminant() const
      {
        return num_steps_ == 0 && num_steps_completed_ == 0;
      }
  
      double fraction_completed() const
      {
        return num_steps_ == 0 ? 0.0 : static_cast<double>(num_steps_completed_) / num_steps_;
      }
    
      auto estimated_time_remaining() const
      {
        if(num_steps_completed_ == num_steps_ )
          return 0.0 * (start_ - start_);
        auto now =  std::chrono::steady_clock::now();
        return (now - start_) * (1.0 - fraction_completed())/fraction_completed();
      }
    
      void make_current(std::uint64_t num_steps_pending)
      {
        if(current() != this)
          current_progress_.push(current_info{this, num_steps_pending});
      }
  
      void resign_current()
      {
        assert(current() == this);
        //divide num steps pending among added children
        current_progress_.pop();
      }
  
  
      void step(std::uint64_t n = 1)
      {
        num_steps_completed_ += n;
        assert(num_steps_completed_ <= num_steps_);
        if(on_changed)
          on_changed();
      
        if(parent_ != nullptr)
        {
          std::uint64_t n_parent = static_cast<std::uint64_t>(fraction_completed() * num_steps_parent_) -num_steps_parent_completed_;
          if(n_parent > 0)
          {
            num_steps_parent_completed_ += n_parent;
          
            parent_->step(n_parent);
          }
        }
      }
    
      std::function<void()> on_changed;
    
      void add_child(progress* child, std::uint64_t num_steps_pending)
      {
        children_.push_back(child);
        child->parent_ = this;
        child->num_steps_parent_ = num_steps_pending;
      }
    
      bool is_pausable() const
      {
      return is_leaf() ? is_pausable_ : owl::utils::all_of(children_, [](const auto& c) { return c->is_pausable();});
      }
    
      bool is_cancellable() const
      {
        return is_leaf() ? is_cancellable_ : owl::utils::all_of(children_, [](const auto& c) { return c->is_cancellable();});
      }
    
      bool is_leaf() const
      {
        return parent_ == nullptr;
      }
  
    private:
      static progress* current()
      {
        if(progress::current_progress_.empty())
          return nullptr;
        return progress::current_progress_.top().current;
      }
    
      static void add_child_to_current(progress* child)
      {
        assert(current() != nullptr);
        current()->add_child(child, current_progress_.top().num_steps_pending);
      }
    
      struct current_info
      {
        progress* current;
        std::size_t num_steps_pending;
      };
    
      static thread_local std::stack<current_info> current_progress_;
  
      progress* parent_ = nullptr;
      std::atomic<std::uint64_t> num_steps_parent_ = 0;
      std::atomic<std::uint64_t> num_steps_parent_completed_ = 0;
    
      std::vector<progress*> children_;
      std::atomic<std::uint64_t> num_steps_ = 0;
      std::atomic<std::uint64_t> num_steps_completed_ = 0;
  
      bool is_canceled_ = false;
      bool is_cancellable_ = false;
    
      bool is_paused_ = false;
      bool is_pausable_ = false;
      std::chrono::steady_clock::time_point start_;
  
    };
  }
}
