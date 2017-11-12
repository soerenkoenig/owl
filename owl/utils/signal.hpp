
#pragma once

#include "owl/utils/non_copyable.hpp"
#include <functional>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

namespace owl
{
 namespace utils
 {
 ////combiners
    template<typename Result>
    struct combiner_last
    {
      using  result_type = Result;
      using  combined_result_type = Result;

      explicit combiner_last() : result_()
      {
      }

      bool operator()(result_type r)
      {
        result_ = r;
        return true;
      }

      combined_result_type get() const
      {
       return result_;
      }
    private:
      combined_result_type result_;
    };
 
    template<typename Result>
    struct combiner_default : combiner_last<Result>
    {
      using result_type = typename combiner_last<Result>::result_type;
      using combined_result_type =typename combiner_last<Result>::combined_result_type;
    };


    template<>
    struct combiner_default<void>
    {
      using result_type = void;
      using combined_result_type = void;

      void get() const {}
      bool operator()(void)  { return true; }
    };
 
    template<typename Result>
    struct combiner_vector
    {
      using result_type = Result;
      using combined_result_type = std::vector<Result>;

      const combined_result_type& get() const
      {
        return result_;
      }

      bool operator()(result_type r)
      {
        result_.push_back(r);
        return true;
      }
  
    private:
      combined_result_type result_;
    };
 
    struct combiner_and
    {
      using result_type = bool;
      using combined_result_type = bool;

      explicit combiner_and() {}

      const combined_result_type& get() const  { return result_; }

      combined_result_type operator()(result_type r)
      {
        result_ = ( result_ && r );
        return true;
      }

    private:
      combined_result_type result_ = true;
    };
 
    struct combiner_or
    {
      using result_type = bool;
      using combined_result_type = bool;

      explicit combiner_or() {}

      const combined_result_type& get() const  { return result_; }

      combined_result_type operator()(result_type r)
      {
        result_ = ( result_ || r );
        return true;
      }

    private:
      combined_result_type result_ = false;
    };
 
    template<typename Result>
    struct combiner_bitwise_and
    {
      using result_type = Result;
      using combined_result_type = Result;

      explicit combiner_bitwise_and() {}

      const combined_result_type& get() const { return result_; }

      combined_result_type operator()(result_type r)
      {
        if(first_)
        {
          result_ = r;
          first_ = false;
          return true;
        }
      
        result_ &= r ;
        return true;
      }

    private:
      combined_result_type result_ = 0;
      bool first_ = true;
    };
 
 
    template<typename Result>
    struct combiner_until_false
    {
      using result_type = Result;
      using combined_result_type = Result;

      explicit combiner_until_false() : result_() {}

      const combined_result_type& get() const { return result_; }

      bool operator()(result_type r)
      {
        result_ = r;
        return result_ ? true : false;
      }

    private:
      combined_result_type result_;
    };
 
    template<typename Result>
    struct combiner_while_false
    {
      using result_type = Result;
      using combined_result_type = Result;

      explicit combiner_while_false() : result_() {}

      const combined_result_type& get() const  { return result_; }

      bool operator()( result_type r )
      {
        result_ = r;
        return  result_ ? false : true ;
      }

    private:
      combined_result_type result_;
    };
 /*
 
    namespace detail
    {
      class signal_base : non_copyable
      {
        virtual bool disconnect(int entry, int priority) = 0;

        friend struct disconnector;
      };
  
      struct disconnector : private non_copyable
      {
        disconnector( signal_base *signal);
    
        bool disconnect( int entry, std::int32_t priority)
        {
          return signal_->disconnect(entry, priority);
        }

      private:
        signal_base*  signal_;
      };
    }
 
    class connection : private non_copyable
    {
     private:
      std::weak_ptr<detail::disconnector>    disconnector_;
    };
 
    namespace detail
    {
      template<typename, typename> struct  invoke;
    
       template<class Collector, class R, class... Args>
      struct invoke<Collector, R ( Args... )> {

  bool operator()( Collector &collector, const std::function<R ( Args... )> &callback, Args... args )
  {
    return collector( callback( args... ) );
  }
};

//! CollectorInvocation specialisation for signals with void return type.
template<class Collector, class... Args>
struct invoke<Collector, void( Args... )>  {

  bool operator()( Collector &collector, const std::function<void( Args... )> &callback, Args... args )
  {
    callback( args... );
    return collector();
  }
};
    
      template <typename, typename>
      class signal_proto;
 
      template <typename R, typename... Args, typename Combiner>
      class signal_proto<R(Args...), Combiner> : signal_base
      {
      public:
        using callback_type = std::function<R(Args...)>;
        using result_type = R ;
        using combined_result_type = typename Combiner::combined_result_type;
    
    
        template <typename... ArgsIn>
        combined_result_type operator()( ArgsIn&&... args )
        {
          Combiner c;
          for(auto&& pair : callbacks_)
          {
            callback_entry& callback = pair.second;
          
            if(!callback.enabled_ || !callback.func_)
              continue;
          
            callback.enabled_ = false;
          continueEmission = this->invoke( collector, link->mCallbackFn, args... );
            bool continue_emit = detail::invoke(<c(callback.func_(std::forward<ArgsIn>(args)...));
         
            callback.enabled_ = true;
          
            if(!continue_emit)
              break;
          }
          return c.get();
        }
      
      
  
        connection connect(const callback_type &callback , std::int32_t priority = 0)
        {
          callbacks_.insert(priority, {callback, true});
        }
    
      
    
      private:
      struct callback_entry
      {
        callback_type func_;
        bool enabled_;
      };
    
      std::multimap<std::int32_t, callback_entry, std::greater<std::int32_t>> callbacks_;
      std::shared_ptr<disconnector> disconnector_;
    };
  }
 
    template <typename Signature, typename Combiner = combiner_default<typename std::function<Signature>::result_type>>
    class signal : public detail::signal_proto<Signature, Combiner>
    {
      bool disconnect(int entr int priority) override { return true; }
    };
 
  }
}
 
 

 
    template <typename Signature, typename Combiner>
    class signal
    {
        using callback_type = std::function<Signature>;
        using result_type = typename callback_type::result_type ;
        using combined_result_type = typename Combiner::combined_result_type;
    
        combined_result_type  operator()( Args... args )
        {
          Combiner c;
          emit(c, args... );
          return c.get();
        }
    private:
         void emit( Combiner &collector, Args... args )
         {
            bool continueEmission = true;
            for( auto &lp : mLinks )
             {
              SignalLink *link = lp.second;
      link->incrRef();
      do {
        if( link->mCallbackFn && link->isEnabled() ) {
          continueEmission = this->invoke( collector, link->mCallbackFn, args... );
          if( ! continueEmission ) {
            break;
          }
        }

        SignalLink *old = link;
        link = old->mNext;

        link->incrRef();
        old->decrRef();
      }
      while( link != lp.second );
      
      link->decrRef();

      if( ! continueEmission )
        break;
    }
  }
 
    }

    tempalte
 
    template<class R, class... Args>
    class signal_base<R ( Args... )>
    {
    
    }
 
   
   namespace detail
   {

//! Base class for signal links, which manages reference counting and provides a concrete type to be passed to Connection
struct SignalLinkBase {
  public:
  SignalLinkBase()
    : mRefCount( 1 ), mEnabled( true )
  {}
  virtual ~SignalLinkBase()
  {
    CI_ASSERT( mRefCount == 0 );
  }

  virtual bool removeSibling( SignalLinkBase *link ) = 0;

  void incrRef()
  {
    mRefCount++;
    CI_ASSERT( mRefCount > 0 );
  }

  void decrRef()
  {
    mRefCount--;
    if( ! mRefCount )
      delete this;
    else
      CI_ASSERT( mRefCount > 0 );
  }

  int getRefCount() const
  {
    return mRefCount;
  }

  void enable()
  {
    mEnabled = true;
  }

  void disable()
  {
    mEnabled = false;
  }

  bool isEnabled() const
  {
    return mEnabled;
  }

  private:
  int    mRefCount;
  bool  mEnabled;
};

//! Base Signal class, which provides a concrete type that can be stored by the Disconnector
struct SignalBase : private Noncopyable
{
  //! abstract method to disconnect \a link from the callback chain, which resides in the priority group \a priority.
  virtual bool disconnect( SignalLinkBase *link, int priority ) = 0;

  friend struct Disconnector;
};



} // namespace detail

// ----------------------------------------------------------------------------------------------------
// Connection and ScopedConnection
// ----------------------------------------------------------------------------------------------------

//! Connection is returned from Signal::connect(), which can be used to disconnect the callback slot.

class connection
{
  public:
  connection();
  connection( const std::shared_ptr<detail::Disconnector> &disconnector,
  detail::SignalLinkBase *link, int priority );
  connection( const connection &other );
  connection( connection &&other );
  connection& operator=( const connection &rhs );
  connection& operator=( connection &&rhs );

  //! Disconnects this Connection from the callback chain. \a return true if a disconnection was made, false otherwise.
  
  bool disconnect() { return true; }
  
  //! Returns whether or not this Connection is still connected to the callback chain.
  bool is_connected() const;

  //! Enable calling the function linked to this Connection. Does not affect the callback chain. Default is enabled.
  void enable();
  //! Disable calling the function linked to this Connection. Does not affect the callback chain.
  void disable();
  //! Returns true if the linked function will be called as part of the callback chain. Default is enabled.
  bool is_enabled() const;

  private:
  std::weak_ptr<detail::Disconnector>    disconnector_;
  detail::SignalLinkBase*                mLink;
  int                                    mPriority;
};

//! ScopedConnection can be captured from Signal::connect() to limit the connection lifetime to the current scope, after which Connection::disconnect() will be called.
class CI_API ScopedConnection : public Connection, private Noncopyable {
  public:
  ScopedConnection();
  ~ScopedConnection();
  ScopedConnection( ScopedConnection &&other );
  ScopedConnection( Connection &&other );
  ScopedConnection& operator=( ScopedConnection &&rhs );
};

// ----------------------------------------------------------------------------------------------------
// ConnectionList
// ----------------------------------------------------------------------------------------------------

//! Maintains a list of Connections and calls disconnect on them when it is destroyed. Non-copyable.

class connection_list : private non_copyable
 {
  public:
  ~connection_list()
  {
    clear();
  }

 
  void add(connection &&target)
  {
    connections_.emplace_back(std::move(target));
  }
 
  void clear()
  {
    for(auto &conn : connections_)
      conn.disconnect();

    connections_.clear();
  }
 
  void operator+=(connection &&target)
  {
    add(std::move( target));
  }

  private:
  std::vector<connection>  connections_;
};

// ----------------------------------------------------------------------------------------------------
// Collectors
// ----------------------------------------------------------------------------------------------------

namespace detail {

//! The template implementation for callback list.
template<typename, typename> class  SignalProto;   // undefined

//! Invokes signal handlers differently depending on return type.
template<typename, typename> struct  CollectorInvocation;


//! CollectorInvocation specialisation for regular signals.
template<class Collector, class R, class... Args>
struct CollectorInvocation<Collector, R ( Args... )> : public SignalBase {

  bool invoke( Collector &collector, const std::function<R ( Args... )> &callback, Args... args )
  {
    return collector( callback( args... ) );
  }
};

//! CollectorInvocation specialisation for signals with void return type.
template<class Collector, class... Args>
struct CollectorInvocation<Collector, void( Args... )> : public SignalBase {

  bool invoke( Collector &collector, const std::function<void( Args... )> &callback, Args... args )
  {
    callback( args... );
    return collector();
  }
};

// ----------------------------------------------------------------------------------------------------
// SignalProto
// ----------------------------------------------------------------------------------------------------

//! SignalProto template, the parent class of Signal, specialised for the callback signature and collector.
template<class Collector, class R, class... Args>
class SignalProto<R ( Args... ), Collector> : private CollectorInvocation<Collector, R ( Args... )> {
  protected:
  typedef std::function<R ( Args... )>    CallbackFn;
  typedef typename CallbackFn::result_type  Result;
  typedef typename Collector::CollectorResult  CollectorResult;

  public:
  //! Constructs an empty SignalProto
  SignalProto()
    : mDisconnector( new Disconnector( this ) )
  {}

  //! Destructor releases all resources associated with this signal.
  ~SignalProto()
  {
    for( auto &lp : mLinks ) {
      SignalLink *link = lp.second;
      if( link ) {
        while( link->mNext != link )
          link->mNext->unlink();

        CI_ASSERT( link->getRefCount() >= 2 );

        link->decrRef();
        link->decrRef();
      }
    }
  }

  //! Connects \a callback to the signal, assigned to the default priority group (priority = 0). \return a Connection, which can be used to disconnect this callback slot.
  Connection connect( const CallbackFn &callback )
  {
    return connect( 0, callback );
  }

  //! Connects \a callback to the signal, assigned to the priority group \a priority. \return a Connection, which can be used to disconnect this callback slot.
  Connection connect( int priority, const CallbackFn &callback )
  {
    auto head = ensureLinkGroup( priority );
    auto link = head->addBefore( callback );
    return Connection( mDisconnector, link, priority );
  }

  //! Emit a signal, i.e. invoke all its callbacks and collect return types with Collector. \return the CollectorResult from the collector.
  CollectorResult  emit( Args... args )
  {
    Collector collector;
    emit( collector, args... );
    return collector.getResult();
  }

  //! Emit a signal, i.e. invoke all its callbacks and collect return types with \a collector.
  void emit( Collector &collector, Args... args )
  {
    bool continueEmission = true;
    for( auto &lp : mLinks ) {
      SignalLink *link = lp.second;
      link->incrRef();
      do {
        if( link->mCallbackFn && link->isEnabled() ) {
          continueEmission = this->invoke( collector, link->mCallbackFn, args... );
          if( ! continueEmission ) {
            break;
          }
        }

        SignalLink *old = link;
        link = old->mNext;

        link->incrRef();
        old->decrRef();
      }
      while( link != lp.second );
      
      link->decrRef();

      if( ! continueEmission )
        break;
    }
  }

  //! Returns the number of connected slots.
  size_t getNumSlots() const
  {
    size_t count = 0;

    for( auto &lp : mLinks ) {
      SignalLink *link = lp.second;
      do {
        if( link->mCallbackFn )
          count++;

        SignalLink *old = link;
        link = old->mNext;
      }
      while( link != lp.second );
    }

    return count;
  }

  private:

  //! implements a doubly-linked ring with ref-counted nodes containing the signal handlers.
  struct SignalLink : public SignalLinkBase {
    explicit SignalLink( const CallbackFn &callback )
      : mNext( nullptr ), mPrev( nullptr ), mCallbackFn( callback )
    {}

    void unlink()
    {
      mCallbackFn = nullptr;
      if( mNext )
        mNext->mPrev = mPrev;
      if( mPrev )
        mPrev->mNext = mNext;

      decrRef();
      // leave intact ->mNext, ->mPrev for stale iterators
    }

    SignalLink* addBefore( const CallbackFn &callback )
    {
      SignalLink *link = new SignalLink( callback );

      link->mPrev = mPrev; // link to last
      link->mNext = this;
      mPrev->mNext = link; // link from last
      mPrev = link;

      return link;
    }

    bool deactivate( const CallbackFn &callback )
    {
      if( callback == mCallbackFn ) {
        mCallbackFn = nullptr;  // deactivate static head
        return true;
      }

      for( SignalLink *link = this->mNext ? this->mNext : this; link != this; link = link->mNext ) {
        if( callback == link->function ) {
          link->unlink();    // deactivate and unlink sibling
          return true;
        }
      }
      return false;
    }

    bool removeSibling( SignalLinkBase *sibling ) override
    {
      for( SignalLink *link = this->mNext ? this->mNext : this; link != this; link = link->mNext ) {
        if( sibling == link ) {
          link->unlink();    // deactivate and unlink sibling
          return true;
        }
      }
      return false;
    }

    SignalLink*    mNext;
    SignalLink*    mPrev;
    CallbackFn    mCallbackFn;
  };

  bool disconnect( SignalLinkBase *link, int priority ) override
  {
    auto it = mLinks.find( priority );
    if( it == mLinks.end() )
      return false;

    return it->second->removeSibling( link );
  }

  //! returns the head link for this priority group
  SignalLink* ensureLinkGroup( int priority )
  {
    auto it = mLinks.find( priority );
    if( it != mLinks.end() )
      return it->second;
    else {
      auto head = new SignalLink( CallbackFn() ); // ref count = 1
      head->incrRef(); // ref count = 2, head of ring, can be deactivated but not removed
      head->mNext = head; // ring head initialization
      head->mPrev = head; // ring tail initialization

      mLinks.insert( { priority, head } );
      return head;
    }
  }

  std::map<int, SignalLink*, std::greater<int> >  mLinks;      // groups of callback nodes, which are stored in a reference counted linked list. Each group represents priority, greater int means fires first.
  std::shared_ptr<Disconnector>          mDisconnector;  // Connection holds a weak_ptr to this to make disconnections.
};

} // cinder::detail

// namespace cinder


template <typename Signature, class Collector = detail::CollectorDefault<typename std::function<Signature>::result_type> >
struct event : detail::SignalProto<Signature, Collector>
{

  typedef detail::SignalProto<Signature, Collector>  SignalProto;
  typedef typename SignalProto::CallbackFn      CallbackFn;
};

// ----------------------------------------------------------------------------------------------------
// slot
// ----------------------------------------------------------------------------------------------------

//! Creates a std::function by binding \a object to the member function pointer \a method.
template<class Instance, class Class, class R, class... Args>
std::function<R ( Args... )> slot( Instance &object, R (Class::*method)( Args... ) )
{
  return [&object, method] ( Args... args )  { return ( object .* method )( args... ); };
}

//! Creates a std::function by binding \a object to the member function pointer \a method.
template<class Class, class R, class... Args>
std::function<R ( Args... )> slot( Class *object, R ( Class::*method )( Args... ) )
{
  return [object, method] ( Args... args )  { return ( object ->* method )( args... ); };
}



*/

}
}

