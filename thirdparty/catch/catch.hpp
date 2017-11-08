/*  Catch v2.0.1
 *  Generated: 2017-11-03 11:53:39.642003
 *  ----------------------------------------------------------
 *  This file has been merged from multiple headers. Please don't edit it directly
 *  Copyright (c) 2017 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
#define TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
// start catch.hpp


#ifdef __clang__
#    pragma clang system_header
#elif defined __GNUC__
#    pragma GCC system_header
#endif

// start catch_suppress_warnings.h

#ifdef __clang__
#   ifdef __ICC // icpc defines the __clang__ macro
#       pragma warning(push)
#       pragma warning(disable: 161 1682)
#   else // __ICC
#       pragma clang diagnostic ignored "-Wglobal-constructors"
#       pragma clang diagnostic ignored "-Wvariadic-macros"
#       pragma clang diagnostic ignored "-Wc99-extensions"
#       pragma clang diagnostic ignored "-Wunused-variable"
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wpadded"
#       pragma clang diagnostic ignored "-Wswitch-enum"
#       pragma clang diagnostic ignored "-Wcovered-switch-default"
#    endif
#elif defined __GNUC__
#    pragma GCC diagnostic ignored "-Wvariadic-macros"
#    pragma GCC diagnostic ignored "-Wunused-variable"
#    pragma GCC diagnostic ignored "-Wparentheses"

#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpadded"
#endif
// end catch_suppress_warnings.h
#if defined(CATCH_CONFIG_MAIN) || defined(CATCH_CONFIG_RUNNER)
#  define CATCH_IMPL
#  define CATCH_CONFIG_EXTERNAL_INTERFACES
#  if defined(CATCH_CONFIG_DISABLE_MATCHERS)
#    undef CATCH_CONFIG_DISABLE_MATCHERS
#  endif
#endif

// start catch_platform.h

#ifdef __APPLE__
# include &lt;TargetConditionals.h&gt;
# if TARGET_OS_MAC == 1
#  define CATCH_PLATFORM_MAC
# elif TARGET_OS_IPHONE == 1
#  define CATCH_PLATFORM_IPHONE
# endif

#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define CATCH_PLATFORM_LINUX

#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER)
#  define CATCH_PLATFORM_WINDOWS
#endif

// end catch_platform.h
#ifdef CATCH_IMPL
#  ifndef CLARA_CONFIG_MAIN
#    define CLARA_CONFIG_MAIN_NOT_DEFINED
#    define CLARA_CONFIG_MAIN
#  endif
#endif

// start catch_tag_alias_autoregistrar.h

// start catch_common.h

// start catch_compiler_capabilities.h

// Detect a number of compiler features - by compiler
// The following features are defined:
//
// CATCH_CONFIG_COUNTER : is the __COUNTER__ macro supported?
// CATCH_CONFIG_WINDOWS_SEH : is Windows SEH supported?
// CATCH_CONFIG_POSIX_SIGNALS : are POSIX signals supported?
// ****************
// Note to maintainers: if new toggles are added please document them
// in configuration.md, too
// ****************

// In general each macro has a _NO_&lt;feature name&gt; form
// (e.g. CATCH_CONFIG_NO_POSIX_SIGNALS) which disables the feature.
// Many features, at point of detection, define an _INTERNAL_ macro, so they
// can be combined, en-mass, with the _NO_ forms later.

#ifdef __cplusplus

#  if __cplusplus &gt;= 201402L
#    define CATCH_CPP14_OR_GREATER
#  endif

#endif

#ifdef __clang__

#       define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
            _Pragma( "clang diagnostic push" ) \
            _Pragma( "clang diagnostic ignored \"-Wexit-time-destructors\"" ) \
            _Pragma( "clang diagnostic ignored \"-Wglobal-constructors\"")
#       define CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS \
            _Pragma( "clang diagnostic pop" )

#       define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            _Pragma( "clang diagnostic push" ) \
            _Pragma( "clang diagnostic ignored \"-Wparentheses\"" )
#       define CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
            _Pragma( "clang diagnostic pop" )

#endif // __clang__

////////////////////////////////////////////////////////////////////////////////
// We know some environments not to support full POSIX signals
#if defined(__CYGWIN__) || defined(__QNX__)

#   if !defined(CATCH_CONFIG_POSIX_SIGNALS)
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#   endif

#endif

#ifdef __OS400__
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#       define CATCH_CONFIG_COLOUR_NONE
#endif

////////////////////////////////////////////////////////////////////////////////
// Cygwin
#ifdef __CYGWIN__

// Required for some versions of Cygwin to declare gettimeofday
// see: http://stackoverflow.com/questions/36901803/gettimeofday-not-declared-in-this-scope-cygwin
#   define _BSD_SOURCE

#endif // __CYGWIN__

////////////////////////////////////////////////////////////////////////////////
// Visual C++
#ifdef _MSC_VER

// Universal Windows platform does not support SEH
// Or console colours (or console at all...)
#  if defined(WINAPI_FAMILY) &amp;&amp; (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#    define CATCH_CONFIG_COLOUR_NONE
#  else
#    define CATCH_INTERNAL_CONFIG_WINDOWS_SEH
#  endif

#endif // _MSC_VER

////////////////////////////////////////////////////////////////////////////////

// Use of __COUNTER__ is suppressed during code analysis in
// CLion/AppCode 2017.2.x and former, because __COUNTER__ is not properly
// handled by it.
// Otherwise all supported compilers support COUNTER macro,
// but user still might want to turn it off
#if ( !defined(__JETBRAINS_IDE__) || __JETBRAINS_IDE__ &gt;= 20170300L )
    #define CATCH_INTERNAL_CONFIG_COUNTER
#endif

#if defined(CATCH_INTERNAL_CONFIG_COUNTER) &amp;&amp; !defined(CATCH_CONFIG_NO_COUNTER) &amp;&amp; !defined(CATCH_CONFIG_COUNTER)
#   define CATCH_CONFIG_COUNTER
#endif
#if defined(CATCH_INTERNAL_CONFIG_WINDOWS_SEH) &amp;&amp; !defined(CATCH_CONFIG_NO_WINDOWS_SEH) &amp;&amp; !defined(CATCH_CONFIG_WINDOWS_SEH)
#   define CATCH_CONFIG_WINDOWS_SEH
#endif
// This is set by default, because we assume that unix compilers are posix-signal-compatible by default.
#if !defined(CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS) &amp;&amp; !defined(CATCH_CONFIG_NO_POSIX_SIGNALS) &amp;&amp; !defined(CATCH_CONFIG_POSIX_SIGNALS)
#   define CATCH_CONFIG_POSIX_SIGNALS
#endif

#if !defined(CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS
#   define CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
#   define CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS
#endif

// end catch_compiler_capabilities.h
#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#ifdef CATCH_CONFIG_COUNTER
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __COUNTER__ )
#else
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __LINE__ )
#endif

#include &lt;iosfwd&gt;
#include &lt;string&gt;
#include &lt;cstdint&gt;

namespace Catch {

    struct CaseSensitive { enum Choice {
        Yes,
        No
    }; };

    class NonCopyable {
        NonCopyable( NonCopyable const&amp; )              = delete;
        NonCopyable( NonCopyable &amp;&amp; )                  = delete;
        NonCopyable&amp; operator = ( NonCopyable const&amp; ) = delete;
        NonCopyable&amp; operator = ( NonCopyable &amp;&amp; )     = delete;

    protected:
        NonCopyable();
        virtual ~NonCopyable();
    };

    struct SourceLineInfo {

        SourceLineInfo() = delete;
        SourceLineInfo( char const* _file, std::size_t _line ) noexcept;

        SourceLineInfo( SourceLineInfo const&amp; other )        = default;
        SourceLineInfo( SourceLineInfo &amp;&amp; )                  = default;
        SourceLineInfo&amp; operator = ( SourceLineInfo const&amp; ) = default;
        SourceLineInfo&amp; operator = ( SourceLineInfo &amp;&amp; )     = default;

        bool empty() const noexcept;
        bool operator == ( SourceLineInfo const&amp; other ) const noexcept;
        bool operator &lt; ( SourceLineInfo const&amp; other ) const noexcept;

        char const* file;
        std::size_t line;
    };

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, SourceLineInfo const&amp; info );

    // This is just here to avoid compiler warnings with macro constants and boolean literals
    bool isTrue( bool value );
    bool alwaysTrue();
    bool alwaysFalse();

    // Use this in variadic streaming macros to allow
    //    &gt;&gt; +StreamEndStop
    // as well as
    //    &gt;&gt; stuff +StreamEndStop
    struct StreamEndStop {
        std::string operator+() const;
    };
    template&lt;typename T&gt;
    T const&amp; operator + ( T const&amp; value, StreamEndStop ) {
        return value;
    }
}

#define CATCH_INTERNAL_LINEINFO \
    ::Catch::SourceLineInfo( __FILE__, static_cast&lt;std::size_t&gt;( __LINE__ ) )

// end catch_common.h
namespace Catch {

    struct RegistrarForTagAliases {
        RegistrarForTagAliases( char const* alias, char const* tag, SourceLineInfo const&amp; lineInfo );
    };

} // end namespace Catch

#define CATCH_REGISTER_TAG_ALIAS( alias, spec ) namespace{ Catch::RegistrarForTagAliases INTERNAL_CATCH_UNIQUE_NAME( AutoRegisterTagAlias )( alias, spec, CATCH_INTERNAL_LINEINFO ); }

// end catch_tag_alias_autoregistrar.h
// start catch_test_registry.h

// start catch_interfaces_testcase.h

#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    class TestSpec;

    struct ITestInvoker {
        virtual void invoke () const = 0;
        virtual ~ITestInvoker();
    };

    using ITestCasePtr = std::shared_ptr&lt;ITestInvoker&gt;;

    class TestCase;
    struct IConfig;

    struct ITestCaseRegistry {
        virtual ~ITestCaseRegistry();
        virtual std::vector&lt;TestCase&gt; const&amp; getAllTests() const = 0;
        virtual std::vector&lt;TestCase&gt; const&amp; getAllTestsSorted( IConfig const&amp; config ) const = 0;
    };

    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config );

}

// end catch_interfaces_testcase.h
// start catch_stringref.h

#include &lt;cstddef&gt;
#include &lt;string&gt;
#include &lt;iosfwd&gt;

namespace Catch {

    class StringData;

    /// A non-owning string class (similar to the forthcoming std::string_view)
    /// Note that, because a StringRef may be a substring of another string,
    /// it may not be null terminated. c_str() must return a null terminated
    /// string, however, and so the StringRef will internally take ownership
    /// (taking a copy), if necessary. In theory this ownership is not externally
    /// visible - but it does mean (substring) StringRefs should not be shared between
    /// threads.
    class StringRef {
        friend struct StringRefTestAccess;

        using size_type = std::size_t;

        char const* m_start;
        size_type m_size;

        char* m_data = nullptr;

        void takeOwnership();

    public: // construction/ assignment
        StringRef() noexcept;
        StringRef( StringRef const&amp; other ) noexcept;
        StringRef( StringRef&amp;&amp; other ) noexcept;
        StringRef( char const* rawChars ) noexcept;
        StringRef( char const* rawChars, size_type size ) noexcept;
        StringRef( std::string const&amp; stdString ) noexcept;
        ~StringRef() noexcept;

        auto operator = ( StringRef other ) noexcept -&gt; StringRef&amp;;
        operator std::string() const;

        void swap( StringRef&amp; other ) noexcept;

    public: // operators
        auto operator == ( StringRef const&amp; other ) const noexcept -&gt; bool;
        auto operator != ( StringRef const&amp; other ) const noexcept -&gt; bool;

        auto operator[] ( size_type index ) const noexcept -&gt; char;

    public: // named queries
        auto empty() const noexcept -&gt; bool;
        auto size() const noexcept -&gt; size_type;
        auto numberOfCharacters() const noexcept -&gt; size_type;
        auto c_str() const -&gt; char const*;

    public: // substrings and searches
        auto substr( size_type start, size_type size ) const noexcept -&gt; StringRef;

    private: // ownership queries - may not be consistent between calls
        auto isOwned() const noexcept -&gt; bool;
        auto isSubstring() const noexcept -&gt; bool;
        auto data() const noexcept -&gt; char const*;
    };

    auto operator + ( StringRef const&amp; lhs, StringRef const&amp; rhs ) -&gt; std::string;
    auto operator + ( StringRef const&amp; lhs, char const* rhs ) -&gt; std::string;
    auto operator + ( char const* lhs, StringRef const&amp; rhs ) -&gt; std::string;

    auto operator &lt;&lt; ( std::ostream&amp; os, StringRef const&amp; sr ) -&gt; std::ostream&amp;;

} // namespace Catch

// end catch_stringref.h
namespace Catch {

template&lt;typename C&gt;
class TestInvokerAsMethod : public ITestInvoker {
    void (C::*m_testAsMethod)();
public:
    TestInvokerAsMethod( void (C::*testAsMethod)() ) noexcept : m_testAsMethod( testAsMethod ) {}

    void invoke() const override {
        C obj;
        (obj.*m_testAsMethod)();
    }
};

auto makeTestInvoker( void(*testAsFunction)() ) noexcept -&gt; ITestInvoker*;

template&lt;typename C&gt;
auto makeTestInvoker( void (C::*testAsMethod)() ) noexcept -&gt; ITestInvoker* {
    return new(std::nothrow) TestInvokerAsMethod&lt;C&gt;( testAsMethod );
}

struct NameAndTags {
    NameAndTags( StringRef name_ = "", StringRef tags_ = "" ) noexcept;
    StringRef name;
    StringRef tags;
};

struct AutoReg : NonCopyable {
    AutoReg( ITestInvoker* invoker, SourceLineInfo const&amp; lineInfo, StringRef classOrMethod, NameAndTags const&amp; nameAndTags ) noexcept;
    ~AutoReg();
};

} // end namespace Catch

#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TESTCASE_NO_REGISTRATION( TestName, ... ) \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION( TestName, ClassName, ... ) \
        namespace{                        \
            struct TestName : ClassName { \
                void test();              \
            };                            \
        }                                 \
        void TestName::test()

#endif

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TESTCASE2( TestName, ... ) \
        static void TestName(); \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &amp;TestName ), CATCH_INTERNAL_LINEINFO, "", Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE( ... ) \
        INTERNAL_CATCH_TESTCASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_METHOD_AS_TEST_CASE( QualifiedMethod, ... ) \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &amp;QualifiedMethod ), CATCH_INTERNAL_LINEINFO, "&amp;" #QualifiedMethod, Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEST_CASE_METHOD2( TestName, ClassName, ... )\
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ \
            struct TestName : ClassName{ \
                void test(); \
            }; \
            Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar ) ( Catch::makeTestInvoker( &amp;TestName::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        } \
        CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS \
        void TestName::test()
    #define INTERNAL_CATCH_TEST_CASE_METHOD( ClassName, ... ) \
        INTERNAL_CATCH_TEST_CASE_METHOD2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), ClassName, __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_REGISTER_TESTCASE( Function, ... ) \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( Function ), CATCH_INTERNAL_LINEINFO, "", Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS

// end catch_test_registry.h
// start catch_capture.hpp

// start catch_assertionhandler.h

// start catch_decomposer.h

// start catch_tostring.h

#include &lt;sstream&gt;
#include &lt;vector&gt;
#include &lt;cstddef&gt;
#include &lt;type_traits&gt;
#include &lt;string&gt;

#ifdef __OBJC__
// start catch_objc_arc.hpp

#import &lt;Foundation/Foundation.h&gt;

#ifdef __has_feature
#define CATCH_ARC_ENABLED __has_feature(objc_arc)
#else
#define CATCH_ARC_ENABLED 0
#endif

void arcSafeRelease( NSObject* obj );
id performOptionalSelector( id obj, SEL sel );

#if !CATCH_ARC_ENABLED
inline void arcSafeRelease( NSObject* obj ) {
    [obj release];
}
inline id performOptionalSelector( id obj, SEL sel ) {
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED
#define CATCH_ARC_STRONG
#else
inline void arcSafeRelease( NSObject* ){}
inline id performOptionalSelector( id obj, SEL sel ) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#endif
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED __unsafe_unretained
#define CATCH_ARC_STRONG __strong
#endif

// end catch_objc_arc.hpp
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4180) // We attempt to stream a function (address) by const&amp;, which MSVC complains about but is harmless
#endif

// We need a dummy global operator&lt;&lt; so we can bring it into Catch namespace later
struct Catch_global_namespace_dummy;
std::ostream&amp; operator&lt;&lt;(std::ostream&amp;, Catch_global_namespace_dummy);

namespace Catch {
    // Bring in operator&lt;&lt; from global namespace into Catch namespace
    using ::operator&lt;&lt;;

    namespace Detail {

        extern const std::string unprintableString;

        std::string rawMemoryToString( const void *object, std::size_t size );

        template&lt;typename T&gt;
        std::string rawMemoryToString( const T&amp; object ) {
          return rawMemoryToString( &amp;object, sizeof(object) );
        }

        template&lt;typename T&gt;
        class IsStreamInsertable {
            template&lt;typename SS, typename TT&gt;
            static auto test(int)
                -&gt; decltype(std::declval&lt;SS&amp;&gt;() &lt;&lt; std::declval&lt;TT&gt;(), std::true_type());

            template&lt;typename, typename&gt;
            static auto test(...)-&gt;std::false_type;

        public:
            static const bool value = decltype(test&lt;std::ostream, const T&amp;&gt;(0))::value;
        };

    } // namespace Detail

    // If we decide for C++14, change these to enable_if_ts
    template &lt;typename T&gt;
    struct StringMaker {
        template &lt;typename Fake = T&gt;
        static
        typename std::enable_if&lt;::Catch::Detail::IsStreamInsertable&lt;Fake&gt;::value, std::string&gt;::type
            convert(const Fake&amp; t) {
                std::ostringstream sstr;
                sstr &lt;&lt; t;
                return sstr.str();
        }

        template &lt;typename Fake = T&gt;
        static
        typename std::enable_if&lt;!::Catch::Detail::IsStreamInsertable&lt;Fake&gt;::value, std::string&gt;::type
            convert(const Fake&amp;) {
                return Detail::unprintableString;
        }
    };

    namespace Detail {

        // This function dispatches all stringification requests inside of Catch.
        // Should be preferably called fully qualified, like ::Catch::Detail::stringify
        template &lt;typename T&gt;
        std::string stringify(const T&amp; e) {
            return ::Catch::StringMaker&lt;typename std::remove_cv&lt;typename std::remove_reference&lt;T&gt;::type&gt;::type&gt;::convert(e);
        }

    } // namespace Detail

    // Some predefined specializations

    template&lt;&gt;
    struct StringMaker&lt;std::string&gt; {
        static std::string convert(const std::string&amp; str);
    };
    template&lt;&gt;
    struct StringMaker&lt;std::wstring&gt; {
        static std::string convert(const std::wstring&amp; wstr);
    };

    template&lt;&gt;
    struct StringMaker&lt;char const *&gt; {
        static std::string convert(char const * str);
    };
    template&lt;&gt;
    struct StringMaker&lt;char *&gt; {
        static std::string convert(char * str);
    };
    template&lt;&gt;
    struct StringMaker&lt;wchar_t const *&gt; {
        static std::string convert(wchar_t const * str);
    };
    template&lt;&gt;
    struct StringMaker&lt;wchar_t *&gt; {
        static std::string convert(wchar_t * str);
    };

    template&lt;int SZ&gt;
    struct StringMaker&lt;char[SZ]&gt; {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template&lt;int SZ&gt;
    struct StringMaker&lt;signed char[SZ]&gt; {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template&lt;int SZ&gt;
    struct StringMaker&lt;unsigned char[SZ]&gt; {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };

    template&lt;&gt;
    struct StringMaker&lt;int&gt; {
        static std::string convert(int value);
    };
    template&lt;&gt;
    struct StringMaker&lt;long&gt; {
        static std::string convert(long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;long long&gt; {
        static std::string convert(long long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned int&gt; {
        static std::string convert(unsigned int value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned long&gt; {
        static std::string convert(unsigned long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned long long&gt; {
        static std::string convert(unsigned long long value);
    };

    template&lt;&gt;
    struct StringMaker&lt;bool&gt; {
        static std::string convert(bool b);
    };

    template&lt;&gt;
    struct StringMaker&lt;char&gt; {
        static std::string convert(char c);
    };
    template&lt;&gt;
    struct StringMaker&lt;signed char&gt; {
        static std::string convert(signed char c);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned char&gt; {
        static std::string convert(unsigned char c);
    };

    template&lt;&gt;
    struct StringMaker&lt;std::nullptr_t&gt; {
        static std::string convert(std::nullptr_t);
    };

    template&lt;&gt;
    struct StringMaker&lt;float&gt; {
        static std::string convert(float value);
    };
    template&lt;&gt;
    struct StringMaker&lt;double&gt; {
        static std::string convert(double value);
    };

    template &lt;typename T&gt;
    struct StringMaker&lt;T*&gt; {
        template &lt;typename U&gt;
        static std::string convert(U* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    template &lt;typename R, typename C&gt;
    struct StringMaker&lt;R C::*&gt; {
        static std::string convert(R C::* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    namespace Detail {
        template&lt;typename InputIterator&gt;
        std::string rangeToString(InputIterator first, InputIterator last) {
            std::ostringstream oss;
            oss &lt;&lt; "{ ";
            if (first != last) {
                oss &lt;&lt; ::Catch::Detail::stringify(*first);
                for (++first; first != last; ++first)
                    oss &lt;&lt; ", " &lt;&lt; ::Catch::Detail::stringify(*first);
            }
            oss &lt;&lt; " }";
            return oss.str();
        }
    }

    template&lt;typename T, typename Allocator&gt;
    struct StringMaker&lt;std::vector&lt;T, Allocator&gt; &gt; {
        static std::string convert( std::vector&lt;T,Allocator&gt; const&amp; v ) {
            return ::Catch::Detail::rangeToString( v.begin(), v.end() );
        }
    };

    template&lt;typename T&gt;
    struct EnumStringMaker {
        static std::string convert(const T&amp; t) {
            return ::Catch::Detail::stringify(static_cast&lt;typename std::underlying_type&lt;T&gt;::type&gt;(t));
        }
    };

#ifdef __OBJC__
    template&lt;&gt;
    struct StringMaker&lt;NSString*&gt; {
        static std::string convert(NSString * nsstring) {
            if (!nsstring)
                return "nil";
            return std::string("@") + [nsstring UTF8String];
        }
    };
    template&lt;&gt;
    struct StringMaker&lt;NSObject*&gt; {
        static std::string convert(NSObject* nsObject) {
            return ::Catch::Detail::stringify([nsObject description]);
        }

    };
    namespace Detail {
        inline std::string stringify( NSString* nsstring ) {
            return StringMaker&lt;NSString*&gt;::convert( nsstring );
        }

    } // namespace Detail
#endif // __OBJC__

} // namespace Catch

//////////////////////////////////////////////////////
// Separate std-lib types stringification, so it can be selectively enabled
// This means that we do not bring in

#if defined(CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS)
#  define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#endif

// Separate std::pair specialization
#if defined(CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER)
#include &lt;utility&gt;
namespace Catch {
    template&lt;typename T1, typename T2&gt;
    struct StringMaker&lt;std::pair&lt;T1, T2&gt; &gt; {
        static std::string convert(const std::pair&lt;T1, T2&gt;&amp; pair) {
            std::ostringstream oss;
            oss &lt;&lt; "{ "
                &lt;&lt; ::Catch::Detail::stringify(pair.first)
                &lt;&lt; ", "
                &lt;&lt; ::Catch::Detail::stringify(pair.second)
                &lt;&lt; " }";
            return oss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

// Separate std::tuple specialization
#if defined(CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER)
#include &lt;tuple&gt;
namespace Catch {
    namespace Detail {
        template&lt;
            typename Tuple,
            std::size_t N = 0,
            bool = (N &lt; std::tuple_size&lt;Tuple&gt;::value)
            &gt;
            struct TupleElementPrinter {
            static void print(const Tuple&amp; tuple, std::ostream&amp; os) {
                os &lt;&lt; (N ? ", " : " ")
                    &lt;&lt; ::Catch::Detail::stringify(std::get&lt;N&gt;(tuple));
                TupleElementPrinter&lt;Tuple, N + 1&gt;::print(tuple, os);
            }
        };

        template&lt;
            typename Tuple,
            std::size_t N
        &gt;
            struct TupleElementPrinter&lt;Tuple, N, false&gt; {
            static void print(const Tuple&amp;, std::ostream&amp;) {}
        };

    }

    template&lt;typename ...Types&gt;
    struct StringMaker&lt;std::tuple&lt;Types...&gt;&gt; {
        static std::string convert(const std::tuple&lt;Types...&gt;&amp; tuple) {
            std::ostringstream os;
            os &lt;&lt; '{';
            Detail::TupleElementPrinter&lt;std::tuple&lt;Types...&gt;&gt;::print(tuple, os);
            os &lt;&lt; " }";
            return os.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER

// Separate std::chrono::duration specialization
#if defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#include &lt;ctime&gt;
#include &lt;ratio&gt;
#include &lt;chrono&gt;

template &lt;class Ratio&gt;
struct ratio_string {
    static std::string symbol();
};

template &lt;class Ratio&gt;
std::string ratio_string&lt;Ratio&gt;::symbol() {
    std::ostringstream oss;
    oss &lt;&lt; '[' &lt;&lt; Ratio::num &lt;&lt; '/'
        &lt;&lt; Ratio::den &lt;&lt; ']';
    return oss.str();
}
template &lt;&gt;
struct ratio_string&lt;std::atto&gt; {
    static std::string symbol() { return "a"; }
};
template &lt;&gt;
struct ratio_string&lt;std::femto&gt; {
    static std::string symbol() { return "f"; }
};
template &lt;&gt;
struct ratio_string&lt;std::pico&gt; {
    static std::string symbol() { return "p"; }
};
template &lt;&gt;
struct ratio_string&lt;std::nano&gt; {
    static std::string symbol() { return "n"; }
};
template &lt;&gt;
struct ratio_string&lt;std::micro&gt; {
    static std::string symbol() { return "u"; }
};
template &lt;&gt;
struct ratio_string&lt;std::milli&gt; {
    static std::string symbol() { return "m"; }
};

namespace Catch {
    ////////////
    // std::chrono::duration specializations
    template&lt;typename Value, typename Ratio&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, Ratio&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, Ratio&gt; const&amp; duration) {
            std::ostringstream oss;
            oss &lt;&lt; duration.count() &lt;&lt; ' ' &lt;&lt; ratio_string&lt;Ratio&gt;::symbol() &lt;&lt; 's';
            return oss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;1&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;1&gt;&gt; const&amp; duration) {
            std::ostringstream oss;
            oss &lt;&lt; duration.count() &lt;&lt; " s";
            return oss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;60&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;60&gt;&gt; const&amp; duration) {
            std::ostringstream oss;
            oss &lt;&lt; duration.count() &lt;&lt; " m";
            return oss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;3600&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;3600&gt;&gt; const&amp; duration) {
            std::ostringstream oss;
            oss &lt;&lt; duration.count() &lt;&lt; " h";
            return oss.str();
        }
    };

    ////////////
    // std::chrono::time_point specialization
    // Generic time_point cannot be specialized, only std::chrono::time_point&lt;system_clock&gt;
    template&lt;typename Clock, typename Duration&gt;
    struct StringMaker&lt;std::chrono::time_point&lt;Clock, Duration&gt;&gt; {
        static std::string convert(std::chrono::time_point&lt;Clock, Duration&gt; const&amp; time_point) {
            return ::Catch::Detail::stringify(time_point.time_since_epoch()) + " since epoch";
        }
    };
    // std::chrono::time_point&lt;system_clock&gt; specialization
    template&lt;typename Duration&gt;
    struct StringMaker&lt;std::chrono::time_point&lt;std::chrono::system_clock, Duration&gt;&gt; {
        static std::string convert(std::chrono::time_point&lt;std::chrono::system_clock, Duration&gt; const&amp; time_point) {
            auto converted = std::chrono::system_clock::to_time_t(time_point);

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&amp;timeInfo, &amp;converted);
#else
            std::tm* timeInfo = std::gmtime(&amp;converted);
#endif

            auto const timeStampSize = sizeof("2017-01-16T17:06:45Z");
            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &amp;timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_tostring.h
#include &lt;ostream&gt;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4389) // '==' : signed/unsigned mismatch
#pragma warning(disable:4018) // more "signed/unsigned mismatch"
#pragma warning(disable:4312) // Converting int to T* using reinterpret_cast (issue on x64 platform)
#pragma warning(disable:4180) // qualifier applied to function type has no meaning
#endif

namespace Catch {

    struct ITransientExpression {
        virtual auto isBinaryExpression() const -&gt; bool = 0;
        virtual auto getResult() const -&gt; bool = 0;
        virtual void streamReconstructedExpression( std::ostream &amp;os ) const = 0;

        // We don't actually need a virtual destructore, but many static analysers
        // complain if it's not here :-(
        virtual ~ITransientExpression();
    };

    void formatReconstructedExpression( std::ostream &amp;os, std::string const&amp; lhs, StringRef op, std::string const&amp; rhs );

    template&lt;typename LhsT, typename RhsT&gt;
    class BinaryExpr  : public ITransientExpression {
        bool m_result;
        LhsT m_lhs;
        StringRef m_op;
        RhsT m_rhs;

        auto isBinaryExpression() const -&gt; bool override { return true; }
        auto getResult() const -&gt; bool override { return m_result; }

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            formatReconstructedExpression
                    ( os, Catch::Detail::stringify( m_lhs ), m_op, Catch::Detail::stringify( m_rhs ) );
        }

    public:
        BinaryExpr( bool comparisonResult, LhsT lhs, StringRef op, RhsT rhs )
        :   m_result( comparisonResult ),
            m_lhs( lhs ),
            m_op( op ),
            m_rhs( rhs )
        {}
    };

    template&lt;typename LhsT&gt;
    class UnaryExpr : public ITransientExpression {
        LhsT m_lhs;

        auto isBinaryExpression() const -&gt; bool override { return false; }
        auto getResult() const -&gt; bool override { return m_lhs ? true : false; }

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            os &lt;&lt; Catch::Detail::stringify( m_lhs );
        }

    public:
        UnaryExpr( LhsT lhs ) : m_lhs( lhs ) {}
    };

    // Specialised comparison functions to handle equality comparisons between ints and pointers (NULL deduces as an int)
    template&lt;typename LhsT, typename RhsT&gt;
    auto compareEqual( LhsT const&amp; lhs, RhsT const&amp; rhs ) -&gt; bool { return lhs == rhs; };
    template&lt;typename T&gt;
    auto compareEqual( T* const&amp; lhs, int rhs ) -&gt; bool { return lhs == reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareEqual( T* const&amp; lhs, long rhs ) -&gt; bool { return lhs == reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareEqual( int lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) == rhs; }
    template&lt;typename T&gt;
    auto compareEqual( long lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) == rhs; }

    template&lt;typename LhsT, typename RhsT&gt;
    auto compareNotEqual( LhsT const&amp; lhs, RhsT&amp;&amp; rhs ) -&gt; bool { return lhs != rhs; };
    template&lt;typename T&gt;
    auto compareNotEqual( T* const&amp; lhs, int rhs ) -&gt; bool { return lhs != reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareNotEqual( T* const&amp; lhs, long rhs ) -&gt; bool { return lhs != reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareNotEqual( int lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) != rhs; }
    template&lt;typename T&gt;
    auto compareNotEqual( long lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) != rhs; }

    template&lt;typename LhsT&gt;
    class ExprLhs {
        LhsT m_lhs;
    public:
        ExprLhs( LhsT lhs ) : m_lhs( lhs ) {}

        template&lt;typename RhsT&gt;
        auto operator == ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( compareEqual( m_lhs, rhs ), m_lhs, "==", rhs );
        }
        auto operator == ( bool rhs ) -&gt; BinaryExpr&lt;LhsT, bool&gt; const {
            return BinaryExpr&lt;LhsT, bool&gt;( m_lhs == rhs, m_lhs, "==", rhs );
        }

        template&lt;typename RhsT&gt;
        auto operator != ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( compareNotEqual( m_lhs, rhs ), m_lhs, "!=", rhs );
        }
        auto operator != ( bool rhs ) -&gt; BinaryExpr&lt;LhsT, bool&gt; const {
            return BinaryExpr&lt;LhsT, bool&gt;( m_lhs != rhs, m_lhs, "!=", rhs );
        }

        template&lt;typename RhsT&gt;
        auto operator &gt; ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( m_lhs &gt; rhs, m_lhs, "&gt;", rhs );
        }
        template&lt;typename RhsT&gt;
        auto operator &lt; ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( m_lhs &lt; rhs, m_lhs, "&lt;", rhs );
        }
        template&lt;typename RhsT&gt;
        auto operator &gt;= ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( m_lhs &gt;= rhs, m_lhs, "&gt;=", rhs );
        }
        template&lt;typename RhsT&gt;
        auto operator &lt;= ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return BinaryExpr&lt;LhsT, RhsT const&amp;&gt;( m_lhs &lt;= rhs, m_lhs, "&lt;=", rhs );
        }

        auto makeUnaryExpr() const -&gt; UnaryExpr&lt;LhsT&gt; {
            return UnaryExpr&lt;LhsT&gt;( m_lhs );
        }
    };

    void handleExpression( ITransientExpression const&amp; expr );

    template&lt;typename T&gt;
    void handleExpression( ExprLhs&lt;T&gt; const&amp; expr ) {
        handleExpression( expr.makeUnaryExpr() );
    }

    struct Decomposer {
        template&lt;typename T&gt;
        auto operator &lt;= ( T const&amp; lhs ) -&gt; ExprLhs&lt;T const&amp;&gt; {
            return ExprLhs&lt;T const&amp;&gt;( lhs );
        }
        auto operator &lt;=( bool value ) -&gt; ExprLhs&lt;bool&gt; {
            return ExprLhs&lt;bool&gt;( value );
        }
    };

} // end namespace Catch

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_decomposer.h
// start catch_assertioninfo.h

// start catch_result_type.h

namespace Catch {

    // ResultWas::OfType enum
    struct ResultWas { enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,

        FailureBit = 0x10,

        ExpressionFailed = FailureBit | 1,
        ExplicitFailure = FailureBit | 2,

        Exception = 0x100 | FailureBit,

        ThrewException = Exception | 1,
        DidntThrowException = Exception | 2,

        FatalErrorCondition = 0x200 | FailureBit

    }; };

    bool isOk( ResultWas::OfType resultType );
    bool isJustInfo( int flags );

    // ResultDisposition::Flags enum
    struct ResultDisposition { enum Flags {
        Normal = 0x01,

        ContinueOnFailure = 0x02,   // Failures fail test, but execution continues
        FalseTest = 0x04,           // Prefix expression with !
        SuppressFail = 0x08         // Failures are reported but do not fail the test
    }; };

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs );

    bool shouldContinueOnFailure( int flags );
    bool isFalseTest( int flags );
    bool shouldSuppressFailure( int flags );

} // end namespace Catch

// end catch_result_type.h
namespace Catch {

    struct AssertionInfo
    {
        StringRef macroName;
        SourceLineInfo lineInfo;
        StringRef capturedExpression;
        ResultDisposition::Flags resultDisposition;

        // We want to delete this constructor but a compiler bug in 4.8 means
        // the struct is then treated as non-aggregate
        //AssertionInfo() = delete;
    };

} // end namespace Catch

// end catch_assertioninfo.h
namespace Catch {

    struct TestFailureException{};
    struct AssertionResultData;

    class LazyExpression {
        friend class AssertionHandler;
        friend struct AssertionStats;

        ITransientExpression const* m_transientExpression = nullptr;
        bool m_isNegated;
    public:
        LazyExpression( bool isNegated );
        LazyExpression( LazyExpression const&amp; other );
        LazyExpression&amp; operator = ( LazyExpression const&amp; ) = delete;

        explicit operator bool() const;

        friend auto operator &lt;&lt; ( std::ostream&amp; os, LazyExpression const&amp; lazyExpr ) -&gt; std::ostream&amp;;
    };

    class AssertionHandler {
        AssertionInfo m_assertionInfo;
        bool m_shouldDebugBreak = false;
        bool m_shouldThrow = false;
        bool m_inExceptionGuard = false;

    public:
        AssertionHandler
            (   StringRef macroName,
                SourceLineInfo const&amp; lineInfo,
                StringRef capturedExpression,
                ResultDisposition::Flags resultDisposition );
        ~AssertionHandler();

        void handle( ITransientExpression const&amp; expr );

        template&lt;typename T&gt;
        void handle( ExprLhs&lt;T&gt; const&amp; expr ) {
            handle( expr.makeUnaryExpr() );
        }
        void handle( ResultWas::OfType resultType );
        void handle( ResultWas::OfType resultType, StringRef const&amp; message );
        void handle( ResultWas::OfType resultType, ITransientExpression const* expr, bool negated );
        void handle( AssertionResultData const&amp; resultData, ITransientExpression const* expr );

        auto shouldDebugBreak() const -&gt; bool;
        auto allowThrows() const -&gt; bool;
        void reactWithDebugBreak() const;
        void reactWithoutDebugBreak() const;
        void useActiveException();
        void setExceptionGuard();
        void unsetExceptionGuard();
    };

    void handleExceptionMatchExpr( AssertionHandler&amp; handler, std::string const&amp; str, StringRef matcherString );

} // namespace Catch

// end catch_assertionhandler.h
// start catch_message.h

#include &lt;string&gt;
#include &lt;sstream&gt;

namespace Catch {

    struct MessageInfo {
        MessageInfo(    std::string const&amp; _macroName,
                        SourceLineInfo const&amp; _lineInfo,
                        ResultWas::OfType _type );

        std::string macroName;
        std::string message;
        SourceLineInfo lineInfo;
        ResultWas::OfType type;
        unsigned int sequence;

        bool operator == ( MessageInfo const&amp; other ) const;
        bool operator &lt; ( MessageInfo const&amp; other ) const;
    private:
        static unsigned int globalCount;
    };

    struct MessageStream {

        template&lt;typename T&gt;
        MessageStream&amp; operator &lt;&lt; ( T const&amp; value ) {
            m_stream &lt;&lt; value;
            return *this;
        }

        // !TBD reuse a global/ thread-local stream
        std::ostringstream m_stream;
    };

    struct MessageBuilder : MessageStream {
        MessageBuilder( std::string const&amp; macroName,
                        SourceLineInfo const&amp; lineInfo,
                        ResultWas::OfType type );

        template&lt;typename T&gt;
        MessageBuilder&amp; operator &lt;&lt; ( T const&amp; value ) {
            m_stream &lt;&lt; value;
            return *this;
        }

        MessageInfo m_info;
    };

    class ScopedMessage {
    public:
        ScopedMessage( MessageBuilder const&amp; builder );
        ~ScopedMessage();

        MessageInfo m_info;
    };

} // end namespace Catch

// end catch_message.h
// start catch_interfaces_capture.h

#include &lt;string&gt;

namespace Catch {

    class AssertionResult;
    struct AssertionInfo;
    struct SectionInfo;
    struct SectionEndInfo;
    struct MessageInfo;
    struct Counts;
    struct BenchmarkInfo;
    struct BenchmarkStats;

    struct IResultCapture {

        virtual ~IResultCapture();

        virtual void assertionStarting( AssertionInfo const&amp; info ) = 0;
        virtual void assertionEnded( AssertionResult const&amp; result ) = 0;
        virtual bool sectionStarted(    SectionInfo const&amp; sectionInfo,
                                        Counts&amp; assertions ) = 0;
        virtual void sectionEnded( SectionEndInfo const&amp; endInfo ) = 0;
        virtual void sectionEndedEarly( SectionEndInfo const&amp; endInfo ) = 0;

        virtual void benchmarkStarting( BenchmarkInfo const&amp; info ) = 0;
        virtual void benchmarkEnded( BenchmarkStats const&amp; stats ) = 0;

        virtual void pushScopedMessage( MessageInfo const&amp; message ) = 0;
        virtual void popScopedMessage( MessageInfo const&amp; message ) = 0;

        virtual std::string getCurrentTestName() const = 0;
        virtual const AssertionResult* getLastResult() const = 0;

        virtual void exceptionEarlyReported() = 0;

        virtual void handleFatalErrorCondition( StringRef message ) = 0;

        virtual bool lastAssertionPassed() = 0;
        virtual void assertionPassed() = 0;
        virtual void assertionRun() = 0;
    };

    IResultCapture&amp; getResultCapture();
}

// end catch_interfaces_capture.h
// start catch_debugger.h

namespace Catch {
    bool isDebuggerActive();
}

#ifdef CATCH_PLATFORM_MAC

    #define CATCH_TRAP() __asm__("int $3\n" : : ) /* NOLINT */

#elif defined(CATCH_PLATFORM_LINUX)
    // If we can use inline assembler, do it because this allows us to break
    // directly at the location of the failing check instead of breaking inside
    // raise() called from it, i.e. one stack frame below.
    #if defined(__GNUC__) &amp;&amp; (defined(__i386) || defined(__x86_64))
        #define CATCH_TRAP() asm volatile ("int $3") /* NOLINT */
    #else // Fall back to the generic way.
        #include &lt;signal.h&gt;

        #define CATCH_TRAP() raise(SIGTRAP)
    #endif
#elif defined(_MSC_VER)
    #define CATCH_TRAP() __debugbreak()
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) void __stdcall DebugBreak();
    #define CATCH_TRAP() DebugBreak()
#endif

#ifdef CATCH_TRAP
    #define CATCH_BREAK_INTO_DEBUGGER() if( Catch::isDebuggerActive() ) { CATCH_TRAP(); }
#else
    #define CATCH_BREAK_INTO_DEBUGGER() Catch::alwaysTrue();
#endif

// end catch_debugger.h
#if !defined(CATCH_CONFIG_DISABLE)

#if !defined(CATCH_CONFIG_DISABLE_STRINGIFICATION)
  #define CATCH_INTERNAL_STRINGIFY(...) #__VA_ARGS__
#else
  #define CATCH_INTERNAL_STRINGIFY(...) "Disabled by CATCH_CONFIG_DISABLE_STRINGIFICATION"
#endif

#if defined(CATCH_CONFIG_FAST_COMPILE)
///////////////////////////////////////////////////////////////////////////////
// We can speedup compilation significantly by breaking into debugger lower in
// the callstack, because then we don't have to expand CATCH_BREAK_INTO_DEBUGGER
// macro in each assertion
#define INTERNAL_CATCH_REACT( handler ) \
    handler.reactWithDebugBreak();

///////////////////////////////////////////////////////////////////////////////
// Another way to speed-up compilation is to omit local try-catch for REQUIRE*
// macros.
// This can potentially cause false negative, if the test code catches
// the exception before it propagates back up to the runner.
#define INTERNAL_CATCH_TRY( capturer ) capturer.setExceptionGuard();
#define INTERNAL_CATCH_CATCH( capturer ) capturer.unsetExceptionGuard();

#else // CATCH_CONFIG_FAST_COMPILE

///////////////////////////////////////////////////////////////////////////////
// In the event of a failure works out if the debugger needs to be invoked
// and/or an exception thrown and takes appropriate action.
// This needs to be done as a macro so the debugger will stop in the user
// source code rather than in Catch library code
#define INTERNAL_CATCH_REACT( handler ) \
    if( handler.shouldDebugBreak() ) CATCH_BREAK_INTO_DEBUGGER(); \
    handler.reactWithoutDebugBreak();

#define INTERNAL_CATCH_TRY( capturer ) try
#define INTERNAL_CATCH_CATCH( capturer ) catch(...) { capturer.useActiveException(); }

#endif

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        INTERNAL_CATCH_TRY( catchAssertionHandler ) { \
            CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            catchAssertionHandler.handle( Catch::Decomposer() &lt;= __VA_ARGS__ ); \
            CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::isTrue( false &amp;&amp; static_cast&lt;bool&gt;( !!(__VA_ARGS__) ) ) ) // the expression here is never evaluated at runtime but it forces the compiler to give it a look
    // The double negation silences MSVC's C4800 warning, the static_cast forces short-circuit evaluation if the type has overloaded &amp;&amp;.

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_IF( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ELSE( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( !Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        try { \
            static_cast&lt;void&gt;(__VA_ARGS__); \
            catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
        } \
        catch( ... ) { \
            catchAssertionHandler.useActiveException(); \
        } \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__); \
                catchAssertionHandler.handle( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
            } \
        else \
            catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( macroName, exceptionType, resultDisposition, expr ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(expr) ", " CATCH_INTERNAL_STRINGIFY(exceptionType), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(expr); \
                catchAssertionHandler.handle( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( exceptionType const&amp; ) { \
                catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
            } \
            catch( ... ) { \
                catchAssertionHandler.useActiveException(); \
            } \
        else \
            catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( macroName, messageType, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, "", resultDisposition ); \
        catchAssertionHandler.handle( messageType, ( Catch::MessageStream() &lt;&lt; __VA_ARGS__ + ::Catch::StreamEndStop() ).m_stream.str() ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_INFO( macroName, log ) \
    Catch::ScopedMessage INTERNAL_CATCH_UNIQUE_NAME( scopedMessage ) = Catch::MessageBuilder( macroName, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) &lt;&lt; log;

///////////////////////////////////////////////////////////////////////////////
// Although this is matcher-based, it can be used with just a string
#define INTERNAL_CATCH_THROWS_STR_MATCHES( macroName, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__); \
                catchAssertionHandler.handle( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( ... ) { \
                handleExceptionMatchExpr( catchAssertionHandler, matcher, #matcher ); \
            } \
        else \
            catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

#endif // CATCH_CONFIG_DISABLE

// end catch_capture.hpp
// start catch_section.h

// start catch_section_info.h

// start catch_totals.h

#include &lt;cstddef&gt;

namespace Catch {

    struct Counts {
        Counts operator - ( Counts const&amp; other ) const;
        Counts&amp; operator += ( Counts const&amp; other );

        std::size_t total() const;
        bool allPassed() const;
        bool allOk() const;

        std::size_t passed = 0;
        std::size_t failed = 0;
        std::size_t failedButOk = 0;
    };

    struct Totals {

        Totals operator - ( Totals const&amp; other ) const;
        Totals&amp; operator += ( Totals const&amp; other );

        Totals delta( Totals const&amp; prevTotals ) const;

        Counts assertions;
        Counts testCases;
    };
}

// end catch_totals.h
#include &lt;string&gt;

namespace Catch {

    struct SectionInfo {
        SectionInfo
            (   SourceLineInfo const&amp; _lineInfo,
                std::string const&amp; _name,
                std::string const&amp; _description = std::string() );

        std::string name;
        std::string description;
        SourceLineInfo lineInfo;
    };

    struct SectionEndInfo {
        SectionEndInfo( SectionInfo const&amp; _sectionInfo, Counts const&amp; _prevAssertions, double _durationInSeconds );

        SectionInfo sectionInfo;
        Counts prevAssertions;
        double durationInSeconds;
    };

} // end namespace Catch

// end catch_section_info.h
// start catch_timer.h

#include &lt;cstdint&gt;

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -&gt; uint64_t;
    auto getEstimatedClockResolution() -&gt; uint64_t;

    class Timer {
        uint64_t m_nanoseconds = 0;
    public:
        void start();
        auto getElapsedNanoseconds() const -&gt; unsigned int;
        auto getElapsedMicroseconds() const -&gt; unsigned int;
        auto getElapsedMilliseconds() const -&gt; unsigned int;
        auto getElapsedSeconds() const -&gt; double;
    };

} // namespace Catch

// end catch_timer.h
#include &lt;string&gt;

namespace Catch {

    class Section : NonCopyable {
    public:
        Section( SectionInfo const&amp; info );
        ~Section();

        // This indicates whether the section should be executed or not
        explicit operator bool() const;

    private:
        SectionInfo m_info;

        std::string m_name;
        Counts m_assertions;
        bool m_sectionIncluded;
        Timer m_timer;
    };

} // end namespace Catch

    #define INTERNAL_CATCH_SECTION( ... ) \
        if( Catch::Section const&amp; INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, __VA_ARGS__ ) )

// end catch_section.h
// start catch_benchmark.h

#include &lt;cstdint&gt;
#include &lt;string&gt;

namespace Catch {

    class BenchmarkLooper {

        std::string m_name;
        std::size_t m_count = 0;
        std::size_t m_iterationsToRun = 1;
        uint64_t m_resolution;
        Timer m_timer;

        static auto getResolution() -&gt; uint64_t;
    public:
        // Keep most of this inline as it's on the code path that is being timed
        BenchmarkLooper( StringRef name )
        :   m_name( name ),
            m_resolution( getResolution() )
        {
            reportStart();
            m_timer.start();
        }

        explicit operator bool() {
            if( m_count &lt; m_iterationsToRun )
                return true;
            return needsMoreIterations();
        }

        void increment() {
            ++m_count;
        }

        void reportStart();
        auto needsMoreIterations() -&gt; bool;
    };

} // end namespace Catch

#define BENCHMARK( name ) \
    for( Catch::BenchmarkLooper looper( name ); looper; looper.increment() )

// end catch_benchmark.h
// start catch_interfaces_exception.h

// start catch_interfaces_registry_hub.h

#include &lt;string&gt;
#include &lt;memory&gt;

namespace Catch {

    class TestCase;
    struct ITestCaseRegistry;
    struct IExceptionTranslatorRegistry;
    struct IExceptionTranslator;
    struct IReporterRegistry;
    struct IReporterFactory;
    struct ITagAliasRegistry;
    class StartupExceptionRegistry;

    using IReporterFactoryPtr = std::shared_ptr&lt;IReporterFactory&gt;;

    struct IRegistryHub {
        virtual ~IRegistryHub();

        virtual IReporterRegistry const&amp; getReporterRegistry() const = 0;
        virtual ITestCaseRegistry const&amp; getTestCaseRegistry() const = 0;
        virtual ITagAliasRegistry const&amp; getTagAliasRegistry() const = 0;

        virtual IExceptionTranslatorRegistry&amp; getExceptionTranslatorRegistry() = 0;

        virtual StartupExceptionRegistry const&amp; getStartupExceptionRegistry() const = 0;
    };

    struct IMutableRegistryHub {
        virtual ~IMutableRegistryHub();
        virtual void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) = 0;
        virtual void registerListener( IReporterFactoryPtr const&amp; factory ) = 0;
        virtual void registerTest( TestCase const&amp; testInfo ) = 0;
        virtual void registerTranslator( const IExceptionTranslator* translator ) = 0;
        virtual void registerTagAlias( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) = 0;
        virtual void registerStartupException() noexcept = 0;
    };

    IRegistryHub&amp; getRegistryHub();
    IMutableRegistryHub&amp; getMutableRegistryHub();
    void cleanUp();
    std::string translateActiveException();

}

// end catch_interfaces_registry_hub.h
#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TRANSLATE_EXCEPTION_NO_REG( translatorName, signature) \
        static std::string translatorName( signature )
#endif

#include &lt;exception&gt;
#include &lt;string&gt;
#include &lt;vector&gt;

namespace Catch {
    using exceptionTranslateFunction = std::string(*)();

    struct IExceptionTranslator;
    using ExceptionTranslators = std::vector&lt;std::unique_ptr&lt;IExceptionTranslator const&gt;&gt;;

    struct IExceptionTranslator {
        virtual ~IExceptionTranslator();
        virtual std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const = 0;
    };

    struct IExceptionTranslatorRegistry {
        virtual ~IExceptionTranslatorRegistry();

        virtual std::string translateActiveException() const = 0;
    };

    class ExceptionTranslatorRegistrar {
        template&lt;typename T&gt;
        class ExceptionTranslator : public IExceptionTranslator {
        public:

            ExceptionTranslator( std::string(*translateFunction)( T&amp; ) )
            : m_translateFunction( translateFunction )
            {}

            std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const override {
                try {
                    if( it == itEnd )
                        std::rethrow_exception(std::current_exception());
                    else
                        return (*it)-&gt;translate( it+1, itEnd );
                }
                catch( T&amp; ex ) {
                    return m_translateFunction( ex );
                }
            }

        protected:
            std::string(*m_translateFunction)( T&amp; );
        };

    public:
        template&lt;typename T&gt;
        ExceptionTranslatorRegistrar( std::string(*translateFunction)( T&amp; ) ) {
            getMutableRegistryHub().registerTranslator
                ( new ExceptionTranslator&lt;T&gt;( translateFunction ) );
        }
    };
}

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TRANSLATE_EXCEPTION2( translatorName, signature ) \
    static std::string translatorName( signature ); \
    namespace{ Catch::ExceptionTranslatorRegistrar INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionRegistrar )( &amp;translatorName ); }\
    static std::string translatorName( signature )

#define INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION2( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// end catch_interfaces_exception.h
// start catch_approx.h

// start catch_enforce.h

#include &lt;sstream&gt;
#include &lt;stdexcept&gt;

#define CATCH_PREPARE_EXCEPTION( type, msg ) \
    type( static_cast&lt;std::ostringstream&amp;&amp;&gt;( std::ostringstream() &lt;&lt; msg ).str() )
#define CATCH_INTERNAL_ERROR( msg ) \
    throw CATCH_PREPARE_EXCEPTION( std::logic_error, CATCH_INTERNAL_LINEINFO &lt;&lt; ": Internal Catch error: " &lt;&lt; msg);
#define CATCH_ERROR( msg ) \
    throw CATCH_PREPARE_EXCEPTION( std::domain_error, msg )
#define CATCH_ENFORCE( condition, msg ) \
    do{ if( !(condition) ) CATCH_ERROR( msg ); } while(false)

// end catch_enforce.h
#include &lt;type_traits&gt;

namespace Catch {
namespace Detail {

    class Approx {
    private:
        bool equalityComparisonImpl(double other) const;

    public:
        explicit Approx ( double value );

        static Approx custom();

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx operator()( T const&amp; value ) {
            Approx approx( static_cast&lt;double&gt;(value) );
            approx.epsilon( m_epsilon );
            approx.margin( m_margin );
            approx.scale( m_scale );
            return approx;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        explicit Approx( T const&amp; value ): Approx(static_cast&lt;double&gt;(value))
        {}

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator == ( const T&amp; lhs, Approx const&amp; rhs ) {
            auto lhs_v = static_cast&lt;double&gt;(lhs);
            return rhs.equalityComparisonImpl(lhs_v);
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator == ( Approx const&amp; lhs, const T&amp; rhs ) {
            return operator==( rhs, lhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator != ( T const&amp; lhs, Approx const&amp; rhs ) {
            return !operator==( lhs, rhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator != ( Approx const&amp; lhs, T const&amp; rhs ) {
            return !operator==( rhs, lhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &lt;= ( T const&amp; lhs, Approx const&amp; rhs ) {
            return static_cast&lt;double&gt;(lhs) &lt; rhs.m_value || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &lt;= ( Approx const&amp; lhs, T const&amp; rhs ) {
            return lhs.m_value &lt; static_cast&lt;double&gt;(rhs) || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &gt;= ( T const&amp; lhs, Approx const&amp; rhs ) {
            return static_cast&lt;double&gt;(lhs) &gt; rhs.m_value || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &gt;= ( Approx const&amp; lhs, T const&amp; rhs ) {
            return lhs.m_value &gt; static_cast&lt;double&gt;(rhs) || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; epsilon( T const&amp; newEpsilon ) {
            double epsilonAsDouble = static_cast&lt;double&gt;(newEpsilon);
            CATCH_ENFORCE(epsilonAsDouble &gt;= 0 &amp;&amp; epsilonAsDouble &lt;= 1.0,
                          "Invalid Approx::epsilon: " &lt;&lt; epsilonAsDouble
                          &lt;&lt; ", Approx::epsilon has to be between 0 and 1");
            m_epsilon = epsilonAsDouble;
            return *this;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; margin( T const&amp; newMargin ) {
            double marginAsDouble = static_cast&lt;double&gt;(newMargin);
            CATCH_ENFORCE(marginAsDouble &gt;= 0,
                          "Invalid Approx::margin: " &lt;&lt; marginAsDouble
                          &lt;&lt; ", Approx::Margin has to be non-negative.");
            m_margin = marginAsDouble;
            return *this;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; scale( T const&amp; newScale ) {
            m_scale = static_cast&lt;double&gt;(newScale);
            return *this;
        }

        std::string toString() const;

    private:
        double m_epsilon;
        double m_margin;
        double m_scale;
        double m_value;
    };
}

template&lt;&gt;
struct StringMaker&lt;Catch::Detail::Approx&gt; {
    static std::string convert(Catch::Detail::Approx const&amp; value);
};

} // end namespace Catch

// end catch_approx.h
// start catch_string_manip.h

#include &lt;string&gt;
#include &lt;iosfwd&gt;

namespace Catch {

    bool startsWith( std::string const&amp; s, std::string const&amp; prefix );
    bool startsWith( std::string const&amp; s, char prefix );
    bool endsWith( std::string const&amp; s, std::string const&amp; suffix );
    bool endsWith( std::string const&amp; s, char suffix );
    bool contains( std::string const&amp; s, std::string const&amp; infix );
    void toLowerInPlace( std::string&amp; s );
    std::string toLower( std::string const&amp; s );
    std::string trim( std::string const&amp; str );
    bool replaceInPlace( std::string&amp; str, std::string const&amp; replaceThis, std::string const&amp; withThis );

    struct pluralise {
        pluralise( std::size_t count, std::string const&amp; label );

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, pluralise const&amp; pluraliser );

        std::size_t m_count;
        std::string m_label;
    };
}

// end catch_string_manip.h
#ifndef CATCH_CONFIG_DISABLE_MATCHERS
// start catch_capture_matchers.h

// start catch_matchers.h

#include &lt;string&gt;
#include &lt;vector&gt;

namespace Catch {
namespace Matchers {
    namespace Impl {

        template&lt;typename ArgT&gt; struct MatchAllOf;
        template&lt;typename ArgT&gt; struct MatchAnyOf;
        template&lt;typename ArgT&gt; struct MatchNotOf;

        class MatcherUntypedBase {
        public:
            MatcherUntypedBase() = default;
            MatcherUntypedBase ( MatcherUntypedBase const&amp; ) = default;
            MatcherUntypedBase&amp; operator = ( MatcherUntypedBase const&amp; ) = delete;
            std::string toString() const;

        protected:
            virtual ~MatcherUntypedBase();
            virtual std::string describe() const = 0;
            mutable std::string m_cachedToString;
        };

        template&lt;typename ObjectT&gt;
        struct MatcherMethod {
            virtual bool match( ObjectT const&amp; arg ) const = 0;
        };
        template&lt;typename PtrT&gt;
        struct MatcherMethod&lt;PtrT*&gt; {
            virtual bool match( PtrT* arg ) const = 0;
        };

        template&lt;typename ObjectT, typename ComparatorT = ObjectT&gt;
        struct MatcherBase : MatcherUntypedBase, MatcherMethod&lt;ObjectT&gt; {

            MatchAllOf&lt;ComparatorT&gt; operator &amp;&amp; ( MatcherBase const&amp; other ) const;
            MatchAnyOf&lt;ComparatorT&gt; operator || ( MatcherBase const&amp; other ) const;
            MatchNotOf&lt;ComparatorT&gt; operator ! () const;
        };

        template&lt;typename ArgT&gt;
        struct MatchAllOf : MatcherBase&lt;ArgT&gt; {
            bool match( ArgT const&amp; arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (!matcher-&gt;match(arg))
                        return false;
                }
                return true;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " and ";
                    description += matcher-&gt;toString();
                }
                description += " )";
                return description;
            }

            MatchAllOf&lt;ArgT&gt;&amp; operator &amp;&amp; ( MatcherBase&lt;ArgT&gt; const&amp; other ) {
                m_matchers.push_back( &amp;other );
                return *this;
            }

            std::vector&lt;MatcherBase&lt;ArgT&gt; const*&gt; m_matchers;
        };
        template&lt;typename ArgT&gt;
        struct MatchAnyOf : MatcherBase&lt;ArgT&gt; {

            bool match( ArgT const&amp; arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (matcher-&gt;match(arg))
                        return true;
                }
                return false;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " or ";
                    description += matcher-&gt;toString();
                }
                description += " )";
                return description;
            }

            MatchAnyOf&lt;ArgT&gt;&amp; operator || ( MatcherBase&lt;ArgT&gt; const&amp; other ) {
                m_matchers.push_back( &amp;other );
                return *this;
            }

            std::vector&lt;MatcherBase&lt;ArgT&gt; const*&gt; m_matchers;
        };

        template&lt;typename ArgT&gt;
        struct MatchNotOf : MatcherBase&lt;ArgT&gt; {

            MatchNotOf( MatcherBase&lt;ArgT&gt; const&amp; underlyingMatcher ) : m_underlyingMatcher( underlyingMatcher ) {}

            bool match( ArgT const&amp; arg ) const override {
                return !m_underlyingMatcher.match( arg );
            }

            std::string describe() const override {
                return "not " + m_underlyingMatcher.toString();
            }
            MatcherBase&lt;ArgT&gt; const&amp; m_underlyingMatcher;
        };

        template&lt;typename ObjectT, typename ComparatorT&gt;
        MatchAllOf&lt;ComparatorT&gt; MatcherBase&lt;ObjectT, ComparatorT&gt;::operator &amp;&amp; ( MatcherBase const&amp; other ) const {
            return MatchAllOf&lt;ComparatorT&gt;() &amp;&amp; *this &amp;&amp; other;
        }
        template&lt;typename ObjectT, typename ComparatorT&gt;
        MatchAnyOf&lt;ComparatorT&gt; MatcherBase&lt;ObjectT, ComparatorT&gt;::operator || ( MatcherBase const&amp; other ) const {
            return MatchAnyOf&lt;ComparatorT&gt;() || *this || other;
        }
        template&lt;typename ObjectT, typename ComparatorT&gt;
        MatchNotOf&lt;ComparatorT&gt; MatcherBase&lt;ObjectT, ComparatorT&gt;::operator ! () const {
            return MatchNotOf&lt;ComparatorT&gt;( *this );
        }

    } // namespace Impl

} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch

// end catch_matchers.h
// start catch_matchers_string.h

#include &lt;string&gt;

namespace Catch {
namespace Matchers {

    namespace StdString {

        struct CasedString
        {
            CasedString( std::string const&amp; str, CaseSensitive::Choice caseSensitivity );
            std::string adjustString( std::string const&amp; str ) const;
            std::string caseSensitivitySuffix() const;

            CaseSensitive::Choice m_caseSensitivity;
            std::string m_str;
        };

        struct StringMatcherBase : MatcherBase&lt;std::string&gt; {
            StringMatcherBase( std::string const&amp; operation, CasedString const&amp; comparator );
            std::string describe() const override;

            CasedString m_comparator;
            std::string m_operation;
        };

        struct EqualsMatcher : StringMatcherBase {
            EqualsMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct ContainsMatcher : StringMatcherBase {
            ContainsMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct StartsWithMatcher : StringMatcherBase {
            StartsWithMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct EndsWithMatcher : StringMatcherBase {
            EndsWithMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };

    } // namespace StdString

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    StdString::EqualsMatcher Equals( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::ContainsMatcher Contains( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::EndsWithMatcher EndsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::StartsWithMatcher StartsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );

} // namespace Matchers
} // namespace Catch

// end catch_matchers_string.h
// start catch_matchers_vector.h

namespace Catch {
namespace Matchers {

    namespace Vector {

        template&lt;typename T&gt;
        struct ContainsElementMatcher : MatcherBase&lt;std::vector&lt;T&gt;, T&gt; {

            ContainsElementMatcher(T const &amp;comparator) : m_comparator( comparator) {}

            bool match(std::vector&lt;T&gt; const &amp;v) const override {
                for (auto const&amp; el : v) {
                    if (el == m_comparator) {
                        return true;
                    }
                }
                return false;
            }

            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            T const&amp; m_comparator;
        };

        template&lt;typename T&gt;
        struct ContainsMatcher : MatcherBase&lt;std::vector&lt;T&gt;, std::vector&lt;T&gt; &gt; {

            ContainsMatcher(std::vector&lt;T&gt; const &amp;comparator) : m_comparator( comparator ) {}

            bool match(std::vector&lt;T&gt; const &amp;v) const override {
                // !TBD: see note in EqualsMatcher
                if (m_comparator.size() &gt; v.size())
                    return false;
                for (auto const&amp; comparator : m_comparator) {
                    auto present = false;
                    for (const auto&amp; el : v) {
                        if (el == comparator) {
                            present = true;
                            break;
                        }
                    }
                    if (!present) {
                        return false;
                    }
                }
                return true;
            }
            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            std::vector&lt;T&gt; const&amp; m_comparator;
        };

        template&lt;typename T&gt;
        struct EqualsMatcher : MatcherBase&lt;std::vector&lt;T&gt;, std::vector&lt;T&gt; &gt; {

            EqualsMatcher(std::vector&lt;T&gt; const &amp;comparator) : m_comparator( comparator ) {}

            bool match(std::vector&lt;T&gt; const &amp;v) const override {
                // !TBD: This currently works if all elements can be compared using !=
                // - a more general approach would be via a compare template that defaults
                // to using !=. but could be specialised for, e.g. std::vector&lt;T&gt; etc
                // - then just call that directly
                if (m_comparator.size() != v.size())
                    return false;
                for (std::size_t i = 0; i &lt; v.size(); ++i)
                    if (m_comparator[i] != v[i])
                        return false;
                return true;
            }
            std::string describe() const override {
                return "Equals: " + ::Catch::Detail::stringify( m_comparator );
            }
            std::vector&lt;T&gt; const&amp; m_comparator;
        };

    } // namespace Vector

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    template&lt;typename T&gt;
    Vector::ContainsMatcher&lt;T&gt; Contains( std::vector&lt;T&gt; const&amp; comparator ) {
        return Vector::ContainsMatcher&lt;T&gt;( comparator );
    }

    template&lt;typename T&gt;
    Vector::ContainsElementMatcher&lt;T&gt; VectorContains( T const&amp; comparator ) {
        return Vector::ContainsElementMatcher&lt;T&gt;( comparator );
    }

    template&lt;typename T&gt;
    Vector::EqualsMatcher&lt;T&gt; Equals( std::vector&lt;T&gt; const&amp; comparator ) {
        return Vector::EqualsMatcher&lt;T&gt;( comparator );
    }

} // namespace Matchers
} // namespace Catch

// end catch_matchers_vector.h
namespace Catch {

    template&lt;typename ArgT, typename MatcherT&gt;
    class MatchExpr : public ITransientExpression {
        ArgT const&amp; m_arg;
        MatcherT m_matcher;
        StringRef m_matcherString;
        bool m_result;
    public:
        MatchExpr( ArgT const&amp; arg, MatcherT const&amp; matcher, StringRef matcherString )
        :   m_arg( arg ),
            m_matcher( matcher ),
            m_matcherString( matcherString ),
            m_result( matcher.match( arg ) )
        {}

        auto isBinaryExpression() const -&gt; bool  override { return true; }
        auto getResult() const -&gt; bool override { return m_result; }

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            auto matcherAsString = m_matcher.toString();
            os &lt;&lt; Catch::Detail::stringify( m_arg ) &lt;&lt; ' ';
            if( matcherAsString == Detail::unprintableString )
                os &lt;&lt; m_matcherString;
            else
                os &lt;&lt; matcherAsString;
        }
    };

    using StringMatcher = Matchers::Impl::MatcherBase&lt;std::string&gt;;

    void handleExceptionMatchExpr( AssertionHandler&amp; handler, StringMatcher const&amp; matcher, StringRef matcherString  );

    template&lt;typename ArgT, typename MatcherT&gt;
    auto makeMatchExpr( ArgT const&amp; arg, MatcherT const&amp; matcher, StringRef matcherString  ) -&gt; MatchExpr&lt;ArgT, MatcherT&gt; {
        return MatchExpr&lt;ArgT, MatcherT&gt;( arg, matcher, matcherString );
    }

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CHECK_THAT( macroName, matcher, resultDisposition, arg ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(arg) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        INTERNAL_CATCH_TRY( catchAssertionHandler ) { \
            catchAssertionHandler.handle( Catch::makeMatchExpr( arg, matcher, #matcher ) ); \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_MATCHES( macroName, exceptionType, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(exceptionType) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__ ); \
                catchAssertionHandler.handle( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( exceptionType const&amp; ex ) { \
                catchAssertionHandler.handle( Catch::makeMatchExpr( ex, matcher, #matcher ) ); \
            } \
            catch( ... ) { \
                catchAssertionHandler.useActiveException(); \
            } \
        else \
            catchAssertionHandler.handle( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( Catch::alwaysFalse() )

// end catch_capture_matchers.h
#endif

// These files are included here so the single_include script doesn't put them
// in the conditionally compiled sections
// start catch_test_case_info.h

#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace Catch {

    struct ITestInvoker;

    struct TestCaseInfo {
        enum SpecialProperties{
            None = 0,
            IsHidden = 1 &lt;&lt; 1,
            ShouldFail = 1 &lt;&lt; 2,
            MayFail = 1 &lt;&lt; 3,
            Throws = 1 &lt;&lt; 4,
            NonPortable = 1 &lt;&lt; 5,
            Benchmark = 1 &lt;&lt; 6
        };

        TestCaseInfo(   std::string const&amp; _name,
                        std::string const&amp; _className,
                        std::string const&amp; _description,
                        std::vector&lt;std::string&gt; const&amp; _tags,
                        SourceLineInfo const&amp; _lineInfo );

        friend void setTags( TestCaseInfo&amp; testCaseInfo, std::vector&lt;std::string&gt; tags );

        bool isHidden() const;
        bool throws() const;
        bool okToFail() const;
        bool expectedToFail() const;

        std::string tagsAsString() const;

        std::string name;
        std::string className;
        std::string description;
        std::vector&lt;std::string&gt; tags;
        std::vector&lt;std::string&gt; lcaseTags;
        SourceLineInfo lineInfo;
        SpecialProperties properties;
    };

    class TestCase : public TestCaseInfo {
    public:

        TestCase( ITestInvoker* testCase, TestCaseInfo const&amp; info );

        TestCase withName( std::string const&amp; _newName ) const;

        void invoke() const;

        TestCaseInfo const&amp; getTestCaseInfo() const;

        bool operator == ( TestCase const&amp; other ) const;
        bool operator &lt; ( TestCase const&amp; other ) const;

    private:
        std::shared_ptr&lt;ITestInvoker&gt; test;
    };

    TestCase makeTestCase(  ITestInvoker* testCase,
                            std::string const&amp; className,
                            std::string const&amp; name,
                            std::string const&amp; description,
                            SourceLineInfo const&amp; lineInfo );
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_case_info.h
// start catch_interfaces_runner.h

namespace Catch {

    struct IRunner {
        virtual ~IRunner();
        virtual bool aborting() const = 0;
    };
}

// end catch_interfaces_runner.h

#ifdef __OBJC__
// start catch_objc.hpp

#import &lt;objc/runtime.h&gt;

#include &lt;string&gt;

// NB. Any general catch headers included here must be included
// in catch.hpp first to make sure they are included by the single
// header for non obj-usage

///////////////////////////////////////////////////////////////////////////////
// This protocol is really only here for (self) documenting purposes, since
// all its methods are optional.
@protocol OcFixture

@optional

-(void) setUp;
-(void) tearDown;

@end

namespace Catch {

    class OcMethod : public ITestInvoker {

    public:
        OcMethod( Class cls, SEL sel ) : m_cls( cls ), m_sel( sel ) {}

        virtual void invoke() const {
            id obj = [[m_cls alloc] init];

            performOptionalSelector( obj, @selector(setUp)  );
            performOptionalSelector( obj, m_sel );
            performOptionalSelector( obj, @selector(tearDown)  );

            arcSafeRelease( obj );
        }
    private:
        virtual ~OcMethod() {}

        Class m_cls;
        SEL m_sel;
    };

    namespace Detail{

        inline std::string getAnnotation(   Class cls,
                                            std::string const&amp; annotationName,
                                            std::string const&amp; testCaseName ) {
            NSString* selStr = [[NSString alloc] initWithFormat:@"Catch_%s_%s", annotationName.c_str(), testCaseName.c_str()];
            SEL sel = NSSelectorFromString( selStr );
            arcSafeRelease( selStr );
            id value = performOptionalSelector( cls, sel );
            if( value )
                return [(NSString*)value UTF8String];
            return "";
        }
    }

    inline std::size_t registerTestMethods() {
        std::size_t noTestMethods = 0;
        int noClasses = objc_getClassList( nullptr, 0 );

        Class* classes = (CATCH_UNSAFE_UNRETAINED Class *)malloc( sizeof(Class) * noClasses);
        objc_getClassList( classes, noClasses );

        for( int c = 0; c &lt; noClasses; c++ ) {
            Class cls = classes[c];
            {
                u_int count;
                Method* methods = class_copyMethodList( cls, &amp;count );
                for( u_int m = 0; m &lt; count ; m++ ) {
                    SEL selector = method_getName(methods[m]);
                    std::string methodName = sel_getName(selector);
                    if( startsWith( methodName, "Catch_TestCase_" ) ) {
                        std::string testCaseName = methodName.substr( 15 );
                        std::string name = Detail::getAnnotation( cls, "Name", testCaseName );
                        std::string desc = Detail::getAnnotation( cls, "Description", testCaseName );
                        const char* className = class_getName( cls );

                        getMutableRegistryHub().registerTest( makeTestCase( new OcMethod( cls, selector ), className, name.c_str(), desc.c_str(), SourceLineInfo("",0) ) );
                        noTestMethods++;
                    }
                }
                free(methods);
            }
        }
        return noTestMethods;
    }

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

    namespace Matchers {
        namespace Impl {
        namespace NSStringMatchers {

            struct StringHolder : MatcherBase&lt;NSString*&gt;{
                StringHolder( NSString* substr ) : m_substr( [substr copy] ){}
                StringHolder( StringHolder const&amp; other ) : m_substr( [other.m_substr copy] ){}
                StringHolder() {
                    arcSafeRelease( m_substr );
                }

                bool match( NSString* arg ) const override {
                    return false;
                }

                NSString* CATCH_ARC_STRONG m_substr;
            };

            struct Equals : StringHolder {
                Equals( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str isEqualToString:m_substr];
                }

                std::string describe() const override {
                    return "equals string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct Contains : StringHolder {
                Contains( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location != NSNotFound;
                }

                std::string describe() const override {
                    return "contains string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct StartsWith : StringHolder {
                StartsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location == 0;
                }

                std::string describe() const override {
                    return "starts with: " + Catch::Detail::stringify( m_substr );
                }
            };
            struct EndsWith : StringHolder {
                EndsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location == [str length] - [m_substr length];
                }

                std::string describe() const override {
                    return "ends with: " + Catch::Detail::stringify( m_substr );
                }
            };

        } // namespace NSStringMatchers
        } // namespace Impl

        inline Impl::NSStringMatchers::Equals
            Equals( NSString* substr ){ return Impl::NSStringMatchers::Equals( substr ); }

        inline Impl::NSStringMatchers::Contains
            Contains( NSString* substr ){ return Impl::NSStringMatchers::Contains( substr ); }

        inline Impl::NSStringMatchers::StartsWith
            StartsWith( NSString* substr ){ return Impl::NSStringMatchers::StartsWith( substr ); }

        inline Impl::NSStringMatchers::EndsWith
            EndsWith( NSString* substr ){ return Impl::NSStringMatchers::EndsWith( substr ); }

    } // namespace Matchers

    using namespace Matchers;

#endif // CATCH_CONFIG_DISABLE_MATCHERS

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define OC_MAKE_UNIQUE_NAME( root, uniqueSuffix ) root##uniqueSuffix
#define OC_TEST_CASE2( name, desc, uniqueSuffix ) \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Name_test_, uniqueSuffix ) \
{ \
return @ name; \
} \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Description_test_, uniqueSuffix ) \
{ \
return @ desc; \
} \
-(void) OC_MAKE_UNIQUE_NAME( Catch_TestCase_test_, uniqueSuffix )

#define OC_TEST_CASE( name, desc ) OC_TEST_CASE2( name, desc, __LINE__ )

// end catch_objc.hpp
#endif

#ifdef CATCH_CONFIG_EXTERNAL_INTERFACES
// start catch_external_interfaces.h

// start catch_reporter_bases.hpp

// start catch_interfaces_reporter.h

// start catch_config.hpp

// start catch_test_spec_parser.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_test_spec.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_wildcard_pattern.h

namespace Catch
{
    class WildcardPattern {
        enum WildcardPosition {
            NoWildcard = 0,
            WildcardAtStart = 1,
            WildcardAtEnd = 2,
            WildcardAtBothEnds = WildcardAtStart | WildcardAtEnd
        };

    public:

        WildcardPattern( std::string const&amp; pattern, CaseSensitive::Choice caseSensitivity );
        virtual ~WildcardPattern() = default;
        virtual bool matches( std::string const&amp; str ) const;

    private:
        std::string adjustCase( std::string const&amp; str ) const;
        CaseSensitive::Choice m_caseSensitivity;
        WildcardPosition m_wildcard = NoWildcard;
        std::string m_pattern;
    };
}

// end catch_wildcard_pattern.h
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    class TestSpec {
        struct Pattern {
            virtual ~Pattern();
            virtual bool matches( TestCaseInfo const&amp; testCase ) const = 0;
        };
        using PatternPtr = std::shared_ptr&lt;Pattern&gt;;

        class NamePattern : public Pattern {
        public:
            NamePattern( std::string const&amp; name );
            virtual ~NamePattern();
            virtual bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            WildcardPattern m_wildcardPattern;
        };

        class TagPattern : public Pattern {
        public:
            TagPattern( std::string const&amp; tag );
            virtual ~TagPattern();
            virtual bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            std::string m_tag;
        };

        class ExcludedPattern : public Pattern {
        public:
            ExcludedPattern( PatternPtr const&amp; underlyingPattern );
            virtual ~ExcludedPattern();
            virtual bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            PatternPtr m_underlyingPattern;
        };

        struct Filter {
            std::vector&lt;PatternPtr&gt; m_patterns;

            bool matches( TestCaseInfo const&amp; testCase ) const;
        };

    public:
        bool hasFilters() const;
        bool matches( TestCaseInfo const&amp; testCase ) const;

    private:
        std::vector&lt;Filter&gt; m_filters;

        friend class TestSpecParser;
    };
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec.h
// start catch_interfaces_tag_alias_registry.h

#include &lt;string&gt;

namespace Catch {

    struct TagAlias;

    struct ITagAliasRegistry {
        virtual ~ITagAliasRegistry();
        // Nullptr if not present
        virtual TagAlias const* find( std::string const&amp; alias ) const = 0;
        virtual std::string expandAliases( std::string const&amp; unexpandedTestSpec ) const = 0;

        static ITagAliasRegistry const&amp; get();
    };

} // end namespace Catch

// end catch_interfaces_tag_alias_registry.h
namespace Catch {

    class TestSpecParser {
        enum Mode{ None, Name, QuotedName, Tag, EscapedName };
        Mode m_mode = None;
        bool m_exclusion = false;
        std::size_t m_start = std::string::npos, m_pos = 0;
        std::string m_arg;
        std::vector&lt;std::size_t&gt; m_escapeChars;
        TestSpec::Filter m_currentFilter;
        TestSpec m_testSpec;
        ITagAliasRegistry const* m_tagAliases = nullptr;

    public:
        TestSpecParser( ITagAliasRegistry const&amp; tagAliases );

        TestSpecParser&amp; parse( std::string const&amp; arg );
        TestSpec testSpec();

    private:
        void visitChar( char c );
        void startNewMode( Mode mode, std::size_t start );
        void escape();
        std::string subString() const;

        template&lt;typename T&gt;
        void addPattern() {
            std::string token = subString();
            for( std::size_t i = 0; i &lt; m_escapeChars.size(); ++i )
                token = token.substr( 0, m_escapeChars[i]-m_start-i ) + token.substr( m_escapeChars[i]-m_start-i+1 );
            m_escapeChars.clear();
            if( startsWith( token, "exclude:" ) ) {
                m_exclusion = true;
                token = token.substr( 8 );
            }
            if( !token.empty() ) {
                TestSpec::PatternPtr pattern = std::make_shared&lt;T&gt;( token );
                if( m_exclusion )
                    pattern = std::make_shared&lt;TestSpec::ExcludedPattern&gt;( pattern );
                m_currentFilter.m_patterns.push_back( pattern );
            }
            m_exclusion = false;
            m_mode = None;
        }

        void addFilter();
    };
    TestSpec parseTestSpec( std::string const&amp; arg );

} // namespace Catch

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec_parser.h
// start catch_interfaces_config.h

#include &lt;iosfwd&gt;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    enum class Verbosity {
        Quiet = 0,
        Normal,
        High
    };

    struct WarnAbout { enum What {
        Nothing = 0x00,
        NoAssertions = 0x01
    }; };

    struct ShowDurations { enum OrNot {
        DefaultForReporter,
        Always,
        Never
    }; };
    struct RunTests { enum InWhatOrder {
        InDeclarationOrder,
        InLexicographicalOrder,
        InRandomOrder
    }; };
    struct UseColour { enum YesOrNo {
        Auto,
        Yes,
        No
    }; };
    struct WaitForKeypress { enum When {
        Never,
        BeforeStart = 1,
        BeforeExit = 2,
        BeforeStartAndExit = BeforeStart | BeforeExit
    }; };

    class TestSpec;

    struct IConfig : NonCopyable {

        virtual ~IConfig();

        virtual bool allowThrows() const = 0;
        virtual std::ostream&amp; stream() const = 0;
        virtual std::string name() const = 0;
        virtual bool includeSuccessfulResults() const = 0;
        virtual bool shouldDebugBreak() const = 0;
        virtual bool warnAboutMissingAssertions() const = 0;
        virtual int abortAfter() const = 0;
        virtual bool showInvisibles() const = 0;
        virtual ShowDurations::OrNot showDurations() const = 0;
        virtual TestSpec const&amp; testSpec() const = 0;
        virtual RunTests::InWhatOrder runOrder() const = 0;
        virtual unsigned int rngSeed() const = 0;
        virtual int benchmarkResolutionMultiple() const = 0;
        virtual UseColour::YesOrNo useColour() const = 0;
        virtual std::vector&lt;std::string&gt; const&amp; getSectionsToRun() const = 0;
        virtual Verbosity verbosity() const = 0;
    };

    using IConfigPtr = std::shared_ptr&lt;IConfig const&gt;;
}

// end catch_interfaces_config.h
// Libstdc++ doesn't like incomplete classes for unique_ptr
// start catch_stream.h

// start catch_streambuf.h

#include &lt;streambuf&gt;

namespace Catch {

    class StreamBufBase : public std::streambuf {
    public:
        virtual ~StreamBufBase();
    };
}

// end catch_streambuf.h
#include &lt;streambuf&gt;
#include &lt;ostream&gt;
#include &lt;fstream&gt;
#include &lt;memory&gt;

namespace Catch {

    std::ostream&amp; cout();
    std::ostream&amp; cerr();
    std::ostream&amp; clog();

    struct IStream {
        virtual ~IStream();
        virtual std::ostream&amp; stream() const = 0;
    };

    class FileStream : public IStream {
        mutable std::ofstream m_ofs;
    public:
        FileStream( std::string const&amp; filename );
        ~FileStream() override = default;
    public: // IStream
        std::ostream&amp; stream() const override;
    };

    class CoutStream : public IStream {
        mutable std::ostream m_os;
    public:
        CoutStream();
        ~CoutStream() override = default;

    public: // IStream
        std::ostream&amp; stream() const override;
    };

    class DebugOutStream : public IStream {
        std::unique_ptr&lt;StreamBufBase&gt; m_streamBuf;
        mutable std::ostream m_os;
    public:
        DebugOutStream();
        ~DebugOutStream() override = default;

    public: // IStream
        std::ostream&amp; stream() const override;
    };
}

// end catch_stream.h

#include &lt;memory&gt;
#include &lt;vector&gt;
#include &lt;string&gt;

#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#define CATCH_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch {

    struct IStream;

    struct ConfigData {
        bool listTests = false;
        bool listTags = false;
        bool listReporters = false;
        bool listTestNamesOnly = false;

        bool showSuccessfulTests = false;
        bool shouldDebugBreak = false;
        bool noThrow = false;
        bool showHelp = false;
        bool showInvisibles = false;
        bool filenamesAsTags = false;
        bool libIdentify = false;

        int abortAfter = -1;
        unsigned int rngSeed = 0;
        int benchmarkResolutionMultiple = 100;

        Verbosity verbosity = Verbosity::Normal;
        WarnAbout::What warnings = WarnAbout::Nothing;
        ShowDurations::OrNot showDurations = ShowDurations::DefaultForReporter;
        RunTests::InWhatOrder runOrder = RunTests::InDeclarationOrder;
        UseColour::YesOrNo useColour = UseColour::Auto;
        WaitForKeypress::When waitForKeypress = WaitForKeypress::Never;

        std::string outputFilename;
        std::string name;
        std::string processName;

        std::vector&lt;std::string&gt; reporterNames;
        std::vector&lt;std::string&gt; testsOrTags;
        std::vector&lt;std::string&gt; sectionsToRun;
    };

    class Config : public IConfig {
    public:

        Config() = default;
        Config( ConfigData const&amp; data );
        virtual ~Config() = default;

        std::string const&amp; getFilename() const;

        bool listTests() const;
        bool listTestNamesOnly() const;
        bool listTags() const;
        bool listReporters() const;

        std::string getProcessName() const;

        std::vector&lt;std::string&gt; const&amp; getReporterNames() const;
        std::vector&lt;std::string&gt; const&amp; getSectionsToRun() const override;

        virtual TestSpec const&amp; testSpec() const override;

        bool showHelp() const;

        // IConfig interface
        bool allowThrows() const override;
        std::ostream&amp; stream() const override;
        std::string name() const override;
        bool includeSuccessfulResults() const override;
        bool warnAboutMissingAssertions() const override;
        ShowDurations::OrNot showDurations() const override;
        RunTests::InWhatOrder runOrder() const override;
        unsigned int rngSeed() const override;
        int benchmarkResolutionMultiple() const override;
        UseColour::YesOrNo useColour() const override;
        bool shouldDebugBreak() const override;
        int abortAfter() const override;
        bool showInvisibles() const override;
        Verbosity verbosity() const override;

    private:

        IStream const* openStream();
        ConfigData m_data;

        std::unique_ptr&lt;IStream const&gt; m_stream;
        TestSpec m_testSpec;
    };

} // end namespace Catch

// end catch_config.hpp
// start catch_assertionresult.h

#include &lt;string&gt;

namespace Catch {

    struct AssertionResultData
    {
        AssertionResultData() = delete;

        AssertionResultData( ResultWas::OfType _resultType, LazyExpression const&amp; _lazyExpression );

        std::string message;
        mutable std::string reconstructedExpression;
        LazyExpression lazyExpression;
        ResultWas::OfType resultType;

        std::string reconstructExpression() const;
    };

    class AssertionResult {
    public:
        AssertionResult() = delete;
        AssertionResult( AssertionInfo const&amp; info, AssertionResultData const&amp; data );

        bool isOk() const;
        bool succeeded() const;
        ResultWas::OfType getResultType() const;
        bool hasExpression() const;
        bool hasMessage() const;
        std::string getExpression() const;
        std::string getExpressionInMacro() const;
        bool hasExpandedExpression() const;
        std::string getExpandedExpression() const;
        std::string getMessage() const;
        SourceLineInfo getSourceInfo() const;
        std::string getTestMacroName() const;

    //protected:
        AssertionInfo m_info;
        AssertionResultData m_resultData;
    };

} // end namespace Catch

// end catch_assertionresult.h
// start catch_option.hpp

namespace Catch {

    // An optional type
    template&lt;typename T&gt;
    class Option {
    public:
        Option() : nullableValue( nullptr ) {}
        Option( T const&amp; _value )
        : nullableValue( new( storage ) T( _value ) )
        {}
        Option( Option const&amp; _other )
        : nullableValue( _other ? new( storage ) T( *_other ) : nullptr )
        {}

        ~Option() {
            reset();
        }

        Option&amp; operator= ( Option const&amp; _other ) {
            if( &amp;_other != this ) {
                reset();
                if( _other )
                    nullableValue = new( storage ) T( *_other );
            }
            return *this;
        }
        Option&amp; operator = ( T const&amp; _value ) {
            reset();
            nullableValue = new( storage ) T( _value );
            return *this;
        }

        void reset() {
            if( nullableValue )
                nullableValue-&gt;~T();
            nullableValue = nullptr;
        }

        T&amp; operator*() { return *nullableValue; }
        T const&amp; operator*() const { return *nullableValue; }
        T* operator-&gt;() { return nullableValue; }
        const T* operator-&gt;() const { return nullableValue; }

        T valueOr( T const&amp; defaultValue ) const {
            return nullableValue ? *nullableValue : defaultValue;
        }

        bool some() const { return nullableValue != nullptr; }
        bool none() const { return nullableValue == nullptr; }

        bool operator !() const { return nullableValue == nullptr; }
        explicit operator bool() const {
            return some();
        }

    private:
        T *nullableValue;
        alignas(alignof(T)) char storage[sizeof(T)];
    };

} // end namespace Catch

// end catch_option.hpp
#include &lt;string&gt;
#include &lt;iosfwd&gt;
#include &lt;map&gt;
#include &lt;set&gt;
#include &lt;memory&gt;

namespace Catch {

    struct ReporterConfig {
        explicit ReporterConfig( IConfigPtr const&amp; _fullConfig );

        ReporterConfig( IConfigPtr const&amp; _fullConfig, std::ostream&amp; _stream );

        std::ostream&amp; stream() const;
        IConfigPtr fullConfig() const;

    private:
        std::ostream* m_stream;
        IConfigPtr m_fullConfig;
    };

    struct ReporterPreferences {
        bool shouldRedirectStdOut = false;
    };

    template&lt;typename T&gt;
    struct LazyStat : Option&lt;T&gt; {
        LazyStat&amp; operator=( T const&amp; _value ) {
            Option&lt;T&gt;::operator=( _value );
            used = false;
            return *this;
        }
        void reset() {
            Option&lt;T&gt;::reset();
            used = false;
        }
        bool used = false;
    };

    struct TestRunInfo {
        TestRunInfo( std::string const&amp; _name );
        std::string name;
    };
    struct GroupInfo {
        GroupInfo(  std::string const&amp; _name,
                    std::size_t _groupIndex,
                    std::size_t _groupsCount );

        std::string name;
        std::size_t groupIndex;
        std::size_t groupsCounts;
    };

    struct AssertionStats {
        AssertionStats( AssertionResult const&amp; _assertionResult,
                        std::vector&lt;MessageInfo&gt; const&amp; _infoMessages,
                        Totals const&amp; _totals );

        AssertionStats( AssertionStats const&amp; )              = default;
        AssertionStats( AssertionStats &amp;&amp; )                  = default;
        AssertionStats&amp; operator = ( AssertionStats const&amp; ) = default;
        AssertionStats&amp; operator = ( AssertionStats &amp;&amp; )     = default;
        virtual ~AssertionStats();

        AssertionResult assertionResult;
        std::vector&lt;MessageInfo&gt; infoMessages;
        Totals totals;
    };

    struct SectionStats {
        SectionStats(   SectionInfo const&amp; _sectionInfo,
                        Counts const&amp; _assertions,
                        double _durationInSeconds,
                        bool _missingAssertions );
        SectionStats( SectionStats const&amp; )              = default;
        SectionStats( SectionStats &amp;&amp; )                  = default;
        SectionStats&amp; operator = ( SectionStats const&amp; ) = default;
        SectionStats&amp; operator = ( SectionStats &amp;&amp; )     = default;
        virtual ~SectionStats();

        SectionInfo sectionInfo;
        Counts assertions;
        double durationInSeconds;
        bool missingAssertions;
    };

    struct TestCaseStats {
        TestCaseStats(  TestCaseInfo const&amp; _testInfo,
                        Totals const&amp; _totals,
                        std::string const&amp; _stdOut,
                        std::string const&amp; _stdErr,
                        bool _aborting );

        TestCaseStats( TestCaseStats const&amp; )              = default;
        TestCaseStats( TestCaseStats &amp;&amp; )                  = default;
        TestCaseStats&amp; operator = ( TestCaseStats const&amp; ) = default;
        TestCaseStats&amp; operator = ( TestCaseStats &amp;&amp; )     = default;
        virtual ~TestCaseStats();

        TestCaseInfo testInfo;
        Totals totals;
        std::string stdOut;
        std::string stdErr;
        bool aborting;
    };

    struct TestGroupStats {
        TestGroupStats( GroupInfo const&amp; _groupInfo,
                        Totals const&amp; _totals,
                        bool _aborting );
        TestGroupStats( GroupInfo const&amp; _groupInfo );

        TestGroupStats( TestGroupStats const&amp; )              = default;
        TestGroupStats( TestGroupStats &amp;&amp; )                  = default;
        TestGroupStats&amp; operator = ( TestGroupStats const&amp; ) = default;
        TestGroupStats&amp; operator = ( TestGroupStats &amp;&amp; )     = default;
        virtual ~TestGroupStats();

        GroupInfo groupInfo;
        Totals totals;
        bool aborting;
    };

    struct TestRunStats {
        TestRunStats(   TestRunInfo const&amp; _runInfo,
                        Totals const&amp; _totals,
                        bool _aborting );

        TestRunStats( TestRunStats const&amp; )              = default;
        TestRunStats( TestRunStats &amp;&amp; )                  = default;
        TestRunStats&amp; operator = ( TestRunStats const&amp; ) = default;
        TestRunStats&amp; operator = ( TestRunStats &amp;&amp; )     = default;
        virtual ~TestRunStats();

        TestRunInfo runInfo;
        Totals totals;
        bool aborting;
    };

    struct BenchmarkInfo {
        std::string name;
    };
    struct BenchmarkStats {
        BenchmarkInfo info;
        std::size_t iterations;
        uint64_t elapsedTimeInNanoseconds;
    };

    struct IStreamingReporter {
        virtual ~IStreamingReporter() = default;

        // Implementing class must also provide the following static methods:
        // static std::string getDescription();
        // static std::set&lt;Verbosity&gt; getSupportedVerbosities()

        virtual ReporterPreferences getPreferences() const = 0;

        virtual void noMatchingTestCases( std::string const&amp; spec ) = 0;

        virtual void testRunStarting( TestRunInfo const&amp; testRunInfo ) = 0;
        virtual void testGroupStarting( GroupInfo const&amp; groupInfo ) = 0;

        virtual void testCaseStarting( TestCaseInfo const&amp; testInfo ) = 0;
        virtual void sectionStarting( SectionInfo const&amp; sectionInfo ) = 0;

        // *** experimental ***
        virtual void benchmarkStarting( BenchmarkInfo const&amp; ) {}

        virtual void assertionStarting( AssertionInfo const&amp; assertionInfo ) = 0;

        // The return value indicates if the messages buffer should be cleared:
        virtual bool assertionEnded( AssertionStats const&amp; assertionStats ) = 0;

        // *** experimental ***
        virtual void benchmarkEnded( BenchmarkStats const&amp; ) {}

        virtual void sectionEnded( SectionStats const&amp; sectionStats ) = 0;
        virtual void testCaseEnded( TestCaseStats const&amp; testCaseStats ) = 0;
        virtual void testGroupEnded( TestGroupStats const&amp; testGroupStats ) = 0;
        virtual void testRunEnded( TestRunStats const&amp; testRunStats ) = 0;

        virtual void skipTest( TestCaseInfo const&amp; testInfo ) = 0;

        // Default empty implementation provided
        virtual void fatalErrorEncountered( StringRef name );

        virtual bool isMulti() const;
    };
    using IStreamingReporterPtr = std::unique_ptr&lt;IStreamingReporter&gt;;

    struct IReporterFactory {
        virtual ~IReporterFactory();
        virtual IStreamingReporterPtr create( ReporterConfig const&amp; config ) const = 0;
        virtual std::string getDescription() const = 0;
    };
    using IReporterFactoryPtr = std::shared_ptr&lt;IReporterFactory&gt;;

    struct IReporterRegistry {
        using FactoryMap = std::map&lt;std::string, IReporterFactoryPtr&gt;;
        using Listeners = std::vector&lt;IReporterFactoryPtr&gt;;

        virtual ~IReporterRegistry();
        virtual IStreamingReporterPtr create( std::string const&amp; name, IConfigPtr const&amp; config ) const = 0;
        virtual FactoryMap const&amp; getFactories() const = 0;
        virtual Listeners const&amp; getListeners() const = 0;
    };

    void addReporter( IStreamingReporterPtr&amp; existingReporter, IStreamingReporterPtr&amp;&amp; additionalReporter );

} // end namespace Catch

// end catch_interfaces_reporter.h
#include &lt;algorithm&gt;
#include &lt;cstring&gt;
#include &lt;cfloat&gt;
#include &lt;cstdio&gt;
#include &lt;assert.h&gt;
#include &lt;memory&gt;

namespace Catch {
    void prepareExpandedExpression(AssertionResult&amp; result);

    // Returns double formatted as %.3f (format expected on output)
    std::string getFormattedDuration( double duration );

    template&lt;typename DerivedT&gt;
    struct StreamingReporterBase : IStreamingReporter {

        StreamingReporterBase( ReporterConfig const&amp; _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            CATCH_ENFORCE( DerivedT::getSupportedVerbosities().count( m_config-&gt;verbosity() ), "Verbosity level not supported by this reporter" );
        }

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set&lt;Verbosity&gt; getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        ~StreamingReporterBase() override = default;

        void noMatchingTestCases(std::string const&amp;) override {}

        void testRunStarting(TestRunInfo const&amp; _testRunInfo) override {
            currentTestRunInfo = _testRunInfo;
        }
        void testGroupStarting(GroupInfo const&amp; _groupInfo) override {
            currentGroupInfo = _groupInfo;
        }

        void testCaseStarting(TestCaseInfo const&amp; _testInfo) override  {
            currentTestCaseInfo = _testInfo;
        }
        void sectionStarting(SectionInfo const&amp; _sectionInfo) override {
            m_sectionStack.push_back(_sectionInfo);
        }

        void sectionEnded(SectionStats const&amp; /* _sectionStats */) override {
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const&amp; /* _testCaseStats */) override {
            currentTestCaseInfo.reset();
        }
        void testGroupEnded(TestGroupStats const&amp; /* _testGroupStats */) override {
            currentGroupInfo.reset();
        }
        void testRunEnded(TestRunStats const&amp; /* _testRunStats */) override {
            currentTestCaseInfo.reset();
            currentGroupInfo.reset();
            currentTestRunInfo.reset();
        }

        void skipTest(TestCaseInfo const&amp;) override {
            // Don't do anything with this by default.
            // It can optionally be overridden in the derived class.
        }

        IConfigPtr m_config;
        std::ostream&amp; stream;

        LazyStat&lt;TestRunInfo&gt; currentTestRunInfo;
        LazyStat&lt;GroupInfo&gt; currentGroupInfo;
        LazyStat&lt;TestCaseInfo&gt; currentTestCaseInfo;

        std::vector&lt;SectionInfo&gt; m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template&lt;typename DerivedT&gt;
    struct CumulativeReporterBase : IStreamingReporter {
        template&lt;typename T, typename ChildNodeT&gt;
        struct Node {
            explicit Node( T const&amp; _value ) : value( _value ) {}
            virtual ~Node() {}

            using ChildNodes = std::vector&lt;std::shared_ptr&lt;ChildNodeT&gt;&gt;;
            T value;
            ChildNodes children;
        };
        struct SectionNode {
            explicit SectionNode(SectionStats const&amp; _stats) : stats(_stats) {}
            virtual ~SectionNode() = default;

            bool operator == (SectionNode const&amp; other) const {
                return stats.sectionInfo.lineInfo == other.stats.sectionInfo.lineInfo;
            }
            bool operator == (std::shared_ptr&lt;SectionNode&gt; const&amp; other) const {
                return operator==(*other);
            }

            SectionStats stats;
            using ChildSections = std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt;;
            using Assertions = std::vector&lt;AssertionStats&gt;;
            ChildSections childSections;
            Assertions assertions;
            std::string stdOut;
            std::string stdErr;
        };

        struct BySectionInfo {
            BySectionInfo( SectionInfo const&amp; other ) : m_other( other ) {}
            BySectionInfo( BySectionInfo const&amp; other ) : m_other( other.m_other ) {}
            bool operator() (std::shared_ptr&lt;SectionNode&gt; const&amp; node) const {
                return ((node-&gt;stats.sectionInfo.name == m_other.name) &amp;&amp;
                        (node-&gt;stats.sectionInfo.lineInfo == m_other.lineInfo));
            }
            void operator=(BySectionInfo const&amp;) = delete;

        private:
            SectionInfo const&amp; m_other;
        };

        using TestCaseNode = Node&lt;TestCaseStats, SectionNode&gt;;
        using TestGroupNode = Node&lt;TestGroupStats, TestCaseNode&gt;;
        using TestRunNode = Node&lt;TestRunStats, TestGroupNode&gt;;

        CumulativeReporterBase( ReporterConfig const&amp; _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            CATCH_ENFORCE( DerivedT::getSupportedVerbosities().count( m_config-&gt;verbosity() ), "Verbosity level not supported by this reporter" );
        }
        ~CumulativeReporterBase() override = default;

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set&lt;Verbosity&gt; getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        void testRunStarting( TestRunInfo const&amp; ) override {}
        void testGroupStarting( GroupInfo const&amp; ) override {}

        void testCaseStarting( TestCaseInfo const&amp; ) override {}

        void sectionStarting( SectionInfo const&amp; sectionInfo ) override {
            SectionStats incompleteStats( sectionInfo, Counts(), 0, false );
            std::shared_ptr&lt;SectionNode&gt; node;
            if( m_sectionStack.empty() ) {
                if( !m_rootSection )
                    m_rootSection = std::make_shared&lt;SectionNode&gt;( incompleteStats );
                node = m_rootSection;
            }
            else {
                SectionNode&amp; parentNode = *m_sectionStack.back();
                auto it =
                    std::find_if(   parentNode.childSections.begin(),
                                    parentNode.childSections.end(),
                                    BySectionInfo( sectionInfo ) );
                if( it == parentNode.childSections.end() ) {
                    node = std::make_shared&lt;SectionNode&gt;( incompleteStats );
                    parentNode.childSections.push_back( node );
                }
                else
                    node = *it;
            }
            m_sectionStack.push_back( node );
            m_deepestSection = std::move(node);
        }

        void assertionStarting(AssertionInfo const&amp;) override {}

        bool assertionEnded(AssertionStats const&amp; assertionStats) override {
            assert(!m_sectionStack.empty());
            // AssertionResult holds a pointer to a temporary DecomposedExpression,
            // which getExpandedExpression() calls to build the expression string.
            // Our section stack copy of the assertionResult will likely outlive the
            // temporary, so it must be expanded or discarded now to avoid calling
            // a destroyed object later.
            prepareExpandedExpression(const_cast&lt;AssertionResult&amp;&gt;( assertionStats.assertionResult ) );
            SectionNode&amp; sectionNode = *m_sectionStack.back();
            sectionNode.assertions.push_back(assertionStats);
            return true;
        }
        void sectionEnded(SectionStats const&amp; sectionStats) override {
            assert(!m_sectionStack.empty());
            SectionNode&amp; node = *m_sectionStack.back();
            node.stats = sectionStats;
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const&amp; testCaseStats) override {
            auto node = std::make_shared&lt;TestCaseNode&gt;(testCaseStats);
            assert(m_sectionStack.size() == 0);
            node-&gt;children.push_back(m_rootSection);
            m_testCases.push_back(node);
            m_rootSection.reset();

            assert(m_deepestSection);
            m_deepestSection-&gt;stdOut = testCaseStats.stdOut;
            m_deepestSection-&gt;stdErr = testCaseStats.stdErr;
        }
        void testGroupEnded(TestGroupStats const&amp; testGroupStats) override {
            auto node = std::make_shared&lt;TestGroupNode&gt;(testGroupStats);
            node-&gt;children.swap(m_testCases);
            m_testGroups.push_back(node);
        }
        void testRunEnded(TestRunStats const&amp; testRunStats) override {
            auto node = std::make_shared&lt;TestRunNode&gt;(testRunStats);
            node-&gt;children.swap(m_testGroups);
            m_testRuns.push_back(node);
            testRunEndedCumulative();
        }
        virtual void testRunEndedCumulative() = 0;

        void skipTest(TestCaseInfo const&amp;) override {}

        IConfigPtr m_config;
        std::ostream&amp; stream;
        std::vector&lt;AssertionStats&gt; m_assertions;
        std::vector&lt;std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt;&gt; m_sections;
        std::vector&lt;std::shared_ptr&lt;TestCaseNode&gt;&gt; m_testCases;
        std::vector&lt;std::shared_ptr&lt;TestGroupNode&gt;&gt; m_testGroups;

        std::vector&lt;std::shared_ptr&lt;TestRunNode&gt;&gt; m_testRuns;

        std::shared_ptr&lt;SectionNode&gt; m_rootSection;
        std::shared_ptr&lt;SectionNode&gt; m_deepestSection;
        std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt; m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template&lt;char C&gt;
    char const* getLineOfChars() {
        static char line[CATCH_CONFIG_CONSOLE_WIDTH] = {0};
        if( !*line ) {
            std::memset( line, C, CATCH_CONFIG_CONSOLE_WIDTH-1 );
            line[CATCH_CONFIG_CONSOLE_WIDTH-1] = 0;
        }
        return line;
    }

    struct TestEventListenerBase : StreamingReporterBase&lt;TestEventListenerBase&gt; {
        TestEventListenerBase( ReporterConfig const&amp; _config );

        void assertionStarting(AssertionInfo const&amp;) override;
        bool assertionEnded(AssertionStats const&amp;) override;
    };

} // end namespace Catch

// end catch_reporter_bases.hpp
// start catch_console_colour.h

namespace Catch {

    struct Colour {
        enum Code {
            None = 0,

            White,
            Red,
            Green,
            Blue,
            Cyan,
            Yellow,
            Grey,

            Bright = 0x10,

            BrightRed = Bright | Red,
            BrightGreen = Bright | Green,
            LightGrey = Bright | Grey,
            BrightWhite = Bright | White,

            // By intention
            FileName = LightGrey,
            Warning = Yellow,
            ResultError = BrightRed,
            ResultSuccess = BrightGreen,
            ResultExpectedFailure = Warning,

            Error = BrightRed,
            Success = Green,

            OriginalExpression = Cyan,
            ReconstructedExpression = Yellow,

            SecondaryText = LightGrey,
            Headers = White
        };

        // Use constructed object for RAII guard
        Colour( Code _colourCode );
        Colour( Colour&amp;&amp; other ) noexcept;
        Colour&amp; operator=( Colour&amp;&amp; other ) noexcept;
        ~Colour();

        // Use static method for one-shot changes
        static void use( Code _colourCode );

    private:
        bool m_moved = false;
    };

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Colour const&amp; );

} // end namespace Catch

// end catch_console_colour.h
// start catch_reporter_registrars.hpp


namespace Catch {

    template&lt;typename T&gt;
    class ReporterRegistrar {

        class ReporterFactory : public IReporterFactory {

            virtual IStreamingReporterPtr create( ReporterConfig const&amp; config ) const override {
                return std::unique_ptr&lt;T&gt;( new T( config ) );
            }

            virtual std::string getDescription() const override {
                return T::getDescription();
            }
        };

    public:

        ReporterRegistrar( std::string const&amp; name ) {
            getMutableRegistryHub().registerReporter( name, std::make_shared&lt;ReporterFactory&gt;() );
        }
    };

    template&lt;typename T&gt;
    class ListenerRegistrar {

        class ListenerFactory : public IReporterFactory {

            virtual IStreamingReporterPtr create( ReporterConfig const&amp; config ) const override {
                return std::unique_ptr&lt;T&gt;( new T( config ) );
            }
            virtual std::string getDescription() const override {
                return std::string();
            }
        };

    public:

        ListenerRegistrar() {
            getMutableRegistryHub().registerListener( std::make_shared&lt;ListenerFactory&gt;() );
        }
    };
}

#if !defined(CATCH_CONFIG_DISABLE)

#define CATCH_REGISTER_REPORTER( name, reporterType ) \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS          \
    namespace{ Catch::ReporterRegistrar&lt;reporterType&gt; catch_internal_RegistrarFor##reporterType( name ); } \
    CATCH_INTERNAL_UNSUPPRESS_GLOBALS_WARNINGS

#define CATCH_REGISTER_LISTENER( listenerType ) \
     CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS   \
     namespace{ Catch::ListenerRegistrar&lt;listenerType&gt; catch_internal_RegistrarFor##listenerType; } \
     CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
#else // CATCH_CONFIG_DISABLE

#define CATCH_REGISTER_REPORTER(name, reporterType)
#define CATCH_REGISTER_LISTENER(listenerType)

#endif // CATCH_CONFIG_DISABLE

// end catch_reporter_registrars.hpp
// end catch_external_interfaces.h
#endif

#ifdef CATCH_IMPL
// start catch_impl.hpp

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// Keep these here for external reporters
// start catch_test_case_tracker.h

#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {
namespace TestCaseTracking {

    struct NameAndLocation {
        std::string name;
        SourceLineInfo location;

        NameAndLocation( std::string const&amp; _name, SourceLineInfo const&amp; _location );
    };

    struct ITracker;

    using ITrackerPtr = std::shared_ptr&lt;ITracker&gt;;

    struct ITracker {
        virtual ~ITracker();

        // static queries
        virtual NameAndLocation const&amp; nameAndLocation() const = 0;

        // dynamic queries
        virtual bool isComplete() const = 0; // Successfully completed or failed
        virtual bool isSuccessfullyCompleted() const = 0;
        virtual bool isOpen() const = 0; // Started but not complete
        virtual bool hasChildren() const = 0;

        virtual ITracker&amp; parent() = 0;

        // actions
        virtual void close() = 0; // Successfully complete
        virtual void fail() = 0;
        virtual void markAsNeedingAnotherRun() = 0;

        virtual void addChild( ITrackerPtr const&amp; child ) = 0;
        virtual ITrackerPtr findChild( NameAndLocation const&amp; nameAndLocation ) = 0;
        virtual void openChild() = 0;

        // Debug/ checking
        virtual bool isSectionTracker() const = 0;
        virtual bool isIndexTracker() const = 0;
    };

    class TrackerContext {

        enum RunState {
            NotStarted,
            Executing,
            CompletedCycle
        };

        ITrackerPtr m_rootTracker;
        ITracker* m_currentTracker = nullptr;
        RunState m_runState = NotStarted;

    public:

        static TrackerContext&amp; instance();

        ITracker&amp; startRun();
        void endRun();

        void startCycle();
        void completeCycle();

        bool completedCycle() const;
        ITracker&amp; currentTracker();
        void setCurrentTracker( ITracker* tracker );
    };

    class TrackerBase : public ITracker {
    protected:
        enum CycleState {
            NotStarted,
            Executing,
            ExecutingChildren,
            NeedsAnotherRun,
            CompletedSuccessfully,
            Failed
        };

        class TrackerHasName {
            NameAndLocation m_nameAndLocation;
        public:
            TrackerHasName( NameAndLocation const&amp; nameAndLocation );
            bool operator ()( ITrackerPtr const&amp; tracker ) const;
        };

        using Children = std::vector&lt;ITrackerPtr&gt;;
        NameAndLocation m_nameAndLocation;
        TrackerContext&amp; m_ctx;
        ITracker* m_parent;
        Children m_children;
        CycleState m_runState = NotStarted;

    public:
        TrackerBase( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent );

        NameAndLocation const&amp; nameAndLocation() const override;
        bool isComplete() const override;
        bool isSuccessfullyCompleted() const override;
        bool isOpen() const override;
        bool hasChildren() const override;

        void addChild( ITrackerPtr const&amp; child ) override;

        ITrackerPtr findChild( NameAndLocation const&amp; nameAndLocation ) override;
        ITracker&amp; parent() override;

        void openChild() override;

        bool isSectionTracker() const override;
        bool isIndexTracker() const override;

        void open();

        void close() override;
        void fail() override;
        void markAsNeedingAnotherRun() override;

    private:
        void moveToParent();
        void moveToThis();
    };

    class SectionTracker : public TrackerBase {
        std::vector&lt;std::string&gt; m_filters;
    public:
        SectionTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent );

        bool isSectionTracker() const override;

        static SectionTracker&amp; acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation );

        void tryOpen();

        void addInitialFilters( std::vector&lt;std::string&gt; const&amp; filters );
        void addNextFilters( std::vector&lt;std::string&gt; const&amp; filters );
    };

    class IndexTracker : public TrackerBase {
        int m_size;
        int m_index = -1;
    public:
        IndexTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent, int size );

        bool isIndexTracker() const override;
        void close() override;

        static IndexTracker&amp; acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation, int size );

        int index() const;

        void moveNext();
    };

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;
using TestCaseTracking::IndexTracker;

} // namespace Catch

// end catch_test_case_tracker.h

// start catch_leak_detector.h

namespace Catch {

    struct LeakDetector {
        LeakDetector();
    };

}
// end catch_leak_detector.h
// Cpp files will be included in the single-header file here
// start catch_approx.cpp

#include &lt;cmath&gt;
#include &lt;limits&gt;

namespace {

// Performs equivalent check of std::fabs(lhs - rhs) &lt;= margin
// But without the subtraction to allow for INFINITY in comparison
bool marginComparison(double lhs, double rhs, double margin) {
    return (lhs + margin &gt;= rhs) &amp;&amp; (rhs + margin &gt;= lhs);
}

}

namespace Catch {
namespace Detail {

    Approx::Approx ( double value )
    :   m_epsilon( std::numeric_limits&lt;float&gt;::epsilon()*100 ),
        m_margin( 0.0 ),
        m_scale( 0.0 ),
        m_value( value )
    {}

    Approx Approx::custom() {
        return Approx( 0 );
    }

    std::string Approx::toString() const {
        std::ostringstream oss;
        oss &lt;&lt; "Approx( " &lt;&lt; ::Catch::Detail::stringify( m_value ) &lt;&lt; " )";
        return oss.str();
    }

    bool Approx::equalityComparisonImpl(const double other) const {
        // First try with fixed margin, then compute margin based on epsilon, scale and Approx's value
        // Thanks to Richard Harris for his help refining the scaled margin value
        return marginComparison(m_value, other, m_margin) || marginComparison(m_value, other, m_epsilon * (m_scale + std::fabs(m_value)));
    }

} // end namespace Detail

std::string StringMaker&lt;Catch::Detail::Approx&gt;::convert(Catch::Detail::Approx const&amp; value) {
    return value.toString();
}

} // end namespace Catch
// end catch_approx.cpp
// start catch_assertionhandler.cpp

// start catch_context.h

#include &lt;memory&gt;

namespace Catch {

    struct IResultCapture;
    struct IRunner;
    struct IConfig;

    using IConfigPtr = std::shared_ptr&lt;IConfig const&gt;;

    struct IContext
    {
        virtual ~IContext();

        virtual IResultCapture* getResultCapture() = 0;
        virtual IRunner* getRunner() = 0;
        virtual IConfigPtr getConfig() const = 0;
    };

    struct IMutableContext : IContext
    {
        virtual ~IMutableContext();
        virtual void setResultCapture( IResultCapture* resultCapture ) = 0;
        virtual void setRunner( IRunner* runner ) = 0;
        virtual void setConfig( IConfigPtr const&amp; config ) = 0;
    };

    IContext&amp; getCurrentContext();
    IMutableContext&amp; getCurrentMutableContext();
    void cleanUpContext();
}

// end catch_context.h
#include &lt;cassert&gt;

namespace Catch {

    auto operator &lt;&lt;( std::ostream&amp; os, ITransientExpression const&amp; expr ) -&gt; std::ostream&amp; {
        expr.streamReconstructedExpression( os );
        return os;
    }

    LazyExpression::LazyExpression( bool isNegated )
    :   m_isNegated( isNegated )
    {}

    LazyExpression::LazyExpression( LazyExpression const&amp; other ) : m_isNegated( other.m_isNegated ) {}

    LazyExpression::operator bool() const {
        return m_transientExpression != nullptr;
    }

    auto operator &lt;&lt; ( std::ostream&amp; os, LazyExpression const&amp; lazyExpr ) -&gt; std::ostream&amp; {
        if( lazyExpr.m_isNegated )
            os &lt;&lt; "!";

        if( lazyExpr ) {
            if( lazyExpr.m_isNegated &amp;&amp; lazyExpr.m_transientExpression-&gt;isBinaryExpression() )
                os &lt;&lt; "(" &lt;&lt; *lazyExpr.m_transientExpression &lt;&lt; ")";
            else
                os &lt;&lt; *lazyExpr.m_transientExpression;
        }
        else {
            os &lt;&lt; "{** error - unchecked empty expression requested **}";
        }
        return os;
    }

    AssertionHandler::AssertionHandler
        (   StringRef macroName,
            SourceLineInfo const&amp; lineInfo,
            StringRef capturedExpression,
            ResultDisposition::Flags resultDisposition )
    :   m_assertionInfo{ macroName, lineInfo, capturedExpression, resultDisposition }
    {
        getCurrentContext().getResultCapture()-&gt;assertionStarting( m_assertionInfo );
    }
    AssertionHandler::~AssertionHandler() {
        if ( m_inExceptionGuard ) {
            handle( ResultWas::ThrewException, "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE" );
            getCurrentContext().getResultCapture()-&gt;exceptionEarlyReported();
        }
    }

    void AssertionHandler::handle( ITransientExpression const&amp; expr ) {

        bool negated = isFalseTest( m_assertionInfo.resultDisposition );
        bool result = expr.getResult() != negated;

        handle( result ? ResultWas::Ok : ResultWas::ExpressionFailed, &amp;expr, negated );
    }
    void AssertionHandler::handle( ResultWas::OfType resultType ) {
        handle( resultType, nullptr, false );
    }
    void AssertionHandler::handle( ResultWas::OfType resultType, StringRef const&amp; message ) {
        AssertionResultData data( resultType, LazyExpression( false ) );
        data.message = message;
        handle( data, nullptr );
    }
    void AssertionHandler::handle( ResultWas::OfType resultType, ITransientExpression const* expr, bool negated ) {
        AssertionResultData data( resultType, LazyExpression( negated ) );
        handle( data, expr );
    }
    void AssertionHandler::handle( AssertionResultData const&amp; resultData, ITransientExpression const* expr ) {

        getResultCapture().assertionRun();

        AssertionResult assertionResult{ m_assertionInfo, resultData };
        assertionResult.m_resultData.lazyExpression.m_transientExpression = expr;

        getResultCapture().assertionEnded( assertionResult );

        if( !assertionResult.isOk() ) {
            m_shouldDebugBreak = getCurrentContext().getConfig()-&gt;shouldDebugBreak();
            m_shouldThrow =
                    getCurrentContext().getRunner()-&gt;aborting() ||
                    (m_assertionInfo.resultDisposition &amp; ResultDisposition::Normal);
        }
    }

    auto AssertionHandler::allowThrows() const -&gt; bool {
        return getCurrentContext().getConfig()-&gt;allowThrows();
    }

    auto AssertionHandler::shouldDebugBreak() const -&gt; bool {
        return m_shouldDebugBreak;
    }
    void AssertionHandler::reactWithDebugBreak() const {
        if (m_shouldDebugBreak) {
            ///////////////////////////////////////////////////////////////////
            // To inspect the state during test, you need to go one level up the callstack
            // To go back to the test and change execution, jump over the reactWithoutDebugBreak() call
            ///////////////////////////////////////////////////////////////////
            CATCH_BREAK_INTO_DEBUGGER();
        }
        reactWithoutDebugBreak();
    }
    void AssertionHandler::reactWithoutDebugBreak() const {
        if( m_shouldThrow )
            throw Catch::TestFailureException();
    }

    void AssertionHandler::useActiveException() {
        handle( ResultWas::ThrewException, Catch::translateActiveException() );
    }

    void AssertionHandler::setExceptionGuard() {
        assert( m_inExceptionGuard == false );
        m_inExceptionGuard = true;
    }
    void AssertionHandler::unsetExceptionGuard() {
        assert( m_inExceptionGuard == true );
        m_inExceptionGuard = false;
    }

    // This is the overload that takes a string and infers the Equals matcher from it
    // The more general overload, that takes any string matcher, is in catch_capture_matchers.cpp
    void handleExceptionMatchExpr( AssertionHandler&amp; handler, std::string const&amp; str, StringRef matcherString  ) {
        handleExceptionMatchExpr( handler, Matchers::Equals( str ), matcherString );
    }

} // namespace Catch
// end catch_assertionhandler.cpp
// start catch_assertionresult.cpp

namespace Catch {
    AssertionResultData::AssertionResultData(ResultWas::OfType _resultType, LazyExpression const &amp; _lazyExpression):
        lazyExpression(_lazyExpression),
        resultType(_resultType) {}

    std::string AssertionResultData::reconstructExpression() const {

        if( reconstructedExpression.empty() ) {
            if( lazyExpression ) {
                // !TBD Use stringstream for now, but rework above to pass stream in
                std::ostringstream oss;
                oss &lt;&lt; lazyExpression;
                reconstructedExpression = oss.str();
            }
        }
        return reconstructedExpression;
    }

    AssertionResult::AssertionResult( AssertionInfo const&amp; info, AssertionResultData const&amp; data )
    :   m_info( info ),
        m_resultData( data )
    {}

    // Result was a success
    bool AssertionResult::succeeded() const {
        return Catch::isOk( m_resultData.resultType );
    }

    // Result was a success, or failure is suppressed
    bool AssertionResult::isOk() const {
        return Catch::isOk( m_resultData.resultType ) || shouldSuppressFailure( m_info.resultDisposition );
    }

    ResultWas::OfType AssertionResult::getResultType() const {
        return m_resultData.resultType;
    }

    bool AssertionResult::hasExpression() const {
        return m_info.capturedExpression[0] != 0;
    }

    bool AssertionResult::hasMessage() const {
        return !m_resultData.message.empty();
    }

    std::string AssertionResult::getExpression() const {
        if( isFalseTest( m_info.resultDisposition ) )
            return "!(" + std::string(m_info.capturedExpression) + ")";
        else
            return m_info.capturedExpression;
    }

    std::string AssertionResult::getExpressionInMacro() const {
        std::string expr;
        if( m_info.macroName[0] == 0 )
            expr = m_info.capturedExpression;
        else {
            expr.reserve( m_info.macroName.size() + m_info.capturedExpression.size() + 4 );
            expr += m_info.macroName;
            expr += "( ";
            expr += m_info.capturedExpression;
            expr += " )";
        }
        return expr;
    }

    bool AssertionResult::hasExpandedExpression() const {
        return hasExpression() &amp;&amp; getExpandedExpression() != getExpression();
    }

    std::string AssertionResult::getExpandedExpression() const {
        std::string expr = m_resultData.reconstructExpression();
        return expr.empty()
                ? getExpression()
                : expr;
    }

    std::string AssertionResult::getMessage() const {
        return m_resultData.message;
    }
    SourceLineInfo AssertionResult::getSourceInfo() const {
        return m_info.lineInfo;
    }

    std::string AssertionResult::getTestMacroName() const {
        return m_info.macroName;
    }

} // end namespace Catch
// end catch_assertionresult.cpp
// start catch_benchmark.cpp

namespace Catch {

    auto BenchmarkLooper::getResolution() -&gt; uint64_t {
        return getEstimatedClockResolution() * getCurrentContext().getConfig()-&gt;benchmarkResolutionMultiple();
    }

    void BenchmarkLooper::reportStart() {
        getResultCapture().benchmarkStarting( { m_name } );
    }
    auto BenchmarkLooper::needsMoreIterations() -&gt; bool {
        auto elapsed = m_timer.getElapsedNanoseconds();

        // Exponentially increasing iterations until we're confident in our timer resolution
        if( elapsed &lt; m_resolution ) {
            m_iterationsToRun *= 10;
            return true;
        }

        getResultCapture().benchmarkEnded( { { m_name }, m_count, elapsed } );
        return false;
    }

} // end namespace Catch
// end catch_benchmark.cpp
// start catch_capture_matchers.cpp

namespace Catch {

    using StringMatcher = Matchers::Impl::MatcherBase&lt;std::string&gt;;

    // This is the general overload that takes a any string matcher
    // There is another overload, in catch_assertinhandler.h/.cpp, that only takes a string and infers
    // the Equals matcher (so the header does not mention matchers)
    void handleExceptionMatchExpr( AssertionHandler&amp; handler, StringMatcher const&amp; matcher, StringRef matcherString  ) {
        std::string exceptionMessage = Catch::translateActiveException();
        MatchExpr&lt;std::string, StringMatcher const&amp;&gt; expr( exceptionMessage, matcher, matcherString );
        handler.handle( expr );
    }

} // namespace Catch
// end catch_capture_matchers.cpp
// start catch_commandline.cpp

// start catch_commandline.h

// start catch_clara.h

// Use Catch's value for console width (store Clara's off to the side, if present)
#ifdef CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#undef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#endif
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_CONFIG_CONSOLE_WIDTH-1

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wshadow"
#endif

// start clara.hpp
// v1.0-develop.2
// See https://github.com/philsquared/Clara


#ifndef CATCH_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_CONFIG_CONSOLE_WIDTH 80
#endif

#ifndef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_CLARA_CONFIG_CONSOLE_WIDTH
#endif

// ----------- #included from clara_textflow.hpp -----------

// TextFlowCpp
//
// A single-header library for wrapping and laying out basic text, by Phil Nash
//
// This work is licensed under the BSD 2-Clause license.
// See the accompanying LICENSE file, or the one at https://opensource.org/licenses/BSD-2-Clause
//
// This project is hosted at https://github.com/philsquared/textflowcpp


#include &lt;cassert&gt;
#include &lt;ostream&gt;
#include &lt;sstream&gt;
#include &lt;vector&gt;

#ifndef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch { namespace clara { namespace TextFlow {

    inline auto isWhitespace( char c ) -&gt; bool {
        static std::string chars = " \t\n\r";
        return chars.find( c ) != std::string::npos;
    }
    inline auto isBreakableBefore( char c ) -&gt; bool {
        static std::string chars = "[({&lt;|";
        return chars.find( c ) != std::string::npos;
    }
    inline auto isBreakableAfter( char c ) -&gt; bool {
        static std::string chars = "])}&gt;.,:;*+-=&amp;/\\";
        return chars.find( c ) != std::string::npos;
    }

    class Columns;

    class Column {
        std::vector&lt;std::string&gt; m_strings;
        size_t m_width = CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH;
        size_t m_indent = 0;
        size_t m_initialIndent = std::string::npos;

    public:
        class iterator {
            friend Column;

            Column const&amp; m_column;
            size_t m_stringIndex = 0;
            size_t m_pos = 0;

            size_t m_len = 0;
            size_t m_end = 0;
            bool m_suffix = false;

            iterator( Column const&amp; column, size_t stringIndex )
            :   m_column( column ),
                m_stringIndex( stringIndex )
            {}

            auto line() const -&gt; std::string const&amp; { return m_column.m_strings[m_stringIndex]; }

            auto isBoundary( size_t at ) const -&gt; bool {
                assert( at &gt; 0 );
                assert( at &lt;= line().size() );

                return at == line().size() ||
                       ( isWhitespace( line()[at] ) &amp;&amp; !isWhitespace( line()[at-1] ) ) ||
                       isBreakableBefore( line()[at] ) ||
                       isBreakableAfter( line()[at-1] );
            }

            void calcLength() {
                assert( m_stringIndex &lt; m_column.m_strings.size() );

                m_suffix = false;
                auto width = m_column.m_width-indent();
                m_end = m_pos;
                while( m_end &lt; line().size() &amp;&amp; line()[m_end] != '\n' )
                    ++m_end;

                if( m_end &lt; m_pos + width ) {
                    m_len = m_end - m_pos;
                }
                else {
                    size_t len = width;
                    while (len &gt; 0 &amp;&amp; !isBoundary(m_pos + len))
                        --len;
                    while (len &gt; 0 &amp;&amp; isWhitespace( line()[m_pos + len - 1] ))
                        --len;

                    if (len &gt; 0) {
                        m_len = len;
                    } else {
                        m_suffix = true;
                        m_len = width - 1;
                    }
                }
            }

            auto indent() const -&gt; size_t {
                auto initial = m_pos == 0 &amp;&amp; m_stringIndex == 0 ? m_column.m_initialIndent : std::string::npos;
                return initial == std::string::npos ? m_column.m_indent : initial;
            }

            auto addIndentAndSuffix(std::string const &amp;plain) const -&gt; std::string {
                return std::string( indent(), ' ' ) + (m_suffix ? plain + "-" : plain);
            }

        public:
            explicit iterator( Column const&amp; column ) : m_column( column ) {
                assert( m_column.m_width &gt; m_column.m_indent );
                assert( m_column.m_initialIndent == std::string::npos || m_column.m_width &gt; m_column.m_initialIndent );
                calcLength();
                if( m_len == 0 )
                    m_stringIndex++; // Empty string
            }

            auto operator *() const -&gt; std::string {
                assert( m_stringIndex &lt; m_column.m_strings.size() );
                assert( m_pos &lt;= m_end );
                if( m_pos + m_column.m_width &lt; m_end )
                    return addIndentAndSuffix(line().substr(m_pos, m_len));
                else
                    return addIndentAndSuffix(line().substr(m_pos, m_end - m_pos));
            }

            auto operator ++() -&gt; iterator&amp; {
                m_pos += m_len;
                if( m_pos &lt; line().size() &amp;&amp; line()[m_pos] == '\n' )
                    m_pos += 1;
                else
                    while( m_pos &lt; line().size() &amp;&amp; isWhitespace( line()[m_pos] ) )
                        ++m_pos;

                if( m_pos == line().size() ) {
                    m_pos = 0;
                    ++m_stringIndex;
                }
                if( m_stringIndex &lt; m_column.m_strings.size() )
                    calcLength();
                return *this;
            }
            auto operator ++(int) -&gt; iterator {
                iterator prev( *this );
                operator++();
                return prev;
            }

            auto operator ==( iterator const&amp; other ) const -&gt; bool {
                return
                    m_pos == other.m_pos &amp;&amp;
                    m_stringIndex == other.m_stringIndex &amp;&amp;
                    &amp;m_column == &amp;other.m_column;
            }
            auto operator !=( iterator const&amp; other ) const -&gt; bool {
                return !operator==( other );
            }
        };
        using const_iterator = iterator;

        explicit Column( std::string const&amp; text ) { m_strings.push_back( text ); }

        auto width( size_t newWidth ) -&gt; Column&amp; {
            assert( newWidth &gt; 0 );
            m_width = newWidth;
            return *this;
        }
        auto indent( size_t newIndent ) -&gt; Column&amp; {
            m_indent = newIndent;
            return *this;
        }
        auto initialIndent( size_t newIndent ) -&gt; Column&amp; {
            m_initialIndent = newIndent;
            return *this;
        }

        auto width() const -&gt; size_t { return m_width; }
        auto begin() const -&gt; iterator { return iterator( *this ); }
        auto end() const -&gt; iterator { return { *this, m_strings.size() }; }

        inline friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Column const&amp; col ) {
            bool first = true;
            for( auto line : col ) {
                if( first )
                    first = false;
                else
                    os &lt;&lt; "\n";
                os &lt;&lt;  line;
            }
            return os;
        }

        auto operator + ( Column const&amp; other ) -&gt; Columns;

        auto toString() const -&gt; std::string {
            std::ostringstream oss;
            oss &lt;&lt; *this;
            return oss.str();
        }
    };

    class Spacer : public Column {

    public:
        explicit Spacer( size_t spaceWidth ) : Column( "" ) {
            width( spaceWidth );
        }
    };

    class Columns {
        std::vector&lt;Column&gt; m_columns;

    public:

        class iterator {
            friend Columns;
            struct EndTag {};

            std::vector&lt;Column&gt; const&amp; m_columns;
            std::vector&lt;Column::iterator&gt; m_iterators;
            size_t m_activeIterators;

            iterator( Columns const&amp; columns, EndTag )
            :   m_columns( columns.m_columns ),
                m_activeIterators( 0 )
            {
                m_iterators.reserve( m_columns.size() );

                for( auto const&amp; col : m_columns )
                    m_iterators.push_back( col.end() );
            }

        public:
            explicit iterator( Columns const&amp; columns )
            :   m_columns( columns.m_columns ),
                m_activeIterators( m_columns.size() )
            {
                m_iterators.reserve( m_columns.size() );

                for( auto const&amp; col : m_columns )
                    m_iterators.push_back( col.begin() );
            }

            auto operator ==( iterator const&amp; other ) const -&gt; bool {
                return m_iterators == other.m_iterators;
            }
            auto operator !=( iterator const&amp; other ) const -&gt; bool {
                return m_iterators != other.m_iterators;
            }
            auto operator *() const -&gt; std::string {
                std::string row, padding;

                for( size_t i = 0; i &lt; m_columns.size(); ++i ) {
                    auto width = m_columns[i].width();
                    if( m_iterators[i] != m_columns[i].end() ) {
                        std::string col = *m_iterators[i];
                        row += padding + col;
                        if( col.size() &lt; width )
                            padding = std::string( width - col.size(), ' ' );
                        else
                            padding = "";
                    }
                    else {
                        padding += std::string( width, ' ' );
                    }
                }
                return row;
            }
            auto operator ++() -&gt; iterator&amp; {
                for( size_t i = 0; i &lt; m_columns.size(); ++i ) {
                    if (m_iterators[i] != m_columns[i].end())
                        ++m_iterators[i];
                }
                return *this;
            }
            auto operator ++(int) -&gt; iterator {
                iterator prev( *this );
                operator++();
                return prev;
            }
        };
        using const_iterator = iterator;

        auto begin() const -&gt; iterator { return iterator( *this ); }
        auto end() const -&gt; iterator { return { *this, iterator::EndTag() }; }

        auto operator += ( Column const&amp; col ) -&gt; Columns&amp; {
            m_columns.push_back( col );
            return *this;
        }
        auto operator + ( Column const&amp; col ) -&gt; Columns {
            Columns combined = *this;
            combined += col;
            return combined;
        }

        inline friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Columns const&amp; cols ) {

            bool first = true;
            for( auto line : cols ) {
                if( first )
                    first = false;
                else
                    os &lt;&lt; "\n";
                os &lt;&lt; line;
            }
            return os;
        }

        auto toString() const -&gt; std::string {
            std::ostringstream oss;
            oss &lt;&lt; *this;
            return oss.str();
        }
    };

    inline auto Column::operator + ( Column const&amp; other ) -&gt; Columns {
        Columns cols;
        cols += *this;
        cols += other;
        return cols;
    }
}}} // namespace Catch::clara::TextFlow

// ----------- end of #include from clara_textflow.hpp -----------
// ........... back in clara.hpp

#include &lt;memory&gt;
#include &lt;set&gt;
#include &lt;algorithm&gt;

#if !defined(CATCH_PLATFORM_WINDOWS) &amp;&amp; ( defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) )
#define CATCH_PLATFORM_WINDOWS
#endif

namespace Catch { namespace clara {
namespace detail {

    // Traits for extracting arg and return type of lambdas (for single argument lambdas)
    template&lt;typename L&gt;
    struct UnaryLambdaTraits : UnaryLambdaTraits&lt;decltype( &amp;L::operator() )&gt; {};

    template&lt;typename ClassT, typename ReturnT, typename... Args&gt;
    struct UnaryLambdaTraits&lt;ReturnT( ClassT::* )( Args... ) const&gt; {
        static const bool isValid = false;
    };

    template&lt;typename ClassT, typename ReturnT, typename ArgT&gt;
    struct UnaryLambdaTraits&lt;ReturnT( ClassT::* )( ArgT ) const&gt; {
        static const bool isValid = true;
        using ArgType = typename std::remove_const&lt;typename std::remove_reference&lt;ArgT&gt;::type&gt;::type;;
        using ReturnType = ReturnT;
    };

    class TokenStream;

    // Transport for raw args (copied from main args, or supplied via init list for testing)
    class Args {
        friend TokenStream;
        std::string m_exeName;
        std::vector&lt;std::string&gt; m_args;

    public:
        Args( int argc, char *argv[] ) {
            m_exeName = argv[0];
            for( int i = 1; i &lt; argc; ++i )
                m_args.push_back( argv[i] );
        }

        Args( std::initializer_list&lt;std::string&gt; args )
        :   m_exeName( *args.begin() ),
            m_args( args.begin()+1, args.end() )
        {}

        auto exeName() const -&gt; std::string {
            return m_exeName;
        }
    };

    // Wraps a token coming from a token stream. These may not directly correspond to strings as a single string
    // may encode an option + its argument if the : or = form is used
    enum class TokenType {
        Option, Argument
    };
    struct Token {
        TokenType type;
        std::string token;
    };

    inline auto isOptPrefix( char c ) -&gt; bool {
        return c == '-'
#ifdef CATCH_PLATFORM_WINDOWS
            || c == '/'
#endif
        ;
    }

    // Abstracts iterators into args as a stream of tokens, with option arguments uniformly handled
    class TokenStream {
        using Iterator = std::vector&lt;std::string&gt;::const_iterator;
        Iterator it;
        Iterator itEnd;
        std::vector&lt;Token&gt; m_tokenBuffer;

        void loadBuffer() {
            m_tokenBuffer.resize( 0 );

            // Skip any empty strings
            while( it != itEnd &amp;&amp; it-&gt;empty() )
                ++it;

            if( it != itEnd ) {
                auto const &amp;next = *it;
                if( isOptPrefix( next[0] ) ) {
                    auto delimiterPos = next.find_first_of( " :=" );
                    if( delimiterPos != std::string::npos ) {
                        m_tokenBuffer.push_back( { TokenType::Option, next.substr( 0, delimiterPos ) } );
                        m_tokenBuffer.push_back( { TokenType::Argument, next.substr( delimiterPos + 1 ) } );
                    } else {
                        if( next[1] != '-' &amp;&amp; next.size() &gt; 2 ) {
                            std::string opt = "- ";
                            for( size_t i = 1; i &lt; next.size(); ++i ) {
                                opt[1] = next[i];
                                m_tokenBuffer.push_back( { TokenType::Option, opt } );
                            }
                        } else {
                            m_tokenBuffer.push_back( { TokenType::Option, next } );
                        }
                    }
                } else {
                    m_tokenBuffer.push_back( { TokenType::Argument, next } );
                }
            }
        }

    public:
        explicit TokenStream( Args const &amp;args ) : TokenStream( args.m_args.begin(), args.m_args.end() ) {}

        TokenStream( Iterator it, Iterator itEnd ) : it( it ), itEnd( itEnd ) {
            loadBuffer();
        }

        explicit operator bool() const {
            return !m_tokenBuffer.empty() || it != itEnd;
        }

        auto count() const -&gt; size_t { return m_tokenBuffer.size() + (itEnd - it); }

        auto operator*() const -&gt; Token {
            assert( !m_tokenBuffer.empty() );
            return m_tokenBuffer.front();
        }

        auto operator-&gt;() const -&gt; Token const * {
            assert( !m_tokenBuffer.empty() );
            return &amp;m_tokenBuffer.front();
        }

        auto operator++() -&gt; TokenStream &amp; {
            if( m_tokenBuffer.size() &gt;= 2 ) {
                m_tokenBuffer.erase( m_tokenBuffer.begin() );
            } else {
                if( it != itEnd )
                    ++it;
                loadBuffer();
            }
            return *this;
        }
    };

    class ResultBase {
    public:
        enum Type {
            Ok, LogicError, RuntimeError
        };

    protected:
        ResultBase( Type type ) : m_type( type ) {}
        virtual ~ResultBase() = default;

        virtual void enforceOk() const = 0;

        Type m_type;
    };

    template&lt;typename T&gt;
    class ResultValueBase : public ResultBase {
    public:
        auto value() const -&gt; T const &amp; {
            enforceOk();
            return m_value;
        }

    protected:
        ResultValueBase( Type type ) : ResultBase( type ) {}

        ResultValueBase( ResultValueBase const &amp;other ) : ResultBase( other ) {
            if( m_type == ResultBase::Ok )
                new( &amp;m_value ) T( other.m_value );
        }

        ResultValueBase( Type, T const &amp;value ) : ResultBase( Ok ) {
            new( &amp;m_value ) T( value );
        }

        auto operator=( ResultValueBase const &amp;other ) -&gt; ResultValueBase &amp; {
            if( m_type == ResultBase::Ok )
                m_value.~T();
            ResultBase::operator=(other);
            if( m_type == ResultBase::Ok )
                new( &amp;m_value ) T( other.m_value );
            return *this;
        }

        ~ResultValueBase() {
            if( m_type == Ok )
                m_value.~T();
        }

        union {
            T m_value;
        };
    };

    template&lt;&gt;
    class ResultValueBase&lt;void&gt; : public ResultBase {
    protected:
        using ResultBase::ResultBase;
    };

    template&lt;typename T = void&gt;
    class BasicResult : public ResultValueBase&lt;T&gt; {
    public:
        template&lt;typename U&gt;
        explicit BasicResult( BasicResult&lt;U&gt; const &amp;other )
        :   ResultValueBase&lt;T&gt;( other.type() ),
            m_errorMessage( other.errorMessage() )
        {
            assert( type() != ResultBase::Ok );
        }

        template&lt;typename U&gt;
        static auto ok( U const &amp;value ) -&gt; BasicResult { return { ResultBase::Ok, value }; }
        static auto ok() -&gt; BasicResult { return { ResultBase::Ok }; }
        static auto logicError( std::string const &amp;message ) -&gt; BasicResult { return { ResultBase::LogicError, message }; }
        static auto runtimeError( std::string const &amp;message ) -&gt; BasicResult { return { ResultBase::RuntimeError, message }; }

        explicit operator bool() const { return m_type == ResultBase::Ok; }
        auto type() const -&gt; ResultBase::Type { return m_type; }
        auto errorMessage() const -&gt; std::string { return m_errorMessage; }

    protected:
        virtual void enforceOk() const {
            // !TBD: If no exceptions, std::terminate here or something
            switch( m_type ) {
                case ResultBase::LogicError:
                    throw std::logic_error( m_errorMessage );
                case ResultBase::RuntimeError:
                    throw std::runtime_error( m_errorMessage );
                case ResultBase::Ok:
                    break;
            }
        }

        std::string m_errorMessage; // Only populated if resultType is an error

        BasicResult( ResultBase::Type type, std::string const &amp;message )
        :   ResultValueBase&lt;T&gt;(type),
            m_errorMessage(message)
        {
            assert( m_type != ResultBase::Ok );
        }

        using ResultValueBase&lt;T&gt;::ResultValueBase;
        using ResultBase::m_type;
    };

    enum class ParseResultType {
        Matched, NoMatch, ShortCircuitAll, ShortCircuitSame
    };

    class ParseState {
    public:

        ParseState( ParseResultType type, TokenStream const &amp;remainingTokens )
        : m_type(type),
          m_remainingTokens( remainingTokens )
        {}

        auto type() const -&gt; ParseResultType { return m_type; }
        auto remainingTokens() const -&gt; TokenStream { return m_remainingTokens; }

    private:
        ParseResultType m_type;
        TokenStream m_remainingTokens;
    };

    using Result = BasicResult&lt;void&gt;;
    using ParserResult = BasicResult&lt;ParseResultType&gt;;
    using InternalParseResult = BasicResult&lt;ParseState&gt;;

    struct HelpColumns {
        std::string left;
        std::string right;
    };

    template&lt;typename T&gt;
    inline auto convertInto( std::string const &amp;source, T&amp; target ) -&gt; ParserResult {
        std::stringstream ss;
        ss &lt;&lt; source;
        ss &gt;&gt; target;
        if( ss.fail() )
            return ParserResult::runtimeError( "Unable to convert '" + source + "' to destination type" );
        else
            return ParserResult::ok( ParseResultType::Matched );
    }
    inline auto convertInto( std::string const &amp;source, std::string&amp; target ) -&gt; ParserResult {
        target = source;
        return ParserResult::ok( ParseResultType::Matched );
    }
    inline auto convertInto( std::string const &amp;source, bool &amp;target ) -&gt; ParserResult {
        std::string srcLC = source;
        std::transform( srcLC.begin(), srcLC.end(), srcLC.begin(), []( char c ) { return static_cast&lt;char&gt;( ::tolower(c) ); } );
        if (srcLC == "y" || srcLC == "1" || srcLC == "true" || srcLC == "yes" || srcLC == "on")
            target = true;
        else if (srcLC == "n" || srcLC == "0" || srcLC == "false" || srcLC == "no" || srcLC == "off")
            target = false;
        else
            return ParserResult::runtimeError( "Expected a boolean value but did not recognise: '" + source + "'" );
        return ParserResult::ok( ParseResultType::Matched );
    }

    struct BoundRefBase {
        BoundRefBase() = default;
        BoundRefBase( BoundRefBase const &amp; ) = delete;
        BoundRefBase( BoundRefBase &amp;&amp; ) = delete;
        BoundRefBase &amp;operator=( BoundRefBase const &amp; ) = delete;
        BoundRefBase &amp;operator=( BoundRefBase &amp;&amp; ) = delete;

        virtual ~BoundRefBase() = default;

        virtual auto isFlag() const -&gt; bool = 0;
        virtual auto isContainer() const -&gt; bool { return false; }
        virtual auto setValue( std::string const &amp;arg ) -&gt; ParserResult = 0;
        virtual auto setFlag( bool flag ) -&gt; ParserResult = 0;
    };

    struct BoundValueRefBase : BoundRefBase {
        auto isFlag() const -&gt; bool override { return false; }

        auto setFlag( bool ) -&gt; ParserResult override {
            return ParserResult::logicError( "Flags can only be set on boolean fields" );
        }
    };

    struct BoundFlagRefBase : BoundRefBase {
        auto isFlag() const -&gt; bool override { return true; }

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            bool flag;
            auto result = convertInto( arg, flag );
            if( result )
                setFlag( flag );
            return result;
        }
    };

    template&lt;typename T&gt;
    struct BoundRef : BoundValueRefBase {
        T &amp;m_ref;

        explicit BoundRef( T &amp;ref ) : m_ref( ref ) {}

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            return convertInto( arg, m_ref );
        }
    };

    template&lt;typename T&gt;
    struct BoundRef&lt;std::vector&lt;T&gt;&gt; : BoundValueRefBase {
        std::vector&lt;T&gt; &amp;m_ref;

        explicit BoundRef( std::vector&lt;T&gt; &amp;ref ) : m_ref( ref ) {}

        auto isContainer() const -&gt; bool override { return true; }

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            T temp;
            auto result = convertInto( arg, temp );
            if( result )
                m_ref.push_back( temp );
            return result;
        }
    };

    struct BoundFlagRef : BoundFlagRefBase {
        bool &amp;m_ref;

        explicit BoundFlagRef( bool &amp;ref ) : m_ref( ref ) {}

        auto setFlag( bool flag ) -&gt; ParserResult override {
            m_ref = flag;
            return ParserResult::ok( ParseResultType::Matched );
        }
    };

    template&lt;typename ReturnType&gt;
    struct LambdaInvoker {
        static_assert( std::is_same&lt;ReturnType, ParserResult&gt;::value, "Lambda must return void or clara::ParserResult" );

        template&lt;typename L, typename ArgType&gt;
        static auto invoke( L const &amp;lambda, ArgType const &amp;arg ) -&gt; ParserResult {
            return lambda( arg );
        }
    };

    template&lt;&gt;
    struct LambdaInvoker&lt;void&gt; {
        template&lt;typename L, typename ArgType&gt;
        static auto invoke( L const &amp;lambda, ArgType const &amp;arg ) -&gt; ParserResult {
            lambda( arg );
            return ParserResult::ok( ParseResultType::Matched );
        }
    };

    template&lt;typename ArgType, typename L&gt;
    inline auto invokeLambda( L const &amp;lambda, std::string const &amp;arg ) -&gt; ParserResult {
        ArgType temp;
        auto result = convertInto( arg, temp );
        return !result
           ? result
           : LambdaInvoker&lt;typename UnaryLambdaTraits&lt;L&gt;::ReturnType&gt;::invoke( lambda, temp );
    };

    template&lt;typename L&gt;
    struct BoundLambda : BoundValueRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits&lt;L&gt;::isValid, "Supplied lambda must take exactly one argument" );
        explicit BoundLambda( L const &amp;lambda ) : m_lambda( lambda ) {}

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            return invokeLambda&lt;typename UnaryLambdaTraits&lt;L&gt;::ArgType&gt;( m_lambda, arg );
        }
    };

    template&lt;typename L&gt;
    struct BoundFlagLambda : BoundFlagRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits&lt;L&gt;::isValid, "Supplied lambda must take exactly one argument" );
        static_assert( std::is_same&lt;typename UnaryLambdaTraits&lt;L&gt;::ArgType, bool&gt;::value, "flags must be boolean" );

        explicit BoundFlagLambda( L const &amp;lambda ) : m_lambda( lambda ) {}

        auto setFlag( bool flag ) -&gt; ParserResult override {
            return LambdaInvoker&lt;typename UnaryLambdaTraits&lt;L&gt;::ReturnType&gt;::invoke( m_lambda, flag );
        }
    };

    enum class Optionality { Optional, Required };

    struct Parser;

    class ParserBase {
    public:
        virtual ~ParserBase() = default;
        virtual auto validate() const -&gt; Result { return Result::ok(); }
        virtual auto parse( std::string const&amp; exeName, TokenStream const &amp;tokens) const -&gt; InternalParseResult  = 0;
        virtual auto cardinality() const -&gt; size_t { return 1; }

        auto parse( Args const &amp;args ) const -&gt; InternalParseResult {
            return parse( args.exeName(), TokenStream( args ) );
        }
    };

    template&lt;typename DerivedT&gt;
    class ComposableParserImpl : public ParserBase {
    public:
        template&lt;typename T&gt;
        auto operator|( T const &amp;other ) const -&gt; Parser;
    };

    // Common code and state for Args and Opts
    template&lt;typename DerivedT&gt;
    class ParserRefImpl : public ComposableParserImpl&lt;DerivedT&gt; {
    protected:
        Optionality m_optionality = Optionality::Optional;
        std::shared_ptr&lt;BoundRefBase&gt; m_ref;
        std::string m_hint;
        std::string m_description;

        explicit ParserRefImpl( std::shared_ptr&lt;BoundRefBase&gt; const &amp;ref ) : m_ref( ref ) {}

    public:
        template&lt;typename T&gt;
        ParserRefImpl( T &amp;ref, std::string const &amp;hint )
        :   m_ref( std::make_shared&lt;BoundRef&lt;T&gt;&gt;( ref ) ),
            m_hint( hint )
        {}

        template&lt;typename LambdaT&gt;
        ParserRefImpl( LambdaT const &amp;ref, std::string const &amp;hint )
        :   m_ref( std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( ref ) ),
            m_hint(hint)
        {}

        auto operator()( std::string const &amp;description ) -&gt; DerivedT &amp; {
            m_description = description;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        }

        auto optional() -&gt; DerivedT &amp; {
            m_optionality = Optionality::Optional;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        };

        auto required() -&gt; DerivedT &amp; {
            m_optionality = Optionality::Required;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        };

        auto isOptional() const -&gt; bool {
            return m_optionality == Optionality::Optional;
        }

        auto cardinality() const -&gt; size_t override {
            if( m_ref-&gt;isContainer() )
                return 0;
            else
                return 1;
        }

        auto hint() const -&gt; std::string { return m_hint; }
    };

    class ExeName : public ComposableParserImpl&lt;ExeName&gt; {
        std::shared_ptr&lt;std::string&gt; m_name;
        std::shared_ptr&lt;BoundRefBase&gt; m_ref;

        template&lt;typename LambdaT&gt;
        static auto makeRef(LambdaT const &amp;lambda) -&gt; std::shared_ptr&lt;BoundRefBase&gt; {
            return std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( lambda) ;
        }

    public:
        ExeName() : m_name( std::make_shared&lt;std::string&gt;( "&lt;executable&gt;" ) ) {}

        explicit ExeName( std::string &amp;ref ) : ExeName() {
            m_ref = std::make_shared&lt;BoundRef&lt;std::string&gt;&gt;( ref );
        }

        template&lt;typename LambdaT&gt;
        explicit ExeName( LambdaT const&amp; lambda ) : ExeName() {
            m_ref = std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( lambda );
        }

        // The exe name is not parsed out of the normal tokens, but is handled specially
        auto parse( std::string const&amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, tokens ) );
        }

        auto name() const -&gt; std::string { return *m_name; }
        auto set( std::string const&amp; newName ) -&gt; ParserResult {

            auto lastSlash = newName.find_last_of( "\\/" );
            auto filename = ( lastSlash == std::string::npos )
                    ? newName
                    : newName.substr( lastSlash+1 );

            *m_name = filename;
            if( m_ref )
                return m_ref-&gt;setValue( filename );
            else
                return ParserResult::ok( ParseResultType::Matched );
        }
    };

    class Arg : public ParserRefImpl&lt;Arg&gt; {
    public:
        using ParserRefImpl::ParserRefImpl;

        auto parse( std::string const &amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            auto validationResult = validate();
            if( !validationResult )
                return InternalParseResult( validationResult );

            auto remainingTokens = tokens;
            auto const &amp;token = *remainingTokens;
            if( token.type != TokenType::Argument )
                return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, remainingTokens ) );

            auto result = m_ref-&gt;setValue( remainingTokens-&gt;token );
            if( !result )
                return InternalParseResult( result );
            else
                return InternalParseResult::ok( ParseState( ParseResultType::Matched, ++remainingTokens ) );
        }
    };

    inline auto normaliseOpt( std::string const &amp;optName ) -&gt; std::string {
#ifdef CATCH_PLATFORM_WINDOWS
        if( optName[0] == '/' )
            return "-" + optName.substr( 1 );
        else
#endif
            return optName;
    }

    class Opt : public ParserRefImpl&lt;Opt&gt; {
    protected:
        std::vector&lt;std::string&gt; m_optNames;

    public:
        template&lt;typename LambdaT&gt;
        explicit Opt( LambdaT const &amp;ref ) : ParserRefImpl( std::make_shared&lt;BoundFlagLambda&lt;LambdaT&gt;&gt;( ref ) ) {}

        explicit Opt( bool &amp;ref ) : ParserRefImpl( std::make_shared&lt;BoundFlagRef&gt;( ref ) ) {}

        template&lt;typename LambdaT&gt;
        Opt( LambdaT const &amp;ref, std::string const &amp;hint ) : ParserRefImpl( ref, hint ) {}

        template&lt;typename T&gt;
        Opt( T &amp;ref, std::string const &amp;hint ) : ParserRefImpl( ref, hint ) {}

        auto operator[]( std::string const &amp;optName ) -&gt; Opt &amp; {
            m_optNames.push_back( optName );
            return *this;
        }

        auto getHelpColumns() const -&gt; std::vector&lt;HelpColumns&gt; {
            std::ostringstream oss;
            bool first = true;
            for( auto const &amp;opt : m_optNames ) {
                if (first)
                    first = false;
                else
                    oss &lt;&lt; ", ";
                oss &lt;&lt; opt;
            }
            if( !m_hint.empty() )
                oss &lt;&lt; " &lt;" &lt;&lt; m_hint &lt;&lt; "&gt;";
            return { { oss.str(), m_description } };
        }

        auto isMatch( std::string const &amp;optToken ) const -&gt; bool {
            auto normalisedToken = normaliseOpt( optToken );
            for( auto const &amp;name : m_optNames ) {
                if( normaliseOpt( name ) == normalisedToken )
                    return true;
            }
            return false;
        }

        using ParserBase::parse;

        auto parse( std::string const&amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            auto validationResult = validate();
            if( !validationResult )
                return InternalParseResult( validationResult );

            auto remainingTokens = tokens;
            if( remainingTokens &amp;&amp; remainingTokens-&gt;type == TokenType::Option ) {
                auto const &amp;token = *remainingTokens;
                if( isMatch(token.token ) ) {
                    if( m_ref-&gt;isFlag() ) {
                        auto result = m_ref-&gt;setFlag( true );
                        if( !result )
                            return InternalParseResult( result );
                        if( result.value() == ParseResultType::ShortCircuitAll )
                            return InternalParseResult::ok( ParseState( result.value(), remainingTokens ) );
                    } else {
                        ++remainingTokens;
                        if( !remainingTokens )
                            return InternalParseResult::runtimeError( "Expected argument following " + token.token );
                        auto const &amp;argToken = *remainingTokens;
                        if( argToken.type != TokenType::Argument )
                            return InternalParseResult::runtimeError( "Expected argument following " + token.token );
                        auto result = m_ref-&gt;setValue( argToken.token );
                        if( !result )
                            return InternalParseResult( result );
                        if( result.value() == ParseResultType::ShortCircuitAll )
                            return InternalParseResult::ok( ParseState( result.value(), remainingTokens ) );
                    }
                    return InternalParseResult::ok( ParseState( ParseResultType::Matched, ++remainingTokens ) );
                }
            }
            return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, remainingTokens ) );
        }

        auto validate() const -&gt; Result override {
            if( m_optNames.empty() )
                return Result::logicError( "No options supplied to Opt" );
            for( auto const &amp;name : m_optNames ) {
                if( name.empty() )
                    return Result::logicError( "Option name cannot be empty" );
#ifdef CATCH_PLATFORM_WINDOWS
                if( name[0] != '-' &amp;&amp; name[0] != '/' )
                    return Result::logicError( "Option name must begin with '-' or '/'" );
#else
                if( name[0] != '-' )
                    return Result::logicError( "Option name must begin with '-'" );
#endif
            }
            return ParserRefImpl::validate();
        }
    };

    struct Help : Opt {
        Help( bool &amp;showHelpFlag )
        :   Opt([&amp;]( bool flag ) {
                showHelpFlag = flag;
                return ParserResult::ok( ParseResultType::ShortCircuitAll );
            })
        {
            static_cast&lt;Opt &amp;&gt;( *this )
                    ("display usage information")
                    ["-?"]["-h"]["--help"]
                    .optional();
        }
    };

    struct Parser : ParserBase {

        mutable ExeName m_exeName;
        std::vector&lt;Opt&gt; m_options;
        std::vector&lt;Arg&gt; m_args;

        auto operator|=( ExeName const &amp;exeName ) -&gt; Parser &amp; {
            m_exeName = exeName;
            return *this;
        }

        auto operator|=( Arg const &amp;arg ) -&gt; Parser &amp; {
            m_args.push_back(arg);
            return *this;
        }

        auto operator|=( Opt const &amp;opt ) -&gt; Parser &amp; {
            m_options.push_back(opt);
            return *this;
        }

        auto operator|=( Parser const &amp;other ) -&gt; Parser &amp; {
            m_options.insert(m_options.end(), other.m_options.begin(), other.m_options.end());
            m_args.insert(m_args.end(), other.m_args.begin(), other.m_args.end());
            return *this;
        }

        template&lt;typename T&gt;
        auto operator|( T const &amp;other ) const -&gt; Parser {
            return Parser( *this ) |= other;
        }

        auto getHelpColumns() const -&gt; std::vector&lt;HelpColumns&gt; {
            std::vector&lt;HelpColumns&gt; cols;
            for (auto const &amp;o : m_options) {
                auto childCols = o.getHelpColumns();
                cols.insert( cols.end(), childCols.begin(), childCols.end() );
            }
            return cols;
        }

        void writeToStream( std::ostream &amp;os ) const {
            if (!m_exeName.name().empty()) {
                os &lt;&lt; "usage:\n" &lt;&lt; "  " &lt;&lt; m_exeName.name() &lt;&lt; " ";
                bool required = true, first = true;
                for( auto const &amp;arg : m_args ) {
                    if (first)
                        first = false;
                    else
                        os &lt;&lt; " ";
                    if( arg.isOptional() &amp;&amp; required ) {
                        os &lt;&lt; "[";
                        required = false;
                    }
                    os &lt;&lt; "&lt;" &lt;&lt; arg.hint() &lt;&lt; "&gt;";
                    if( arg.cardinality() == 0 )
                        os &lt;&lt; " ... ";
                }
                if( !required )
                    os &lt;&lt; "]";
                if( !m_options.empty() )
                    os &lt;&lt; " options";
                os &lt;&lt; "\n\nwhere options are:" &lt;&lt; std::endl;
            }

            auto rows = getHelpColumns();
            size_t consoleWidth = CATCH_CLARA_CONFIG_CONSOLE_WIDTH;
            size_t optWidth = 0;
            for( auto const &amp;cols : rows )
                optWidth = (std::max)(optWidth, cols.left.size() + 2);

            for( auto const &amp;cols : rows ) {
                auto row =
                        TextFlow::Column( cols.left ).width( optWidth ).indent( 2 ) +
                        TextFlow::Spacer(4) +
                        TextFlow::Column( cols.right ).width( consoleWidth - 7 - optWidth );
                os &lt;&lt; row &lt;&lt; std::endl;
            }
        }

        friend auto operator&lt;&lt;( std::ostream &amp;os, Parser const &amp;parser ) -&gt; std::ostream&amp; {
            parser.writeToStream( os );
            return os;
        }

        auto validate() const -&gt; Result override {
            for( auto const &amp;opt : m_options ) {
                auto result = opt.validate();
                if( !result )
                    return result;
            }
            for( auto const &amp;arg : m_args ) {
                auto result = arg.validate();
                if( !result )
                    return result;
            }
            return Result::ok();
        }

        using ParserBase::parse;

        auto parse( std::string const&amp; exeName, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {

            struct ParserInfo {
                ParserBase const* parser = nullptr;
                size_t count = 0;
            };
            const size_t totalParsers = m_options.size() + m_args.size();
            assert( totalParsers &lt; 512 );
            // ParserInfo parseInfos[totalParsers]; // &lt;-- this is what we really want to do
            ParserInfo parseInfos[512];

            {
                size_t i = 0;
                for (auto const &amp;opt : m_options) parseInfos[i++].parser = &amp;opt;
                for (auto const &amp;arg : m_args) parseInfos[i++].parser = &amp;arg;
            }

            m_exeName.set( exeName );

            auto result = InternalParseResult::ok( ParseState( ParseResultType::NoMatch, tokens ) );
            while( result.value().remainingTokens() ) {
                bool tokenParsed = false;

                for( size_t i = 0; i &lt; totalParsers; ++i ) {
                    auto&amp;  parseInfo = parseInfos[i];
                    if( parseInfo.parser-&gt;cardinality() == 0 || parseInfo.count &lt; parseInfo.parser-&gt;cardinality() ) {
                        result = parseInfo.parser-&gt;parse(exeName, result.value().remainingTokens());
                        if (!result)
                            return result;
                        if (result.value().type() != ParseResultType::NoMatch) {
                            tokenParsed = true;
                            ++parseInfo.count;
                            break;
                        }
                    }
                }

                if( result.value().type() == ParseResultType::ShortCircuitAll )
                    return result;
                if( !tokenParsed )
                    return InternalParseResult::runtimeError( "Unrecognised token: " + result.value().remainingTokens()-&gt;token );
            }
            // !TBD Check missing required options
            return result;
        }
    };

    template&lt;typename DerivedT&gt;
    template&lt;typename T&gt;
    auto ComposableParserImpl&lt;DerivedT&gt;::operator|( T const &amp;other ) const -&gt; Parser {
        return Parser() | static_cast&lt;DerivedT const &amp;&gt;( *this ) | other;
    }
} // namespace detail

// A Combined parser
using detail::Parser;

// A parser for options
using detail::Opt;

// A parser for arguments
using detail::Arg;

// Wrapper for argc, argv from main()
using detail::Args;

// Specifies the name of the executable
using detail::ExeName;

// Convenience wrapper for option parser that specifies the help option
using detail::Help;

// enum of result types from a parse
using detail::ParseResultType;

// Result type for parser operation
using detail::ParserResult;

}} // namespace Catch::clara

// end clara.hpp
#ifdef __clang__
#pragma clang diagnostic pop
#endif

// Restore Clara's value for console width, if present
#ifdef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#undef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#endif

// end catch_clara.h
namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData&amp; config );

} // end namespace Catch

// end catch_commandline.h
#include &lt;fstream&gt;
#include &lt;ctime&gt;

namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData&amp; config ) {

        using namespace clara;

        auto const setWarning = [&amp;]( std::string const&amp; warning ) {
                if( warning != "NoAssertions" )
                    return ParserResult::runtimeError( "Unrecognised warning: '" + warning + "'" );
                config.warnings = static_cast&lt;WarnAbout::What&gt;( config.warnings | WarnAbout::NoAssertions );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const loadTestNamesFromFile = [&amp;]( std::string const&amp; filename ) {
                std::ifstream f( filename.c_str() );
                if( !f.is_open() )
                    return ParserResult::runtimeError( "Unable to load input file: '" + filename + "'" );

                std::string line;
                while( std::getline( f, line ) ) {
                    line = trim(line);
                    if( !line.empty() &amp;&amp; !startsWith( line, '#' ) ) {
                        if( !startsWith( line, '"' ) )
                            line = '"' + line + '"';
                        config.testsOrTags.push_back( line + ',' );
                    }
                }
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setTestOrder = [&amp;]( std::string const&amp; order ) {
                if( startsWith( "declared", order ) )
                    config.runOrder = RunTests::InDeclarationOrder;
                else if( startsWith( "lexical", order ) )
                    config.runOrder = RunTests::InLexicographicalOrder;
                else if( startsWith( "random", order ) )
                    config.runOrder = RunTests::InRandomOrder;
                else
                    return clara::ParserResult::runtimeError( "Unrecognised ordering: '" + order + "'" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setRngSeed = [&amp;]( std::string const&amp; seed ) {
                if( seed != "time" )
                    return clara::detail::convertInto( seed, config.rngSeed );
                config.rngSeed = static_cast&lt;unsigned int&gt;( std::time(nullptr) );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setColourUsage = [&amp;]( std::string const&amp; useColour ) {
                    auto mode = toLower( useColour );

                    if( mode == "yes" )
                        config.useColour = UseColour::Yes;
                    else if( mode == "no" )
                        config.useColour = UseColour::No;
                    else if( mode == "auto" )
                        config.useColour = UseColour::Auto;
                    else
                        return ParserResult::runtimeError( "colour mode must be one of: auto, yes or no. '" + useColour + "' not recognised" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setWaitForKeypress = [&amp;]( std::string const&amp; keypress ) {
                auto keypressLc = toLower( keypress );
                if( keypressLc == "start" )
                    config.waitForKeypress = WaitForKeypress::BeforeStart;
                else if( keypressLc == "exit" )
                    config.waitForKeypress = WaitForKeypress::BeforeExit;
                else if( keypressLc == "both" )
                    config.waitForKeypress = WaitForKeypress::BeforeStartAndExit;
                else
                    return ParserResult::runtimeError( "keypress argument must be one of: start, exit or both. '" + keypress + "' not recognised" );
            return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setVerbosity = [&amp;]( std::string const&amp; verbosity ) {
            auto lcVerbosity = toLower( verbosity );
            if( lcVerbosity == "quiet" )
                config.verbosity = Verbosity::Quiet;
            else if( lcVerbosity == "normal" )
                config.verbosity = Verbosity::Normal;
            else if( lcVerbosity == "high" )
                config.verbosity = Verbosity::High;
            else
                return ParserResult::runtimeError( "Unrecognised verbosity, '" + verbosity + "'" );
            return ParserResult::ok( ParseResultType::Matched );
        };

        auto cli
            = ExeName( config.processName )
            | Help( config.showHelp )
            | Opt( config.listTests )
                ["-l"]["--list-tests"]
                ( "list all/matching test cases" )
            | Opt( config.listTags )
                ["-t"]["--list-tags"]
                ( "list all/matching tags" )
            | Opt( config.showSuccessfulTests )
                ["-s"]["--success"]
                ( "include successful tests in output" )
            | Opt( config.shouldDebugBreak )
                ["-b"]["--break"]
                ( "break into debugger on failure" )
            | Opt( config.noThrow )
                ["-e"]["--nothrow"]
                ( "skip exception tests" )
            | Opt( config.showInvisibles )
                ["-i"]["--invisibles"]
                ( "show invisibles (tabs, newlines)" )
            | Opt( config.outputFilename, "filename" )
                ["-o"]["--out"]
                ( "output filename" )
            | Opt( config.reporterNames, "name" )
                ["-r"]["--reporter"]
                ( "reporter to use (defaults to console)" )
            | Opt( config.name, "name" )
                ["-n"]["--name"]
                ( "suite name" )
            | Opt( [&amp;]( bool ){ config.abortAfter = 1; } )
                ["-a"]["--abort"]
                ( "abort at first failure" )
            | Opt( [&amp;]( int x ){ config.abortAfter = x; }, "no. failures" )
                ["-x"]["--abortx"]
                ( "abort after x failures" )
            | Opt( setWarning, "warning name" )
                ["-w"]["--warn"]
                ( "enable warnings" )
            | Opt( [&amp;]( bool flag ) { config.showDurations = flag ? ShowDurations::Always : ShowDurations::Never; }, "yes|no" )
                ["-d"]["--durations"]
                ( "show test durations" )
            | Opt( loadTestNamesFromFile, "filename" )
                ["-f"]["--input-file"]
                ( "load test names to run from a file" )
            | Opt( config.filenamesAsTags )
                ["-#"]["--filenames-as-tags"]
                ( "adds a tag for the filename" )
            | Opt( config.sectionsToRun, "section name" )
                ["-c"]["--section"]
                ( "specify section to run" )
            | Opt( setVerbosity, "quiet|normal|high" )
                ["-v"]["--verbosity"]
                ( "set output verbosity" )
            | Opt( config.listTestNamesOnly )
                ["--list-test-names-only"]
                ( "list all/matching test cases names only" )
            | Opt( config.listReporters )
                ["--list-reporters"]
                ( "list all reporters" )
            | Opt( setTestOrder, "decl|lex|rand" )
                ["--order"]
                ( "test case order (defaults to decl)" )
            | Opt( setRngSeed, "'time'|number" )
                ["--rng-seed"]
                ( "set a specific seed for random numbers" )
            | Opt( setColourUsage, "yes|no" )
                ["--use-colour"]
                ( "should output be colourised" )
            | Opt( config.libIdentify )
                ["--libidentify"]
                ( "report name and version according to libidentify standard" )
            | Opt( setWaitForKeypress, "start|exit|both" )
                ["--wait-for-keypress"]
                ( "waits for a keypress before exiting" )
            | Opt( config.benchmarkResolutionMultiple, "multiplier" )
                ["--benchmark-resolution-multiple"]
                ( "multiple of clock resolution to run benchmarks" )

            | Arg( config.testsOrTags, "test name|pattern|tags" )
                ( "which test or tests to use" );

        return cli;
    }

} // end namespace Catch
// end catch_commandline.cpp
// start catch_common.cpp

#include &lt;cstring&gt;
#include &lt;ostream&gt;

namespace Catch {

    SourceLineInfo::SourceLineInfo( char const* _file, std::size_t _line ) noexcept
    :   file( _file ),
        line( _line )
    {}
    bool SourceLineInfo::empty() const noexcept {
        return file[0] == '\0';
    }
    bool SourceLineInfo::operator == ( SourceLineInfo const&amp; other ) const noexcept {
        return line == other.line &amp;&amp; (file == other.file || std::strcmp(file, other.file) == 0);
    }
    bool SourceLineInfo::operator &lt; ( SourceLineInfo const&amp; other ) const noexcept {
        return line &lt; other.line || ( line == other.line &amp;&amp; (std::strcmp(file, other.file) &lt; 0));
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, SourceLineInfo const&amp; info ) {
#ifndef __GNUG__
        os &lt;&lt; info.file &lt;&lt; '(' &lt;&lt; info.line &lt;&lt; ')';
#else
        os &lt;&lt; info.file &lt;&lt; ':' &lt;&lt; info.line;
#endif
        return os;
    }

    bool isTrue( bool value ){ return value; }
    bool alwaysTrue() { return true; }
    bool alwaysFalse() { return false; }

    std::string StreamEndStop::operator+() const {
        return std::string();
    }

    NonCopyable::NonCopyable() = default;
    NonCopyable::~NonCopyable() = default;

}
// end catch_common.cpp
// start catch_config.cpp

namespace Catch {

    Config::Config( ConfigData const&amp; data )
    :   m_data( data ),
        m_stream( openStream() )
    {
        if( !data.testsOrTags.empty() ) {
            TestSpecParser parser( ITagAliasRegistry::get() );
            for( auto const&amp; testOrTags : data.testsOrTags )
                parser.parse( testOrTags );
            m_testSpec = parser.testSpec();
        }
    }

    std::string const&amp; Config::getFilename() const {
        return m_data.outputFilename ;
    }

    bool Config::listTests() const          { return m_data.listTests; }
    bool Config::listTestNamesOnly() const  { return m_data.listTestNamesOnly; }
    bool Config::listTags() const           { return m_data.listTags; }
    bool Config::listReporters() const      { return m_data.listReporters; }

    std::string Config::getProcessName() const { return m_data.processName; }

    std::vector&lt;std::string&gt; const&amp; Config::getReporterNames() const { return m_data.reporterNames; }
    std::vector&lt;std::string&gt; const&amp; Config::getSectionsToRun() const { return m_data.sectionsToRun; }

    TestSpec const&amp; Config::testSpec() const { return m_testSpec; }

    bool Config::showHelp() const { return m_data.showHelp; }

    // IConfig interface
    bool Config::allowThrows() const                   { return !m_data.noThrow; }
    std::ostream&amp; Config::stream() const               { return m_stream-&gt;stream(); }
    std::string Config::name() const                   { return m_data.name.empty() ? m_data.processName : m_data.name; }
    bool Config::includeSuccessfulResults() const      { return m_data.showSuccessfulTests; }
    bool Config::warnAboutMissingAssertions() const    { return m_data.warnings &amp; WarnAbout::NoAssertions; }
    ShowDurations::OrNot Config::showDurations() const { return m_data.showDurations; }
    RunTests::InWhatOrder Config::runOrder() const     { return m_data.runOrder; }
    unsigned int Config::rngSeed() const               { return m_data.rngSeed; }
    int Config::benchmarkResolutionMultiple() const    { return m_data.benchmarkResolutionMultiple; }
    UseColour::YesOrNo Config::useColour() const       { return m_data.useColour; }
    bool Config::shouldDebugBreak() const              { return m_data.shouldDebugBreak; }
    int Config::abortAfter() const                     { return m_data.abortAfter; }
    bool Config::showInvisibles() const                { return m_data.showInvisibles; }
    Verbosity Config::verbosity() const                { return m_data.verbosity; }

    IStream const* Config::openStream() {
        if( m_data.outputFilename.empty() )
            return new CoutStream();
        else if( m_data.outputFilename[0] == '%' ) {
            if( m_data.outputFilename == "%debug" )
                return new DebugOutStream();
            else
                CATCH_ERROR( "Unrecognised stream: '" &lt;&lt; m_data.outputFilename &lt;&lt; "'" );
        }
        else
            return new FileStream( m_data.outputFilename );
    }

} // end namespace Catch
// end catch_config.cpp
// start catch_console_colour.cpp

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

// start catch_errno_guard.h

namespace Catch {

    class ErrnoGuard {
    public:
        ErrnoGuard();
        ~ErrnoGuard();
    private:
        int m_oldErrno;
    };

}

// end catch_errno_guard.h
// start catch_windows_h_proxy.h


#if defined(CATCH_PLATFORM_WINDOWS)

#if !defined(NOMINMAX) &amp;&amp; !defined(CATCH_CONFIG_NO_NOMINMAX)
#  define CATCH_DEFINED_NOMINMAX
#  define NOMINMAX
#endif
#if !defined(WIN32_LEAN_AND_MEAN) &amp;&amp; !defined(CATCH_CONFIG_NO_WIN32_LEAN_AND_MEAN)
#  define CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif

#ifdef __AFXDLL
#include &lt;AfxWin.h&gt;
#else
#include &lt;windows.h&gt;
#endif

#ifdef CATCH_DEFINED_NOMINMAX
#  undef NOMINMAX
#endif
#ifdef CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#  undef WIN32_LEAN_AND_MEAN
#endif

#endif // defined(CATCH_PLATFORM_WINDOWS)

// end catch_windows_h_proxy.h
namespace Catch {
    namespace {

        struct IColourImpl {
            virtual ~IColourImpl() = default;
            virtual void use( Colour::Code _colourCode ) = 0;
        };

        struct NoColourImpl : IColourImpl {
            void use( Colour::Code ) {}

            static IColourImpl* instance() {
                static NoColourImpl s_instance;
                return &amp;s_instance;
            }
        };

    } // anon namespace
} // namespace Catch

#if !defined( CATCH_CONFIG_COLOUR_NONE ) &amp;&amp; !defined( CATCH_CONFIG_COLOUR_WINDOWS ) &amp;&amp; !defined( CATCH_CONFIG_COLOUR_ANSI )
#   ifdef CATCH_PLATFORM_WINDOWS
#       define CATCH_CONFIG_COLOUR_WINDOWS
#   else
#       define CATCH_CONFIG_COLOUR_ANSI
#   endif
#endif

#if defined ( CATCH_CONFIG_COLOUR_WINDOWS ) /////////////////////////////////////////

namespace Catch {
namespace {

    class Win32ColourImpl : public IColourImpl {
    public:
        Win32ColourImpl() : stdoutHandle( GetStdHandle(STD_OUTPUT_HANDLE) )
        {
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            GetConsoleScreenBufferInfo( stdoutHandle, &amp;csbiInfo );
            originalForegroundAttributes = csbiInfo.wAttributes &amp; ~( BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY );
            originalBackgroundAttributes = csbiInfo.wAttributes &amp; ~( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        }

        virtual void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:      return setTextAttribute( originalForegroundAttributes );
                case Colour::White:     return setTextAttribute( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
                case Colour::Red:       return setTextAttribute( FOREGROUND_RED );
                case Colour::Green:     return setTextAttribute( FOREGROUND_GREEN );
                case Colour::Blue:      return setTextAttribute( FOREGROUND_BLUE );
                case Colour::Cyan:      return setTextAttribute( FOREGROUND_BLUE | FOREGROUND_GREEN );
                case Colour::Yellow:    return setTextAttribute( FOREGROUND_RED | FOREGROUND_GREEN );
                case Colour::Grey:      return setTextAttribute( 0 );

                case Colour::LightGrey:     return setTextAttribute( FOREGROUND_INTENSITY );
                case Colour::BrightRed:     return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_RED );
                case Colour::BrightGreen:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN );
                case Colour::BrightWhite:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );
            }
        }

    private:
        void setTextAttribute( WORD _textAttribute ) {
            SetConsoleTextAttribute( stdoutHandle, _textAttribute | originalBackgroundAttributes );
        }
        HANDLE stdoutHandle;
        WORD originalForegroundAttributes;
        WORD originalBackgroundAttributes;
    };

    IColourImpl* platformColourInstance() {
        static Win32ColourImpl s_instance;

        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config-&gt;useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = UseColour::Yes;
        return colourMode == UseColour::Yes
            ? &amp;s_instance
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#elif defined( CATCH_CONFIG_COLOUR_ANSI ) //////////////////////////////////////

#include &lt;unistd.h&gt;

namespace Catch {
namespace {

    // use POSIX/ ANSI console terminal codes
    // Thanks to Adam Strzelecki for original contribution
    // (http://github.com/nanoant)
    // https://github.com/philsquared/Catch/pull/131
    class PosixColourImpl : public IColourImpl {
    public:
        virtual void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:
                case Colour::White:     return setColour( "[0m" );
                case Colour::Red:       return setColour( "[0;31m" );
                case Colour::Green:     return setColour( "[0;32m" );
                case Colour::Blue:      return setColour( "[0;34m" );
                case Colour::Cyan:      return setColour( "[0;36m" );
                case Colour::Yellow:    return setColour( "[0;33m" );
                case Colour::Grey:      return setColour( "[1;30m" );

                case Colour::LightGrey:     return setColour( "[0;37m" );
                case Colour::BrightRed:     return setColour( "[1;31m" );
                case Colour::BrightGreen:   return setColour( "[1;32m" );
                case Colour::BrightWhite:   return setColour( "[1;37m" );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );
            }
        }
        static IColourImpl* instance() {
            static PosixColourImpl s_instance;
            return &amp;s_instance;
        }

    private:
        void setColour( const char* _escapeCode ) {
            Catch::cout() &lt;&lt; '\033' &lt;&lt; _escapeCode;
        }
    };

    bool useColourOnPlatform() {
        return
#ifdef CATCH_PLATFORM_MAC
            !isDebuggerActive() &amp;&amp;
#endif
            isatty(STDOUT_FILENO);
    }
    IColourImpl* platformColourInstance() {
        ErrnoGuard guard;
        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config-&gt;useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = useColourOnPlatform()
                ? UseColour::Yes
                : UseColour::No;
        return colourMode == UseColour::Yes
            ? PosixColourImpl::instance()
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#else  // not Windows or ANSI ///////////////////////////////////////////////

namespace Catch {

    static IColourImpl* platformColourInstance() { return NoColourImpl::instance(); }

} // end namespace Catch

#endif // Windows/ ANSI/ None

namespace Catch {

    Colour::Colour( Code _colourCode ) { use( _colourCode ); }
    Colour::Colour( Colour&amp;&amp; rhs ) noexcept {
        m_moved = rhs.m_moved;
        rhs.m_moved = true;
    }
    Colour&amp; Colour::operator=( Colour&amp;&amp; rhs ) noexcept {
        m_moved = rhs.m_moved;
        rhs.m_moved  = true;
        return *this;
    }

    Colour::~Colour(){ if( !m_moved ) use( None ); }

    void Colour::use( Code _colourCode ) {
        static IColourImpl* impl = platformColourInstance();
        impl-&gt;use( _colourCode );
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Colour const&amp; ) {
        return os;
    }

} // end namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif

// end catch_console_colour.cpp
// start catch_context.cpp

namespace Catch {

    class Context : public IMutableContext, NonCopyable {

    public: // IContext
        virtual IResultCapture* getResultCapture() override {
            return m_resultCapture;
        }
        virtual IRunner* getRunner() override {
            return m_runner;
        }

        virtual IConfigPtr getConfig() const override {
            return m_config;
        }

        virtual ~Context() override;

    public: // IMutableContext
        virtual void setResultCapture( IResultCapture* resultCapture ) override {
            m_resultCapture = resultCapture;
        }
        virtual void setRunner( IRunner* runner ) override {
            m_runner = runner;
        }
        virtual void setConfig( IConfigPtr const&amp; config ) override {
            m_config = config;
        }

        friend IMutableContext&amp; getCurrentMutableContext();

    private:
        IConfigPtr m_config;
        IRunner* m_runner = nullptr;
        IResultCapture* m_resultCapture = nullptr;
    };

    namespace {
        Context* currentContext = nullptr;
    }
    IMutableContext&amp; getCurrentMutableContext() {
        if( !currentContext )
            currentContext = new Context();
        return *currentContext;
    }
    IContext&amp; getCurrentContext() {
        return getCurrentMutableContext();
    }

    void cleanUpContext() {
        delete currentContext;
        currentContext = nullptr;
    }
    IContext::~IContext() = default;
    IMutableContext::~IMutableContext() = default;
    Context::~Context() = default;
}
// end catch_context.cpp
// start catch_debug_console.cpp

// start catch_debug_console.h

#include &lt;string&gt;

namespace Catch {
    void writeToDebugConsole( std::string const&amp; text );
}

// end catch_debug_console.h
#ifdef CATCH_PLATFORM_WINDOWS

    namespace Catch {
        void writeToDebugConsole( std::string const&amp; text ) {
            ::OutputDebugStringA( text.c_str() );
        }
    }
#else
    namespace Catch {
        void writeToDebugConsole( std::string const&amp; text ) {
            // !TBD: Need a version for Mac/ XCode and other IDEs
            Catch::cout() &lt;&lt; text;
        }
    }
#endif // Platform
// end catch_debug_console.cpp
// start catch_debugger.cpp

#ifdef CATCH_PLATFORM_MAC

    #include &lt;assert.h&gt;
    #include &lt;stdbool.h&gt;
    #include &lt;sys/types.h&gt;
    #include &lt;unistd.h&gt;
    #include &lt;sys/sysctl.h&gt;

    namespace Catch {

        // The following function is taken directly from the following technical note:
        // http://developer.apple.com/library/mac/#qa/qa2004/qa1361.html

        // Returns true if the current process is being debugged (either
        // running under the debugger or has a debugger attached post facto).
        bool isDebuggerActive(){

            int                 mib[4];
            struct kinfo_proc   info;
            std::size_t         size;

            // Initialize the flags so that, if sysctl fails for some bizarre
            // reason, we get a predictable result.

            info.kp_proc.p_flag = 0;

            // Initialize mib, which tells sysctl the info we want, in this case
            // we're looking for information about a specific process ID.

            mib[0] = CTL_KERN;
            mib[1] = KERN_PROC;
            mib[2] = KERN_PROC_PID;
            mib[3] = getpid();

            // Call sysctl.

            size = sizeof(info);
            if( sysctl(mib, sizeof(mib) / sizeof(*mib), &amp;info, &amp;size, nullptr, 0) != 0 ) {
                Catch::cerr() &lt;&lt; "\n** Call to sysctl failed - unable to determine if debugger is active **\n" &lt;&lt; std::endl;
                return false;
            }

            // We're being debugged if the P_TRACED flag is set.

            return ( (info.kp_proc.p_flag &amp; P_TRACED) != 0 );
        }
    } // namespace Catch

#elif defined(CATCH_PLATFORM_LINUX)
    #include &lt;fstream&gt;
    #include &lt;string&gt;

    namespace Catch{
        // The standard POSIX way of detecting a debugger is to attempt to
        // ptrace() the process, but this needs to be done from a child and not
        // this process itself to still allow attaching to this process later
        // if wanted, so is rather heavy. Under Linux we have the PID of the
        // "debugger" (which doesn't need to be gdb, of course, it could also
        // be strace, for example) in /proc/$PID/status, so just get it from
        // there instead.
        bool isDebuggerActive(){
            // Libstdc++ has a bug, where std::ifstream sets errno to 0
            // This way our users can properly assert over errno values
            ErrnoGuard guard;
            std::ifstream in("/proc/self/status");
            for( std::string line; std::getline(in, line); ) {
                static const int PREFIX_LEN = 11;
                if( line.compare(0, PREFIX_LEN, "TracerPid:\t") == 0 ) {
                    // We're traced if the PID is not 0 and no other PID starts
                    // with 0 digit, so it's enough to check for just a single
                    // character.
                    return line.length() &gt; PREFIX_LEN &amp;&amp; line[PREFIX_LEN] != '0';
                }
            }

            return false;
        }
    } // namespace Catch
#elif defined(_MSC_VER)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#else
    namespace Catch {
       bool isDebuggerActive() { return false; }
    }
#endif // Platform
// end catch_debugger.cpp
// start catch_decomposer.cpp

namespace Catch {

    ITransientExpression::~ITransientExpression() = default;

    void formatReconstructedExpression( std::ostream &amp;os, std::string const&amp; lhs, StringRef op, std::string const&amp; rhs ) {
        if( lhs.size() + rhs.size() &lt; 40 &amp;&amp;
                lhs.find('\n') == std::string::npos &amp;&amp;
                rhs.find('\n') == std::string::npos )
            os &lt;&lt; lhs &lt;&lt; " " &lt;&lt; op &lt;&lt; " " &lt;&lt; rhs;
        else
            os &lt;&lt; lhs &lt;&lt; "\n" &lt;&lt; op &lt;&lt; "\n" &lt;&lt; rhs;
    }
}
// end catch_decomposer.cpp
// start catch_errno_guard.cpp

#include &lt;cerrno&gt;

namespace Catch {
        ErrnoGuard::ErrnoGuard():m_oldErrno(errno){}
        ErrnoGuard::~ErrnoGuard() { errno = m_oldErrno; }
}
// end catch_errno_guard.cpp
// start catch_exception_translator_registry.cpp

// start catch_exception_translator_registry.h

#include &lt;vector&gt;
#include &lt;string&gt;
#include &lt;memory&gt;

namespace Catch {

    class ExceptionTranslatorRegistry : public IExceptionTranslatorRegistry {
    public:
        ~ExceptionTranslatorRegistry();
        virtual void registerTranslator( const IExceptionTranslator* translator );
        virtual std::string translateActiveException() const override;
        std::string tryTranslators() const;

    private:
        std::vector&lt;std::unique_ptr&lt;IExceptionTranslator const&gt;&gt; m_translators;
    };
}

// end catch_exception_translator_registry.h
#ifdef __OBJC__
#import "Foundation/Foundation.h"
#endif

namespace Catch {

    ExceptionTranslatorRegistry::~ExceptionTranslatorRegistry() {
    }

    void ExceptionTranslatorRegistry::registerTranslator( const IExceptionTranslator* translator ) {
        m_translators.push_back( std::unique_ptr&lt;const IExceptionTranslator&gt;( translator ) );
    }

    std::string ExceptionTranslatorRegistry::translateActiveException() const {
        try {
#ifdef __OBJC__
            // In Objective-C try objective-c exceptions first
            @try {
                return tryTranslators();
            }
            @catch (NSException *exception) {
                return Catch::Detail::stringify( [exception description] );
            }
#else
            return tryTranslators();
#endif
        }
        catch( TestFailureException&amp; ) {
            std::rethrow_exception(std::current_exception());
        }
        catch( std::exception&amp; ex ) {
            return ex.what();
        }
        catch( std::string&amp; msg ) {
            return msg;
        }
        catch( const char* msg ) {
            return msg;
        }
        catch(...) {
            return "Unknown exception";
        }
    }

    std::string ExceptionTranslatorRegistry::tryTranslators() const {
        if( m_translators.empty() )
            std::rethrow_exception(std::current_exception());
        else
            return m_translators[0]-&gt;translate( m_translators.begin()+1, m_translators.end() );
    }
}
// end catch_exception_translator_registry.cpp
// start catch_fatal_condition.cpp

// start catch_fatal_condition.h

#include &lt;string&gt;

#if defined ( CATCH_PLATFORM_WINDOWS ) /////////////////////////////////////////

#  if !defined ( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {
    struct FatalConditionHandler {
        void reset();
    };
}

#  else // CATCH_CONFIG_WINDOWS_SEH is defined

namespace Catch {

    struct FatalConditionHandler {

        static LONG CALLBACK handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo);
        FatalConditionHandler();
        static void reset();
        ~FatalConditionHandler();

    private:
        static bool isSet;
        static ULONG guaranteeSize;
        static PVOID exceptionHandlerHandle;
    };

} // namespace Catch

#  endif // CATCH_CONFIG_WINDOWS_SEH

#else // Not Windows - assumed to be POSIX compatible //////////////////////////

#  if !defined(CATCH_CONFIG_POSIX_SIGNALS)

namespace Catch {
    struct FatalConditionHandler {
        void reset();
    };
}

#  else // CATCH_CONFIG_POSIX_SIGNALS is defined

#include &lt;signal.h&gt;

namespace Catch {

    struct FatalConditionHandler {

        static bool isSet;
        static struct sigaction oldSigActions[];// [sizeof(signalDefs) / sizeof(SignalDefs)];
        static stack_t oldSigStack;
        static char altStackMem[];

        static void handleSignal( int sig );

        FatalConditionHandler();
        ~FatalConditionHandler();
        static void reset();
    };

} // namespace Catch

#  endif // CATCH_CONFIG_POSIX_SIGNALS

#endif // not Windows

// end catch_fatal_condition.h
namespace {
    // Report the error condition
    void reportFatal( char const * const message ) {
        Catch::getCurrentContext().getResultCapture()-&gt;handleFatalErrorCondition( message );
    }
}

#if defined ( CATCH_PLATFORM_WINDOWS ) /////////////////////////////////////////

#  if !defined ( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {
    void FatalConditionHandler::reset() {}
}

#  else // CATCH_CONFIG_WINDOWS_SEH is defined

namespace Catch {
    struct SignalDefs { DWORD id; const char* name; };

    // There is no 1-1 mapping between signals and windows exceptions.
    // Windows can easily distinguish between SO and SigSegV,
    // but SigInt, SigTerm, etc are handled differently.
    static SignalDefs signalDefs[] = {
        { EXCEPTION_ILLEGAL_INSTRUCTION,  "SIGILL - Illegal instruction signal" },
        { EXCEPTION_STACK_OVERFLOW, "SIGSEGV - Stack overflow" },
        { EXCEPTION_ACCESS_VIOLATION, "SIGSEGV - Segmentation violation signal" },
        { EXCEPTION_INT_DIVIDE_BY_ZERO, "Divide by zero error" },
    };

    LONG CALLBACK FatalConditionHandler::handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo) {
        for (auto const&amp; def : signalDefs) {
            if (ExceptionInfo-&gt;ExceptionRecord-&gt;ExceptionCode == def.id) {
                reportFatal(def.name);
            }
        }
        // If its not an exception we care about, pass it along.
        // This stops us from eating debugger breaks etc.
        return EXCEPTION_CONTINUE_SEARCH;
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        // 32k seems enough for Catch to handle stack overflow,
        // but the value was found experimentally, so there is no strong guarantee
        guaranteeSize = 32 * 1024;
        exceptionHandlerHandle = nullptr;
        // Register as first handler in current chain
        exceptionHandlerHandle = AddVectoredExceptionHandler(1, handleVectoredException);
        // Pass in guarantee size to be filled
        SetThreadStackGuarantee(&amp;guaranteeSize);
    }

    void FatalConditionHandler::reset() {
        if (isSet) {
            // Unregister handler and restore the old guarantee
            RemoveVectoredExceptionHandler(exceptionHandlerHandle);
            SetThreadStackGuarantee(&amp;guaranteeSize);
            exceptionHandlerHandle = nullptr;
            isSet = false;
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

bool FatalConditionHandler::isSet = false;
ULONG FatalConditionHandler::guaranteeSize = 0;
PVOID FatalConditionHandler::exceptionHandlerHandle = nullptr;

} // namespace Catch

#  endif // CATCH_CONFIG_WINDOWS_SEH

#else // Not Windows - assumed to be POSIX compatible //////////////////////////

#  if !defined(CATCH_CONFIG_POSIX_SIGNALS)

namespace Catch {
    void FatalConditionHandler::reset() {}
}

#  else // CATCH_CONFIG_POSIX_SIGNALS is defined

#include &lt;signal.h&gt;

namespace Catch {

    struct SignalDefs {
        int id;
        const char* name;
    };
    static SignalDefs signalDefs[] = {
        { SIGINT,  "SIGINT - Terminal interrupt signal" },
        { SIGILL,  "SIGILL - Illegal instruction signal" },
        { SIGFPE,  "SIGFPE - Floating point error signal" },
        { SIGSEGV, "SIGSEGV - Segmentation violation signal" },
        { SIGTERM, "SIGTERM - Termination request signal" },
        { SIGABRT, "SIGABRT - Abort (abnormal termination) signal" }
    };

    void FatalConditionHandler::handleSignal( int sig ) {
        char const * name = "&lt;unknown signal&gt;";
        for (auto const&amp; def : signalDefs) {
            if (sig == def.id) {
                name = def.name;
                break;
            }
        }
        reset();
        reportFatal(name);
        raise( sig );
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        stack_t sigStack;
        sigStack.ss_sp = altStackMem;
        sigStack.ss_size = SIGSTKSZ;
        sigStack.ss_flags = 0;
        sigaltstack(&amp;sigStack, &amp;oldSigStack);
        struct sigaction sa = { };

        sa.sa_handler = handleSignal;
        sa.sa_flags = SA_ONSTACK;
        for (std::size_t i = 0; i &lt; sizeof(signalDefs)/sizeof(SignalDefs); ++i) {
            sigaction(signalDefs[i].id, &amp;sa, &amp;oldSigActions[i]);
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

    void FatalConditionHandler::reset() {
        if( isSet ) {
            // Set signals back to previous values -- hopefully nobody overwrote them in the meantime
            for( std::size_t i = 0; i &lt; sizeof(signalDefs)/sizeof(SignalDefs); ++i ) {
                sigaction(signalDefs[i].id, &amp;oldSigActions[i], nullptr);
            }
            // Return the old stack
            sigaltstack(&amp;oldSigStack, nullptr);
            isSet = false;
        }
    }

    bool FatalConditionHandler::isSet = false;
    struct sigaction FatalConditionHandler::oldSigActions[sizeof(signalDefs)/sizeof(SignalDefs)] = {};
    stack_t FatalConditionHandler::oldSigStack = {};
    char FatalConditionHandler::altStackMem[SIGSTKSZ] = {};

} // namespace Catch

#  endif // CATCH_CONFIG_POSIX_SIGNALS

#endif // not Windows
// end catch_fatal_condition.cpp
// start catch_interfaces_capture.cpp

namespace Catch {
    IResultCapture::~IResultCapture() = default;
}
// end catch_interfaces_capture.cpp
// start catch_interfaces_config.cpp

namespace Catch {
    IConfig::~IConfig() = default;
}
// end catch_interfaces_config.cpp
// start catch_interfaces_exception.cpp

namespace Catch {
    IExceptionTranslator::~IExceptionTranslator() = default;
    IExceptionTranslatorRegistry::~IExceptionTranslatorRegistry() = default;
}
// end catch_interfaces_exception.cpp
// start catch_interfaces_registry_hub.cpp

namespace Catch {
    IRegistryHub::~IRegistryHub() = default;
    IMutableRegistryHub::~IMutableRegistryHub() = default;
}
// end catch_interfaces_registry_hub.cpp
// start catch_interfaces_reporter.cpp

// start catch_reporter_multi.h

namespace Catch {

    class MultipleReporters : public IStreamingReporter {
        using Reporters = std::vector&lt;IStreamingReporterPtr&gt;;
        Reporters m_reporters;

    public:
        void add( IStreamingReporterPtr&amp;&amp; reporter );

    public: // IStreamingReporter

        ReporterPreferences getPreferences() const override;

        void noMatchingTestCases( std::string const&amp; spec ) override;

        static std::set&lt;Verbosity&gt; getSupportedVerbosities();

        void benchmarkStarting( BenchmarkInfo const&amp; benchmarkInfo ) override;
        void benchmarkEnded( BenchmarkStats const&amp; benchmarkStats ) override;

        void testRunStarting( TestRunInfo const&amp; testRunInfo ) override;
        void testGroupStarting( GroupInfo const&amp; groupInfo ) override;
        void testCaseStarting( TestCaseInfo const&amp; testInfo ) override;
        void sectionStarting( SectionInfo const&amp; sectionInfo ) override;
        void assertionStarting( AssertionInfo const&amp; assertionInfo ) override;

        // The return value indicates if the messages buffer should be cleared:
        bool assertionEnded( AssertionStats const&amp; assertionStats ) override;
        void sectionEnded( SectionStats const&amp; sectionStats ) override;
        void testCaseEnded( TestCaseStats const&amp; testCaseStats ) override;
        void testGroupEnded( TestGroupStats const&amp; testGroupStats ) override;
        void testRunEnded( TestRunStats const&amp; testRunStats ) override;

        void skipTest( TestCaseInfo const&amp; testInfo ) override;
        bool isMulti() const override;

    };

} // end namespace Catch

// end catch_reporter_multi.h
namespace Catch {

    ReporterConfig::ReporterConfig( IConfigPtr const&amp; _fullConfig )
    :   m_stream( &amp;_fullConfig-&gt;stream() ), m_fullConfig( _fullConfig ) {}

    ReporterConfig::ReporterConfig( IConfigPtr const&amp; _fullConfig, std::ostream&amp; _stream )
    :   m_stream( &amp;_stream ), m_fullConfig( _fullConfig ) {}

    std::ostream&amp; ReporterConfig::stream() const { return *m_stream; }
    IConfigPtr ReporterConfig::fullConfig() const { return m_fullConfig; }

    TestRunInfo::TestRunInfo( std::string const&amp; _name ) : name( _name ) {}

    GroupInfo::GroupInfo(  std::string const&amp; _name,
                           std::size_t _groupIndex,
                           std::size_t _groupsCount )
    :   name( _name ),
        groupIndex( _groupIndex ),
        groupsCounts( _groupsCount )
    {}

     AssertionStats::AssertionStats( AssertionResult const&amp; _assertionResult,
                                     std::vector&lt;MessageInfo&gt; const&amp; _infoMessages,
                                     Totals const&amp; _totals )
    :   assertionResult( _assertionResult ),
        infoMessages( _infoMessages ),
        totals( _totals )
    {
        assertionResult.m_resultData.lazyExpression.m_transientExpression = _assertionResult.m_resultData.lazyExpression.m_transientExpression;

        if( assertionResult.hasMessage() ) {
            // Copy message into messages list.
            // !TBD This should have been done earlier, somewhere
            MessageBuilder builder( assertionResult.getTestMacroName(), assertionResult.getSourceInfo(), assertionResult.getResultType() );
            builder &lt;&lt; assertionResult.getMessage();
            builder.m_info.message = builder.m_stream.str();

            infoMessages.push_back( builder.m_info );
        }
    }

     AssertionStats::~AssertionStats() = default;

    SectionStats::SectionStats(  SectionInfo const&amp; _sectionInfo,
                                 Counts const&amp; _assertions,
                                 double _durationInSeconds,
                                 bool _missingAssertions )
    :   sectionInfo( _sectionInfo ),
        assertions( _assertions ),
        durationInSeconds( _durationInSeconds ),
        missingAssertions( _missingAssertions )
    {}

    SectionStats::~SectionStats() = default;

    TestCaseStats::TestCaseStats(  TestCaseInfo const&amp; _testInfo,
                                   Totals const&amp; _totals,
                                   std::string const&amp; _stdOut,
                                   std::string const&amp; _stdErr,
                                   bool _aborting )
    : testInfo( _testInfo ),
        totals( _totals ),
        stdOut( _stdOut ),
        stdErr( _stdErr ),
        aborting( _aborting )
    {}

    TestCaseStats::~TestCaseStats() = default;

    TestGroupStats::TestGroupStats( GroupInfo const&amp; _groupInfo,
                                    Totals const&amp; _totals,
                                    bool _aborting )
    :   groupInfo( _groupInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    TestGroupStats::TestGroupStats( GroupInfo const&amp; _groupInfo )
    :   groupInfo( _groupInfo ),
        aborting( false )
    {}

    TestGroupStats::~TestGroupStats() = default;

    TestRunStats::TestRunStats(   TestRunInfo const&amp; _runInfo,
                    Totals const&amp; _totals,
                    bool _aborting )
    :   runInfo( _runInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    TestRunStats::~TestRunStats() = default;

    void IStreamingReporter::fatalErrorEncountered( StringRef ) {}
    bool IStreamingReporter::isMulti() const { return false; }

    IReporterFactory::~IReporterFactory() = default;
    IReporterRegistry::~IReporterRegistry() = default;

    void addReporter( IStreamingReporterPtr&amp; existingReporter, IStreamingReporterPtr&amp;&amp; additionalReporter ) {

        if( !existingReporter ) {
            existingReporter = std::move( additionalReporter );
            return;
        }

        MultipleReporters* multi = nullptr;

        if( existingReporter-&gt;isMulti() ) {
            multi = static_cast&lt;MultipleReporters*&gt;( existingReporter.get() );
        }
        else {
            auto newMulti = std::unique_ptr&lt;MultipleReporters&gt;( new MultipleReporters );
            newMulti-&gt;add( std::move( existingReporter ) );
            multi = newMulti.get();
            existingReporter = std::move( newMulti );
        }
        multi-&gt;add( std::move( additionalReporter ) );
    }

} // end namespace Catch
// end catch_interfaces_reporter.cpp
// start catch_interfaces_runner.cpp

namespace Catch {
    IRunner::~IRunner() = default;
}
// end catch_interfaces_runner.cpp
// start catch_interfaces_testcase.cpp

namespace Catch {
    ITestInvoker::~ITestInvoker() = default;
    ITestCaseRegistry::~ITestCaseRegistry() = default;
}
// end catch_interfaces_testcase.cpp
// start catch_leak_detector.cpp

namespace Catch {

#ifdef CATCH_CONFIG_WINDOWS_CRTDBG
#include &lt;crtdbg.h&gt;

	LeakDetector::LeakDetector() {
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		flag |= _CRTDBG_ALLOC_MEM_DF;
		_CrtSetDbgFlag(flag);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
		// Change this to leaking allocation's number to break there
		_CrtSetBreakAlloc(-1);
	}

#else

    LeakDetector::LeakDetector(){}

#endif

}
// end catch_leak_detector.cpp
// start catch_list.cpp

// start catch_list.h

#include &lt;set&gt;

namespace Catch {

    std::size_t listTests( Config const&amp; config );

    std::size_t listTestsNamesOnly( Config const&amp; config );

    struct TagInfo {
        void add( std::string const&amp; spelling );
        std::string all() const;

        std::set&lt;std::string&gt; spellings;
        std::size_t count = 0;
    };

    std::size_t listTags( Config const&amp; config );

    std::size_t listReporters( Config const&amp; /*config*/ );

    Option&lt;std::size_t&gt; list( Config const&amp; config );

} // end namespace Catch

// end catch_list.h
// start catch_text.h

namespace Catch {
    using namespace clara::TextFlow;
}

// end catch_text.h
#include &lt;limits&gt;
#include &lt;algorithm&gt;
#include &lt;iomanip&gt;

namespace Catch {

    std::size_t listTests( Config const&amp; config ) {
        TestSpec testSpec = config.testSpec();
        if( config.testSpec().hasFilters() )
            Catch::cout() &lt;&lt; "Matching test cases:\n";
        else {
            Catch::cout() &lt;&lt; "All available test cases:\n";
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        }

        auto matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCaseInfo : matchedTestCases ) {
            Colour::Code colour = testCaseInfo.isHidden()
                ? Colour::SecondaryText
                : Colour::None;
            Colour colourGuard( colour );

            Catch::cout() &lt;&lt; Column( testCaseInfo.name ).initialIndent( 2 ).indent( 4 ) &lt;&lt; "\n";
            if( config.verbosity() &gt;= Verbosity::High ) {
                Catch::cout() &lt;&lt; Column( Catch::Detail::stringify( testCaseInfo.lineInfo ) ).indent(4) &lt;&lt; std::endl;
                std::string description = testCaseInfo.description;
                if( description.empty() )
                    description = "(NO DESCRIPTION)";
                Catch::cout() &lt;&lt; Column( description ).indent(4) &lt;&lt; std::endl;
            }
            if( !testCaseInfo.tags.empty() )
                Catch::cout() &lt;&lt; Column( testCaseInfo.tagsAsString() ).indent( 6 ) &lt;&lt; "\n";
        }

        if( !config.testSpec().hasFilters() )
            Catch::cout() &lt;&lt; pluralise( matchedTestCases.size(), "test case" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        else
            Catch::cout() &lt;&lt; pluralise( matchedTestCases.size(), "matching test case" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        return matchedTestCases.size();
    }

    std::size_t listTestsNamesOnly( Config const&amp; config ) {
        TestSpec testSpec = config.testSpec();
        if( !config.testSpec().hasFilters() )
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        std::size_t matchedTests = 0;
        std::vector&lt;TestCase&gt; matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCaseInfo : matchedTestCases ) {
            matchedTests++;
            if( startsWith( testCaseInfo.name, '#' ) )
               Catch::cout() &lt;&lt; '"' &lt;&lt; testCaseInfo.name &lt;&lt; '"';
            else
               Catch::cout() &lt;&lt; testCaseInfo.name;
            if ( config.verbosity() &gt;= Verbosity::High )
                Catch::cout() &lt;&lt; "\t@" &lt;&lt; testCaseInfo.lineInfo;
            Catch::cout() &lt;&lt; std::endl;
        }
        return matchedTests;
    }

    void TagInfo::add( std::string const&amp; spelling ) {
        ++count;
        spellings.insert( spelling );
    }

    std::string TagInfo::all() const {
        std::string out;
        for( auto const&amp; spelling : spellings )
            out += "[" + spelling + "]";
        return out;
    }

    std::size_t listTags( Config const&amp; config ) {
        TestSpec testSpec = config.testSpec();
        if( config.testSpec().hasFilters() )
            Catch::cout() &lt;&lt; "Tags for matching test cases:\n";
        else {
            Catch::cout() &lt;&lt; "All available tags:\n";
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        }

        std::map&lt;std::string, TagInfo&gt; tagCounts;

        std::vector&lt;TestCase&gt; matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCase : matchedTestCases ) {
            for( auto const&amp; tagName : testCase.getTestCaseInfo().tags ) {
                std::string lcaseTagName = toLower( tagName );
                auto countIt = tagCounts.find( lcaseTagName );
                if( countIt == tagCounts.end() )
                    countIt = tagCounts.insert( std::make_pair( lcaseTagName, TagInfo() ) ).first;
                countIt-&gt;second.add( tagName );
            }
        }

        for( auto const&amp; tagCount : tagCounts ) {
            std::ostringstream oss;
            oss &lt;&lt; "  " &lt;&lt; std::setw(2) &lt;&lt; tagCount.second.count &lt;&lt; "  ";
            auto wrapper = Column( tagCount.second.all() )
                                                    .initialIndent( 0 )
                                                    .indent( oss.str().size() )
                                                    .width( CATCH_CONFIG_CONSOLE_WIDTH-10 );
            Catch::cout() &lt;&lt; oss.str() &lt;&lt; wrapper &lt;&lt; '\n';
        }
        Catch::cout() &lt;&lt; pluralise( tagCounts.size(), "tag" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        return tagCounts.size();
    }

    std::size_t listReporters( Config const&amp; /*config*/ ) {
        Catch::cout() &lt;&lt; "Available reporters:\n";
        IReporterRegistry::FactoryMap const&amp; factories = getRegistryHub().getReporterRegistry().getFactories();
        std::size_t maxNameLen = 0;
        for( auto const&amp; factoryKvp : factories )
            maxNameLen = (std::max)( maxNameLen, factoryKvp.first.size() );

        for( auto const&amp; factoryKvp : factories ) {
            Catch::cout()
                    &lt;&lt; Column( factoryKvp.first + ":" )
                            .indent(2)
                            .width( 5+maxNameLen )
                    +  Column( factoryKvp.second-&gt;getDescription() )
                            .initialIndent(0)
                            .indent(2)
                            .width( CATCH_CONFIG_CONSOLE_WIDTH - maxNameLen-8 )
                    &lt;&lt; "\n";
        }
        Catch::cout() &lt;&lt; std::endl;
        return factories.size();
    }

    Option&lt;std::size_t&gt; list( Config const&amp; config ) {
        Option&lt;std::size_t&gt; listedCount;
        if( config.listTests() )
            listedCount = listedCount.valueOr(0) + listTests( config );
        if( config.listTestNamesOnly() )
            listedCount = listedCount.valueOr(0) + listTestsNamesOnly( config );
        if( config.listTags() )
            listedCount = listedCount.valueOr(0) + listTags( config );
        if( config.listReporters() )
            listedCount = listedCount.valueOr(0) + listReporters( config );
        return listedCount;
    }

} // end namespace Catch
// end catch_list.cpp
// start catch_matchers.cpp

namespace Catch {
namespace Matchers {
    namespace Impl {

        std::string MatcherUntypedBase::toString() const {
            if( m_cachedToString.empty() )
                m_cachedToString = describe();
            return m_cachedToString;
        }

        MatcherUntypedBase::~MatcherUntypedBase() = default;

    } // namespace Impl
} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch
// end catch_matchers.cpp
// start catch_matchers_string.cpp

namespace Catch {
namespace Matchers {

    namespace StdString {

        CasedString::CasedString( std::string const&amp; str, CaseSensitive::Choice caseSensitivity )
        :   m_caseSensitivity( caseSensitivity ),
            m_str( adjustString( str ) )
        {}
        std::string CasedString::adjustString( std::string const&amp; str ) const {
            return m_caseSensitivity == CaseSensitive::No
                   ? toLower( str )
                   : str;
        }
        std::string CasedString::caseSensitivitySuffix() const {
            return m_caseSensitivity == CaseSensitive::No
                   ? " (case insensitive)"
                   : std::string();
        }

        StringMatcherBase::StringMatcherBase( std::string const&amp; operation, CasedString const&amp; comparator )
        : m_comparator( comparator ),
          m_operation( operation ) {
        }

        std::string StringMatcherBase::describe() const {
            std::string description;
            description.reserve(5 + m_operation.size() + m_comparator.m_str.size() +
                                        m_comparator.caseSensitivitySuffix().size());
            description += m_operation;
            description += ": \"";
            description += m_comparator.m_str;
            description += "\"";
            description += m_comparator.caseSensitivitySuffix();
            return description;
        }

        EqualsMatcher::EqualsMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "equals", comparator ) {}

        bool EqualsMatcher::match( std::string const&amp; source ) const {
            return m_comparator.adjustString( source ) == m_comparator.m_str;
        }

        ContainsMatcher::ContainsMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "contains", comparator ) {}

        bool ContainsMatcher::match( std::string const&amp; source ) const {
            return contains( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        StartsWithMatcher::StartsWithMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "starts with", comparator ) {}

        bool StartsWithMatcher::match( std::string const&amp; source ) const {
            return startsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        EndsWithMatcher::EndsWithMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "ends with", comparator ) {}

        bool EndsWithMatcher::match( std::string const&amp; source ) const {
            return endsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

    } // namespace StdString

    StdString::EqualsMatcher Equals( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EqualsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::ContainsMatcher Contains( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::ContainsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::EndsWithMatcher EndsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EndsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::StartsWithMatcher StartsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::StartsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }

} // namespace Matchers
} // namespace Catch
// end catch_matchers_string.cpp
// start catch_message.cpp

namespace Catch {

    MessageInfo::MessageInfo(   std::string const&amp; _macroName,
                                SourceLineInfo const&amp; _lineInfo,
                                ResultWas::OfType _type )
    :   macroName( _macroName ),
        lineInfo( _lineInfo ),
        type( _type ),
        sequence( ++globalCount )
    {}

    bool MessageInfo::operator==( MessageInfo const&amp; other ) const {
        return sequence == other.sequence;
    }

    bool MessageInfo::operator&lt;( MessageInfo const&amp; other ) const {
        return sequence &lt; other.sequence;
    }

    // This may need protecting if threading support is added
    unsigned int MessageInfo::globalCount = 0;

    ////////////////////////////////////////////////////////////////////////////

    Catch::MessageBuilder::MessageBuilder( std::string const&amp; macroName,
                                           SourceLineInfo const&amp; lineInfo,
                                           ResultWas::OfType type )
        :m_info(macroName, lineInfo, type) {}

    ////////////////////////////////////////////////////////////////////////////

    ScopedMessage::ScopedMessage( MessageBuilder const&amp; builder )
    : m_info( builder.m_info )
    {
        m_info.message = builder.m_stream.str();
        getResultCapture().pushScopedMessage( m_info );
    }

    ScopedMessage::~ScopedMessage() {
        if ( !std::uncaught_exception() ){
            getResultCapture().popScopedMessage(m_info);
        }
    }

} // end namespace Catch
// end catch_message.cpp
// start catch_random_number_generator.cpp

// start catch_random_number_generator.h

#include &lt;algorithm&gt;

namespace Catch {

    struct IConfig;

    void seedRng( IConfig const&amp; config );

    unsigned int rngSeed();

    struct RandomNumberGenerator {
        using result_type = unsigned int;

        static constexpr result_type (min)() { return 0; }
        static constexpr result_type (max)() { return 1000000; }

        result_type operator()( result_type n ) const;
        result_type operator()() const;

        template&lt;typename V&gt;
        static void shuffle( V&amp; vector ) {
            RandomNumberGenerator rng;
            std::shuffle( vector.begin(), vector.end(), rng );
        }
    };

}

// end catch_random_number_generator.h
#include &lt;cstdlib&gt;

namespace Catch {

    void seedRng( IConfig const&amp; config ) {
        if( config.rngSeed() != 0 )
            std::srand( config.rngSeed() );
    }
    unsigned int rngSeed() {
        return getCurrentContext().getConfig()-&gt;rngSeed();
    }

    RandomNumberGenerator::result_type RandomNumberGenerator::operator()( result_type n ) const {
        return std::rand() % n;
    }
    RandomNumberGenerator::result_type RandomNumberGenerator::operator()() const {
        return std::rand() % (max)();
    }

}
// end catch_random_number_generator.cpp
// start catch_registry_hub.cpp

// start catch_test_case_registry_impl.h

#include &lt;vector&gt;
#include &lt;set&gt;
#include &lt;algorithm&gt;
#include &lt;ios&gt;

namespace Catch {

    class TestCase;
    struct IConfig;

    std::vector&lt;TestCase&gt; sortTests( IConfig const&amp; config, std::vector&lt;TestCase&gt; const&amp; unsortedTestCases );
    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config );

    void enforceNoDuplicateTestCases( std::vector&lt;TestCase&gt; const&amp; functions );

    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config );

    class TestRegistry : public ITestCaseRegistry {
    public:
        virtual ~TestRegistry() = default;

        virtual void registerTest( TestCase const&amp; testCase );

        std::vector&lt;TestCase&gt; const&amp; getAllTests() const override;
        std::vector&lt;TestCase&gt; const&amp; getAllTestsSorted( IConfig const&amp; config ) const override;

    private:
        std::vector&lt;TestCase&gt; m_functions;
        mutable RunTests::InWhatOrder m_currentSortOrder = RunTests::InDeclarationOrder;
        mutable std::vector&lt;TestCase&gt; m_sortedFunctions;
        std::size_t m_unnamedCount = 0;
        std::ios_base::Init m_ostreamInit; // Forces cout/ cerr to be initialised
    };

    ///////////////////////////////////////////////////////////////////////////

    class TestInvokerAsFunction : public ITestInvoker {
        void(*m_testAsFunction)();
    public:
        TestInvokerAsFunction( void(*testAsFunction)() ) noexcept;

        void invoke() const override;
    };

    std::string extractClassName( std::string const&amp; classOrQualifiedMethodName );

    ///////////////////////////////////////////////////////////////////////////

} // end namespace Catch

// end catch_test_case_registry_impl.h
// start catch_reporter_registry.h

#include &lt;map&gt;

namespace Catch {

    class ReporterRegistry : public IReporterRegistry {

    public:

        ~ReporterRegistry() override;

        IStreamingReporterPtr create( std::string const&amp; name, IConfigPtr const&amp; config ) const override;

        void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory );
        void registerListener( IReporterFactoryPtr const&amp; factory );

        FactoryMap const&amp; getFactories() const override;
        Listeners const&amp; getListeners() const override;

    private:
        FactoryMap m_factories;
        Listeners m_listeners;
    };
}

// end catch_reporter_registry.h
// start catch_tag_alias_registry.h

// start catch_tag_alias.h

#include &lt;string&gt;

namespace Catch {

    struct TagAlias {
        TagAlias(std::string const&amp; _tag, SourceLineInfo _lineInfo);

        std::string tag;
        SourceLineInfo lineInfo;
    };

} // end namespace Catch

// end catch_tag_alias.h
#include &lt;map&gt;

namespace Catch {

    class TagAliasRegistry : public ITagAliasRegistry {
    public:
        ~TagAliasRegistry() override;
        TagAlias const* find( std::string const&amp; alias ) const override;
        std::string expandAliases( std::string const&amp; unexpandedTestSpec ) const override;
        void add( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo );

    private:
        std::map&lt;std::string, TagAlias&gt; m_registry;
    };

} // end namespace Catch

// end catch_tag_alias_registry.h
// start catch_startup_exception_registry.h

#include &lt;vector&gt;
#include &lt;exception&gt;

namespace Catch {

    class StartupExceptionRegistry {
    public:
        void add(std::exception_ptr const&amp; exception) noexcept;
        std::vector&lt;std::exception_ptr&gt; const&amp; getExceptions() const noexcept;
    private:
        std::vector&lt;std::exception_ptr&gt; m_exceptions;
    };

} // end namespace Catch

// end catch_startup_exception_registry.h
namespace Catch {

    namespace {

        class RegistryHub : public IRegistryHub, public IMutableRegistryHub,
                            private NonCopyable {

        public: // IRegistryHub
            RegistryHub() = default;
            IReporterRegistry const&amp; getReporterRegistry() const override {
                return m_reporterRegistry;
            }
            ITestCaseRegistry const&amp; getTestCaseRegistry() const override {
                return m_testCaseRegistry;
            }
            IExceptionTranslatorRegistry&amp; getExceptionTranslatorRegistry() override {
                return m_exceptionTranslatorRegistry;
            }
            ITagAliasRegistry const&amp; getTagAliasRegistry() const override {
                return m_tagAliasRegistry;
            }
            StartupExceptionRegistry const&amp; getStartupExceptionRegistry() const override {
                return m_exceptionRegistry;
            }

        public: // IMutableRegistryHub
            void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) override {
                m_reporterRegistry.registerReporter( name, factory );
            }
            void registerListener( IReporterFactoryPtr const&amp; factory ) override {
                m_reporterRegistry.registerListener( factory );
            }
            void registerTest( TestCase const&amp; testInfo ) override {
                m_testCaseRegistry.registerTest( testInfo );
            }
            void registerTranslator( const IExceptionTranslator* translator ) override {
                m_exceptionTranslatorRegistry.registerTranslator( translator );
            }
            void registerTagAlias( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) override {
                m_tagAliasRegistry.add( alias, tag, lineInfo );
            }
            void registerStartupException() noexcept override {
                m_exceptionRegistry.add(std::current_exception());
            }

        private:
            TestRegistry m_testCaseRegistry;
            ReporterRegistry m_reporterRegistry;
            ExceptionTranslatorRegistry m_exceptionTranslatorRegistry;
            TagAliasRegistry m_tagAliasRegistry;
            StartupExceptionRegistry m_exceptionRegistry;
        };

        // Single, global, instance
        RegistryHub*&amp; getTheRegistryHub() {
            static RegistryHub* theRegistryHub = nullptr;
            if( !theRegistryHub )
                theRegistryHub = new RegistryHub();
            return theRegistryHub;
        }
    }

    IRegistryHub&amp; getRegistryHub() {
        return *getTheRegistryHub();
    }
    IMutableRegistryHub&amp; getMutableRegistryHub() {
        return *getTheRegistryHub();
    }
    void cleanUp() {
        delete getTheRegistryHub();
        getTheRegistryHub() = nullptr;
        cleanUpContext();
    }
    std::string translateActiveException() {
        return getRegistryHub().getExceptionTranslatorRegistry().translateActiveException();
    }

} // end namespace Catch
// end catch_registry_hub.cpp
// start catch_reporter_registry.cpp

namespace Catch {

    ReporterRegistry::~ReporterRegistry() = default;

    IStreamingReporterPtr ReporterRegistry::create( std::string const&amp; name, IConfigPtr const&amp; config ) const {
        auto it =  m_factories.find( name );
        if( it == m_factories.end() )
            return nullptr;
        return it-&gt;second-&gt;create( ReporterConfig( config ) );
    }

    void ReporterRegistry::registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) {
        m_factories.emplace(name, factory);
    }
    void ReporterRegistry::registerListener( IReporterFactoryPtr const&amp; factory ) {
        m_listeners.push_back( factory );
    }

    IReporterRegistry::FactoryMap const&amp; ReporterRegistry::getFactories() const {
        return m_factories;
    }
    IReporterRegistry::Listeners const&amp; ReporterRegistry::getListeners() const {
        return m_listeners;
    }

}
// end catch_reporter_registry.cpp
// start catch_result_type.cpp

namespace Catch {

    bool isOk( ResultWas::OfType resultType ) {
        return ( resultType &amp; ResultWas::FailureBit ) == 0;
    }
    bool isJustInfo( int flags ) {
        return flags == ResultWas::Info;
    }

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs ) {
        return static_cast&lt;ResultDisposition::Flags&gt;( static_cast&lt;int&gt;( lhs ) | static_cast&lt;int&gt;( rhs ) );
    }

    bool shouldContinueOnFailure( int flags )    { return ( flags &amp; ResultDisposition::ContinueOnFailure ) != 0; }
    bool isFalseTest( int flags )                { return ( flags &amp; ResultDisposition::FalseTest ) != 0; }
    bool shouldSuppressFailure( int flags )      { return ( flags &amp; ResultDisposition::SuppressFail ) != 0; }

} // end namespace Catch
// end catch_result_type.cpp
// start catch_run_context.cpp
// start catch_run_context.h

#include &lt;string&gt;

namespace Catch {

    struct IMutableContext;

    class StreamRedirect {

    public:
        StreamRedirect(std::ostream&amp; stream, std::string&amp; targetString);

        ~StreamRedirect();

    private:
        std::ostream&amp; m_stream;
        std::streambuf* m_prevBuf;
        std::ostringstream m_oss;
        std::string&amp; m_targetString;
    };

    // StdErr has two constituent streams in C++, std::cerr and std::clog
    // This means that we need to redirect 2 streams into 1 to keep proper
    // order of writes and cannot use StreamRedirect on its own
    class StdErrRedirect {
    public:
        StdErrRedirect(std::string&amp; targetString);
        ~StdErrRedirect();
    private:
        std::streambuf* m_cerrBuf;
        std::streambuf* m_clogBuf;
        std::ostringstream m_oss;
        std::string&amp; m_targetString;
    };

    ///////////////////////////////////////////////////////////////////////////

    class RunContext : public IResultCapture, public IRunner {

    public:
        RunContext( RunContext const&amp; ) = delete;
        RunContext&amp; operator =( RunContext const&amp; ) = delete;

        explicit RunContext(IConfigPtr const&amp; _config, IStreamingReporterPtr&amp;&amp; reporter);

        virtual ~RunContext();

        void testGroupStarting(std::string const&amp; testSpec, std::size_t groupIndex, std::size_t groupsCount);
        void testGroupEnded(std::string const&amp; testSpec, Totals const&amp; totals, std::size_t groupIndex, std::size_t groupsCount);

        Totals runTest(TestCase const&amp; testCase);

        IConfigPtr config() const;
        IStreamingReporter&amp; reporter() const;

    private: // IResultCapture

        void assertionStarting(AssertionInfo const&amp; info) override;
        void assertionEnded(AssertionResult const&amp; result) override;

        bool sectionStarted( SectionInfo const&amp; sectionInfo, Counts&amp; assertions ) override;
        bool testForMissingAssertions(Counts&amp; assertions);

        void sectionEnded(SectionEndInfo const&amp; endInfo) override;
        void sectionEndedEarly(SectionEndInfo const&amp; endInfo) override;

        void benchmarkStarting( BenchmarkInfo const&amp; info ) override;
        void benchmarkEnded( BenchmarkStats const&amp; stats ) override;

        void pushScopedMessage(MessageInfo const&amp; message) override;
        void popScopedMessage(MessageInfo const&amp; message) override;

        std::string getCurrentTestName() const override;

        const AssertionResult* getLastResult() const override;

        void exceptionEarlyReported() override;

        void handleFatalErrorCondition( StringRef message ) override;

        bool lastAssertionPassed() override;

        void assertionPassed() override;

        void assertionRun() override;

    public:
        // !TBD We need to do this another way!
        bool aborting() const override;

    private:

        void runCurrentTest(std::string&amp; redirectedCout, std::string&amp; redirectedCerr);
        void invokeActiveTestCase();

    private:

        void handleUnfinishedSections();

        TestRunInfo m_runInfo;
        IMutableContext&amp; m_context;
        TestCase const* m_activeTestCase = nullptr;
        ITracker* m_testCaseTracker;
        Option&lt;AssertionResult&gt; m_lastResult;

        IConfigPtr m_config;
        Totals m_totals;
        IStreamingReporterPtr m_reporter;
        std::vector&lt;MessageInfo&gt; m_messages;
        AssertionInfo m_lastAssertionInfo;
        std::vector&lt;SectionEndInfo&gt; m_unfinishedSections;
        std::vector&lt;ITracker*&gt; m_activeSections;
        TrackerContext m_trackerContext;
        std::size_t m_prevPassed = 0;
        bool m_shouldReportUnexpected = true;
    };

    IResultCapture&amp; getResultCapture();

} // end namespace Catch

// end catch_run_context.h

#include &lt;cassert&gt;
#include &lt;algorithm&gt;

namespace Catch {

    StreamRedirect::StreamRedirect(std::ostream&amp; stream, std::string&amp; targetString)
        : m_stream(stream),
        m_prevBuf(stream.rdbuf()),
        m_targetString(targetString) {
        stream.rdbuf(m_oss.rdbuf());
    }

    StreamRedirect::~StreamRedirect() {
        m_targetString += m_oss.str();
        m_stream.rdbuf(m_prevBuf);
    }

    StdErrRedirect::StdErrRedirect(std::string &amp; targetString)
        :m_cerrBuf(cerr().rdbuf()), m_clogBuf(clog().rdbuf()),
        m_targetString(targetString) {
        cerr().rdbuf(m_oss.rdbuf());
        clog().rdbuf(m_oss.rdbuf());
    }

    StdErrRedirect::~StdErrRedirect() {
        m_targetString += m_oss.str();
        cerr().rdbuf(m_cerrBuf);
        clog().rdbuf(m_clogBuf);
    }

    RunContext::RunContext(IConfigPtr const&amp; _config, IStreamingReporterPtr&amp;&amp; reporter)
    :   m_runInfo(_config-&gt;name()),
        m_context(getCurrentMutableContext()),
        m_config(_config),
        m_reporter(std::move(reporter)),
        m_lastAssertionInfo{ "", SourceLineInfo("",0), "", ResultDisposition::Normal }
    {
        m_context.setRunner(this);
        m_context.setConfig(m_config);
        m_context.setResultCapture(this);
        m_reporter-&gt;testRunStarting(m_runInfo);
    }

    RunContext::~RunContext() {
        m_reporter-&gt;testRunEnded(TestRunStats(m_runInfo, m_totals, aborting()));
    }

    void RunContext::testGroupStarting(std::string const&amp; testSpec, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter-&gt;testGroupStarting(GroupInfo(testSpec, groupIndex, groupsCount));
    }

    void RunContext::testGroupEnded(std::string const&amp; testSpec, Totals const&amp; totals, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter-&gt;testGroupEnded(TestGroupStats(GroupInfo(testSpec, groupIndex, groupsCount), totals, aborting()));
    }

    Totals RunContext::runTest(TestCase const&amp; testCase) {
        Totals prevTotals = m_totals;

        std::string redirectedCout;
        std::string redirectedCerr;

        TestCaseInfo testInfo = testCase.getTestCaseInfo();

        m_reporter-&gt;testCaseStarting(testInfo);

        m_activeTestCase = &amp;testCase;

        ITracker&amp; rootTracker = m_trackerContext.startRun();
        assert(rootTracker.isSectionTracker());
        static_cast&lt;SectionTracker&amp;&gt;(rootTracker).addInitialFilters(m_config-&gt;getSectionsToRun());
        do {
            m_trackerContext.startCycle();
            m_testCaseTracker = &amp;SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(testInfo.name, testInfo.lineInfo));
            runCurrentTest(redirectedCout, redirectedCerr);
        } while (!m_testCaseTracker-&gt;isSuccessfullyCompleted() &amp;&amp; !aborting());

        Totals deltaTotals = m_totals.delta(prevTotals);
        if (testInfo.expectedToFail() &amp;&amp; deltaTotals.testCases.passed &gt; 0) {
            deltaTotals.assertions.failed++;
            deltaTotals.testCases.passed--;
            deltaTotals.testCases.failed++;
        }
        m_totals.testCases += deltaTotals.testCases;
        m_reporter-&gt;testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  redirectedCout,
                                  redirectedCerr,
                                  aborting()));

        m_activeTestCase = nullptr;
        m_testCaseTracker = nullptr;

        return deltaTotals;
    }

    IConfigPtr RunContext::config() const {
        return m_config;
    }

    IStreamingReporter&amp; RunContext::reporter() const {
        return *m_reporter;
    }

    void RunContext::assertionStarting(AssertionInfo const&amp; info) {
        m_reporter-&gt;assertionStarting( info );
    }
    void RunContext::assertionEnded(AssertionResult const &amp; result) {
        if (result.getResultType() == ResultWas::Ok) {
            m_totals.assertions.passed++;
        } else if (!result.isOk()) {
            if( m_activeTestCase-&gt;getTestCaseInfo().okToFail() )
                m_totals.assertions.failedButOk++;
            else
                m_totals.assertions.failed++;
        }

        // We have no use for the return value (whether messages should be cleared), because messages were made scoped
        // and should be let to clear themselves out.
        static_cast&lt;void&gt;(m_reporter-&gt;assertionEnded(AssertionStats(result, m_messages, m_totals)));

        // Reset working state
        m_lastAssertionInfo = { "", m_lastAssertionInfo.lineInfo, "{Unknown expression after the reported line}", m_lastAssertionInfo.resultDisposition };
        m_lastResult = result;
    }

    bool RunContext::sectionStarted(SectionInfo const &amp; sectionInfo, Counts &amp; assertions) {
        ITracker&amp; sectionTracker = SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(sectionInfo.name, sectionInfo.lineInfo));
        if (!sectionTracker.isOpen())
            return false;
        m_activeSections.push_back(&amp;sectionTracker);

        m_lastAssertionInfo.lineInfo = sectionInfo.lineInfo;

        m_reporter-&gt;sectionStarting(sectionInfo);

        assertions = m_totals.assertions;

        return true;
    }

    bool RunContext::testForMissingAssertions(Counts&amp; assertions) {
        if (assertions.total() != 0)
            return false;
        if (!m_config-&gt;warnAboutMissingAssertions())
            return false;
        if (m_trackerContext.currentTracker().hasChildren())
            return false;
        m_totals.assertions.failed++;
        assertions.failed++;
        return true;
    }

    void RunContext::sectionEnded(SectionEndInfo const &amp; endInfo) {
        Counts assertions = m_totals.assertions - endInfo.prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);

        if (!m_activeSections.empty()) {
            m_activeSections.back()-&gt;close();
            m_activeSections.pop_back();
        }

        m_reporter-&gt;sectionEnded(SectionStats(endInfo.sectionInfo, assertions, endInfo.durationInSeconds, missingAssertions));
        m_messages.clear();
    }

    void RunContext::sectionEndedEarly(SectionEndInfo const &amp; endInfo) {
        if (m_unfinishedSections.empty())
            m_activeSections.back()-&gt;fail();
        else
            m_activeSections.back()-&gt;close();
        m_activeSections.pop_back();

        m_unfinishedSections.push_back(endInfo);
    }
    void RunContext::benchmarkStarting( BenchmarkInfo const&amp; info ) {
        m_reporter-&gt;benchmarkStarting( info );
    }
    void RunContext::benchmarkEnded( BenchmarkStats const&amp; stats ) {
        m_reporter-&gt;benchmarkEnded( stats );
    }

    void RunContext::pushScopedMessage(MessageInfo const &amp; message) {
        m_messages.push_back(message);
    }

    void RunContext::popScopedMessage(MessageInfo const &amp; message) {
        m_messages.erase(std::remove(m_messages.begin(), m_messages.end(), message), m_messages.end());
    }

    std::string RunContext::getCurrentTestName() const {
        return m_activeTestCase
            ? m_activeTestCase-&gt;getTestCaseInfo().name
            : std::string();
    }

    const AssertionResult * RunContext::getLastResult() const {
        return &amp;(*m_lastResult);
    }

    void RunContext::exceptionEarlyReported() {
        m_shouldReportUnexpected = false;
    }

    void RunContext::handleFatalErrorCondition( StringRef message ) {
        // First notify reporter that bad things happened
        m_reporter-&gt;fatalErrorEncountered(message);

        // Don't rebuild the result -- the stringification itself can cause more fatal errors
        // Instead, fake a result data.
        AssertionResultData tempResult( ResultWas::FatalErrorCondition, { false } );
        tempResult.message = message;
        AssertionResult result(m_lastAssertionInfo, tempResult);

        getResultCapture().assertionEnded(result);

        handleUnfinishedSections();

        // Recreate section for test case (as we will lose the one that was in scope)
        auto const&amp; testCaseInfo = m_activeTestCase-&gt;getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name, testCaseInfo.description);

        Counts assertions;
        assertions.failed = 1;
        SectionStats testCaseSectionStats(testCaseSection, assertions, 0, false);
        m_reporter-&gt;sectionEnded(testCaseSectionStats);

        auto const&amp; testInfo = m_activeTestCase-&gt;getTestCaseInfo();

        Totals deltaTotals;
        deltaTotals.testCases.failed = 1;
        deltaTotals.assertions.failed = 1;
        m_reporter-&gt;testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  std::string(),
                                  std::string(),
                                  false));
        m_totals.testCases.failed++;
        testGroupEnded(std::string(), m_totals, 1, 1);
        m_reporter-&gt;testRunEnded(TestRunStats(m_runInfo, m_totals, false));
    }

    bool RunContext::lastAssertionPassed() {
         return m_totals.assertions.passed == (m_prevPassed + 1);
    }

    void RunContext::assertionPassed() {
        ++m_totals.assertions.passed;
        m_lastAssertionInfo.capturedExpression = "{Unknown expression after the reported line}";
        m_lastAssertionInfo.macroName = "";
    }

    void RunContext::assertionRun() {
        m_prevPassed = m_totals.assertions.passed;
    }

    bool RunContext::aborting() const {
        return m_totals.assertions.failed == static_cast&lt;std::size_t&gt;(m_config-&gt;abortAfter());
    }

    void RunContext::runCurrentTest(std::string &amp; redirectedCout, std::string &amp; redirectedCerr) {
        auto const&amp; testCaseInfo = m_activeTestCase-&gt;getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name, testCaseInfo.description);
        m_reporter-&gt;sectionStarting(testCaseSection);
        Counts prevAssertions = m_totals.assertions;
        double duration = 0;
        m_shouldReportUnexpected = true;
        try {
            m_lastAssertionInfo = { "TEST_CASE", testCaseInfo.lineInfo, "", ResultDisposition::Normal };

            seedRng(*m_config);

            Timer timer;
            timer.start();
            if (m_reporter-&gt;getPreferences().shouldRedirectStdOut) {
                StreamRedirect coutRedir(cout(), redirectedCout);
                StdErrRedirect errRedir(redirectedCerr);
                invokeActiveTestCase();
            } else {
                invokeActiveTestCase();
            }
            duration = timer.getElapsedSeconds();
        } catch (TestFailureException&amp;) {
            // This just means the test was aborted due to failure
        } catch (...) {
            // Under CATCH_CONFIG_FAST_COMPILE, unexpected exceptions under REQUIRE assertions
            // are reported without translation at the point of origin.
            if (m_shouldReportUnexpected) {
                AssertionHandler
                    ( m_lastAssertionInfo.macroName,
                      m_lastAssertionInfo.lineInfo,
                      m_lastAssertionInfo.capturedExpression,
                      m_lastAssertionInfo.resultDisposition ).useActiveException();
            }
        }
        m_testCaseTracker-&gt;close();
        handleUnfinishedSections();
        m_messages.clear();

        Counts assertions = m_totals.assertions - prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);
        SectionStats testCaseSectionStats(testCaseSection, assertions, duration, missingAssertions);
        m_reporter-&gt;sectionEnded(testCaseSectionStats);
    }

    void RunContext::invokeActiveTestCase() {
        FatalConditionHandler fatalConditionHandler; // Handle signals
        m_activeTestCase-&gt;invoke();
        fatalConditionHandler.reset();
    }

    void RunContext::handleUnfinishedSections() {
        // If sections ended prematurely due to an exception we stored their
        // infos here so we can tear them down outside the unwind process.
        for (auto it = m_unfinishedSections.rbegin(),
             itEnd = m_unfinishedSections.rend();
             it != itEnd;
             ++it)
            sectionEnded(*it);
        m_unfinishedSections.clear();
    }

    IResultCapture&amp; getResultCapture() {
        if (auto* capture = getCurrentContext().getResultCapture())
            return *capture;
        else
            CATCH_INTERNAL_ERROR("No result capture instance");
    }
}
// end catch_run_context.cpp
// start catch_section.cpp

namespace Catch {

    Section::Section( SectionInfo const&amp; info )
    :   m_info( info ),
        m_sectionIncluded( getResultCapture().sectionStarted( m_info, m_assertions ) )
    {
        m_timer.start();
    }

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996) // std::uncaught_exception is deprecated in C++17
#endif
    Section::~Section() {
        if( m_sectionIncluded ) {
            SectionEndInfo endInfo( m_info, m_assertions, m_timer.getElapsedSeconds() );
            if( std::uncaught_exception() )
                getResultCapture().sectionEndedEarly( endInfo );
            else
                getResultCapture().sectionEnded( endInfo );
        }
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    // This indicates whether the section should be executed or not
    Section::operator bool() const {
        return m_sectionIncluded;
    }

} // end namespace Catch
// end catch_section.cpp
// start catch_section_info.cpp

namespace Catch {

    SectionInfo::SectionInfo
        (   SourceLineInfo const&amp; _lineInfo,
            std::string const&amp; _name,
            std::string const&amp; _description )
    :   name( _name ),
        description( _description ),
        lineInfo( _lineInfo )
    {}

    SectionEndInfo::SectionEndInfo( SectionInfo const&amp; _sectionInfo, Counts const&amp; _prevAssertions, double _durationInSeconds )
    : sectionInfo( _sectionInfo ), prevAssertions( _prevAssertions ), durationInSeconds( _durationInSeconds )
    {}

} // end namespace Catch
// end catch_section_info.cpp
// start catch_session.cpp

// start catch_session.h

#include &lt;memory&gt;

namespace Catch {

    class Session : NonCopyable {
    public:

        Session();
        ~Session() override;

        void showHelp() const;
        void libIdentify();

        int applyCommandLine( int argc, char* argv[] );

        void useConfigData( ConfigData const&amp; configData );

        int run( int argc, char* argv[] );
    #if defined(WIN32) &amp;&amp; defined(UNICODE)
        int run( int argc, wchar_t* const argv[] );
    #endif
        int run();

        clara::Parser const&amp; cli() const;
        void cli( clara::Parser const&amp; newParser );
        ConfigData&amp; configData();
        Config&amp; config();
    private:
        int runInternal();

        clara::Parser m_cli;
        ConfigData m_configData;
        std::shared_ptr&lt;Config&gt; m_config;
        bool m_startupExceptions = false;
    };

} // end namespace Catch

// end catch_session.h
// start catch_version.h

#include &lt;iosfwd&gt;

namespace Catch {

    // Versioning information
    struct Version {
        Version( Version const&amp; ) = delete;
        Version&amp; operator=( Version const&amp; ) = delete;
        Version(    unsigned int _majorVersion,
                    unsigned int _minorVersion,
                    unsigned int _patchNumber,
                    char const * const _branchName,
                    unsigned int _buildNumber );

        unsigned int const majorVersion;
        unsigned int const minorVersion;
        unsigned int const patchNumber;

        // buildNumber is only used if branchName is not null
        char const * const branchName;
        unsigned int const buildNumber;

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Version const&amp; version );
    };

    Version const&amp; libraryVersion();
}

// end catch_version.h
#include &lt;cstdlib&gt;
#include &lt;iomanip&gt;

namespace {
    const int MaxExitCode = 255;
    using Catch::IStreamingReporterPtr;
    using Catch::IConfigPtr;
    using Catch::Config;

    IStreamingReporterPtr createReporter(std::string const&amp; reporterName, IConfigPtr const&amp; config) {
        auto reporter = Catch::getRegistryHub().getReporterRegistry().create(reporterName, config);
        CATCH_ENFORCE(reporter, "No reporter registered with name: '" &lt;&lt; reporterName &lt;&lt; "'");

        return reporter;
    }

#ifndef CATCH_CONFIG_DEFAULT_REPORTER
#define CATCH_CONFIG_DEFAULT_REPORTER "console"
#endif

    IStreamingReporterPtr makeReporter(std::shared_ptr&lt;Config&gt; const&amp; config) {
        auto const&amp; reporterNames = config-&gt;getReporterNames();
        if (reporterNames.empty())
            return createReporter(CATCH_CONFIG_DEFAULT_REPORTER, config);

        IStreamingReporterPtr reporter;
        for (auto const&amp; name : reporterNames)
            addReporter(reporter, createReporter(name, config));
        return reporter;
    }

#undef CATCH_CONFIG_DEFAULT_REPORTER

    void addListeners(IStreamingReporterPtr&amp; reporters, IConfigPtr const&amp; config) {
        auto const&amp; listeners = Catch::getRegistryHub().getReporterRegistry().getListeners();
        for (auto const&amp; listener : listeners)
            addReporter(reporters, listener-&gt;create(Catch::ReporterConfig(config)));
    }

    Catch::Totals runTests(std::shared_ptr&lt;Config&gt; const&amp; config) {
        using namespace Catch;
        IStreamingReporterPtr reporter = makeReporter(config);
        addListeners(reporter, config);

        RunContext context(config, std::move(reporter));

        Totals totals;

        context.testGroupStarting(config-&gt;name(), 1, 1);

        TestSpec testSpec = config-&gt;testSpec();
        if (!testSpec.hasFilters())
            testSpec = TestSpecParser(ITagAliasRegistry::get()).parse("~[.]").testSpec(); // All not hidden tests

        auto const&amp; allTestCases = getAllTestCasesSorted(*config);
        for (auto const&amp; testCase : allTestCases) {
            if (!context.aborting() &amp;&amp; matchTest(testCase, testSpec, *config))
                totals += context.runTest(testCase);
            else
                context.reporter().skipTest(testCase);
        }

        context.testGroupEnded(config-&gt;name(), totals, 1, 1);
        return totals;
    }

    void applyFilenamesAsTags(Catch::IConfig const&amp; config) {
        using namespace Catch;
        auto&amp; tests = const_cast&lt;std::vector&lt;TestCase&gt;&amp;&gt;(getAllTestCasesSorted(config));
        for (auto&amp; testCase : tests) {
            auto tags = testCase.tags;

            std::string filename = testCase.lineInfo.file;
            auto lastSlash = filename.find_last_of("\\/");
            if (lastSlash != std::string::npos) {
                filename.erase(0, lastSlash);
                filename[0] = '#';
            }

            auto lastDot = filename.find_last_of('.');
            if (lastDot != std::string::npos) {
                filename.erase(lastDot);
            }

            tags.push_back(std::move(filename));
            setTags(testCase, tags);
        }
    }

}

namespace Catch {

    Session::Session() {
        static bool alreadyInstantiated = false;
        if( alreadyInstantiated ) {
            try         { CATCH_INTERNAL_ERROR( "Only one instance of Catch::Session can ever be used" ); }
            catch(...)  { getMutableRegistryHub().registerStartupException(); }
        }

        const auto&amp; exceptions = getRegistryHub().getStartupExceptionRegistry().getExceptions();
        if ( !exceptions.empty() ) {
            m_startupExceptions = true;
            Colour colourGuard( Colour::Red );
            Catch::cerr() &lt;&lt; "Errors occured during startup!" &lt;&lt; '\n';
            // iterate over all exceptions and notify user
            for ( const auto&amp; ex_ptr : exceptions ) {
                try {
                    std::rethrow_exception(ex_ptr);
                } catch ( std::exception const&amp; ex ) {
                    Catch::cerr() &lt;&lt; Column( ex.what() ).indent(2) &lt;&lt; '\n';
                }
            }
        }

        alreadyInstantiated = true;
        m_cli = makeCommandLineParser( m_configData );
    }
    Session::~Session() {
        Catch::cleanUp();
    }

    void Session::showHelp() const {
        Catch::cout()
                &lt;&lt; "\nCatch v" &lt;&lt; libraryVersion() &lt;&lt; "\n"
                &lt;&lt; m_cli &lt;&lt; std::endl
                &lt;&lt; "For more detailed usage please see the project docs\n" &lt;&lt; std::endl;
    }
    void Session::libIdentify() {
        Catch::cout()
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "description: " &lt;&lt; "A Catch test executable\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "category: " &lt;&lt; "testframework\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "framework: " &lt;&lt; "Catch Test\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "version: " &lt;&lt; libraryVersion() &lt;&lt; std::endl;
    }

    int Session::applyCommandLine( int argc, char* argv[] ) {
        if( m_startupExceptions )
            return 1;

        auto result = m_cli.parse( clara::Args( argc, argv ) );
        if( !result ) {
            Catch::cerr()
                &lt;&lt; Colour( Colour::Red )
                &lt;&lt; "\nError(s) in input:\n"
                &lt;&lt; Column( result.errorMessage() ).indent( 2 )
                &lt;&lt; "\n\n";
            Catch::cerr() &lt;&lt; "Run with -? for usage\n" &lt;&lt; std::endl;
            return MaxExitCode;
        }

        if( m_configData.showHelp )
            showHelp();
        if( m_configData.libIdentify )
            libIdentify();
        m_config.reset();
        return 0;
    }

    void Session::useConfigData( ConfigData const&amp; configData ) {
        m_configData = configData;
        m_config.reset();
    }

    int Session::run( int argc, char* argv[] ) {
        if( m_startupExceptions )
            return 1;
        int returnCode = applyCommandLine( argc, argv );
        if( returnCode == 0 )
            returnCode = run();
        return returnCode;
    }

#if defined(WIN32) &amp;&amp; defined(UNICODE)
    int Session::run( int argc, wchar_t* const argv[] ) {

        char **utf8Argv = new char *[ argc ];

        for ( int i = 0; i &lt; argc; ++i ) {
            int bufSize = WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL );

            utf8Argv[ i ] = new char[ bufSize ];

            WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, utf8Argv[i], bufSize, NULL, NULL );
        }

        int returnCode = run( argc, utf8Argv );

        for ( int i = 0; i &lt; argc; ++i )
            delete [] utf8Argv[ i ];

        delete [] utf8Argv;

        return returnCode;
    }
#endif
    int Session::run() {
        if( ( m_configData.waitForKeypress &amp; WaitForKeypress::BeforeStart ) != 0 ) {
            Catch::cout() &lt;&lt; "...waiting for enter/ return before starting" &lt;&lt; std::endl;
            static_cast&lt;void&gt;(std::getchar());
        }
        int exitCode = runInternal();
        if( ( m_configData.waitForKeypress &amp; WaitForKeypress::BeforeExit ) != 0 ) {
            Catch::cout() &lt;&lt; "...waiting for enter/ return before exiting, with code: " &lt;&lt; exitCode &lt;&lt; std::endl;
            static_cast&lt;void&gt;(std::getchar());
        }
        return exitCode;
    }

    clara::Parser const&amp; Session::cli() const {
        return m_cli;
    }
    void Session::cli( clara::Parser const&amp; newParser ) {
        m_cli = newParser;
    }
    ConfigData&amp; Session::configData() {
        return m_configData;
    }
    Config&amp; Session::config() {
        if( !m_config )
            m_config = std::make_shared&lt;Config&gt;( m_configData );
        return *m_config;
    }

    int Session::runInternal() {
        if( m_startupExceptions )
            return 1;

        if( m_configData.showHelp || m_configData.libIdentify )
            return 0;

        try
        {
            config(); // Force config to be constructed

            seedRng( *m_config );

            if( m_configData.filenamesAsTags )
                applyFilenamesAsTags( *m_config );

            // Handle list request
            if( Option&lt;std::size_t&gt; listed = list( config() ) )
                return static_cast&lt;int&gt;( *listed );

            return (std::min)( MaxExitCode, static_cast&lt;int&gt;( runTests( m_config ).assertions.failed ) );
        }
        catch( std::exception&amp; ex ) {
            Catch::cerr() &lt;&lt; ex.what() &lt;&lt; std::endl;
            return MaxExitCode;
        }
    }

} // end namespace Catch
// end catch_session.cpp
// start catch_startup_exception_registry.cpp

namespace Catch {
    void StartupExceptionRegistry::add( std::exception_ptr const&amp; exception ) noexcept {
        try {
            m_exceptions.push_back(exception);
        }
        catch(...) {
            // If we run out of memory during start-up there's really not a lot more we can do about it
            std::terminate();
        }
    }

    std::vector&lt;std::exception_ptr&gt; const&amp; StartupExceptionRegistry::getExceptions() const noexcept {
        return m_exceptions;
    }

} // end namespace Catch
// end catch_startup_exception_registry.cpp
// start catch_stream.cpp

#include &lt;stdexcept&gt;
#include &lt;cstdio&gt;
#include &lt;iostream&gt;

namespace Catch {

    template&lt;typename WriterF, std::size_t bufferSize=256&gt;
    class StreamBufImpl : public StreamBufBase {
        char data[bufferSize];
        WriterF m_writer;

    public:
        StreamBufImpl() {
            setp( data, data + sizeof(data) );
        }

        ~StreamBufImpl() noexcept {
            StreamBufImpl::sync();
        }

    private:
        int overflow( int c ) override {
            sync();

            if( c != EOF ) {
                if( pbase() == epptr() )
                    m_writer( std::string( 1, static_cast&lt;char&gt;( c ) ) );
                else
                    sputc( static_cast&lt;char&gt;( c ) );
            }
            return 0;
        }

        int sync() override {
            if( pbase() != pptr() ) {
                m_writer( std::string( pbase(), static_cast&lt;std::string::size_type&gt;( pptr() - pbase() ) ) );
                setp( pbase(), epptr() );
            }
            return 0;
        }
    };

    ///////////////////////////////////////////////////////////////////////////

    Catch::IStream::~IStream() = default;

    FileStream::FileStream( std::string const&amp; filename ) {
        m_ofs.open( filename.c_str() );
        CATCH_ENFORCE( !m_ofs.fail(), "Unable to open file: '" &lt;&lt; filename &lt;&lt; "'" );
    }

    std::ostream&amp; FileStream::stream() const {
        return m_ofs;
    }

    struct OutputDebugWriter {

        void operator()( std::string const&amp;str ) {
            writeToDebugConsole( str );
        }
    };

    DebugOutStream::DebugOutStream()
    :   m_streamBuf( new StreamBufImpl&lt;OutputDebugWriter&gt;() ),
        m_os( m_streamBuf.get() )
    {}

    std::ostream&amp; DebugOutStream::stream() const {
        return m_os;
    }

    // Store the streambuf from cout up-front because
    // cout may get redirected when running tests
    CoutStream::CoutStream()
    :   m_os( Catch::cout().rdbuf() )
    {}

    std::ostream&amp; CoutStream::stream() const {
        return m_os;
    }

#ifndef CATCH_CONFIG_NOSTDOUT // If you #define this you must implement these functions
    std::ostream&amp; cout() {
        return std::cout;
    }
    std::ostream&amp; cerr() {
        return std::cerr;
    }
    std::ostream&amp; clog() {
        return std::clog;
    }
#endif
}
// end catch_stream.cpp
// start catch_streambuf.cpp

namespace Catch {
    StreamBufBase::~StreamBufBase() = default;
}
// end catch_streambuf.cpp
// start catch_string_manip.cpp

#include &lt;algorithm&gt;
#include &lt;ostream&gt;
#include &lt;cstring&gt;
#include &lt;cctype&gt;

namespace Catch {

    bool startsWith( std::string const&amp; s, std::string const&amp; prefix ) {
        return s.size() &gt;= prefix.size() &amp;&amp; std::equal(prefix.begin(), prefix.end(), s.begin());
    }
    bool startsWith( std::string const&amp; s, char prefix ) {
        return !s.empty() &amp;&amp; s[0] == prefix;
    }
    bool endsWith( std::string const&amp; s, std::string const&amp; suffix ) {
        return s.size() &gt;= suffix.size() &amp;&amp; std::equal(suffix.rbegin(), suffix.rend(), s.rbegin());
    }
    bool endsWith( std::string const&amp; s, char suffix ) {
        return !s.empty() &amp;&amp; s[s.size()-1] == suffix;
    }
    bool contains( std::string const&amp; s, std::string const&amp; infix ) {
        return s.find( infix ) != std::string::npos;
    }
    char toLowerCh(char c) {
        return static_cast&lt;char&gt;( std::tolower( c ) );
    }
    void toLowerInPlace( std::string&amp; s ) {
        std::transform( s.begin(), s.end(), s.begin(), toLowerCh );
    }
    std::string toLower( std::string const&amp; s ) {
        std::string lc = s;
        toLowerInPlace( lc );
        return lc;
    }
    std::string trim( std::string const&amp; str ) {
        static char const* whitespaceChars = "\n\r\t ";
        std::string::size_type start = str.find_first_not_of( whitespaceChars );
        std::string::size_type end = str.find_last_not_of( whitespaceChars );

        return start != std::string::npos ? str.substr( start, 1+end-start ) : std::string();
    }

    bool replaceInPlace( std::string&amp; str, std::string const&amp; replaceThis, std::string const&amp; withThis ) {
        bool replaced = false;
        std::size_t i = str.find( replaceThis );
        while( i != std::string::npos ) {
            replaced = true;
            str = str.substr( 0, i ) + withThis + str.substr( i+replaceThis.size() );
            if( i &lt; str.size()-withThis.size() )
                i = str.find( replaceThis, i+withThis.size() );
            else
                i = std::string::npos;
        }
        return replaced;
    }

    pluralise::pluralise( std::size_t count, std::string const&amp; label )
    :   m_count( count ),
        m_label( label )
    {}

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, pluralise const&amp; pluraliser ) {
        os &lt;&lt; pluraliser.m_count &lt;&lt; ' ' &lt;&lt; pluraliser.m_label;
        if( pluraliser.m_count != 1 )
            os &lt;&lt; 's';
        return os;
    }

}
// end catch_string_manip.cpp
// start catch_stringref.cpp

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

#include &lt;ostream&gt;
#include &lt;cassert&gt;
#include &lt;cstring&gt;

namespace Catch {

    auto getEmptyStringRef() -&gt; StringRef {
        static StringRef s_emptyStringRef("");
        return s_emptyStringRef;
    }

    StringRef::StringRef() noexcept
    :   StringRef( getEmptyStringRef() )
    {}

    StringRef::StringRef( StringRef const&amp; other ) noexcept
    :   m_start( other.m_start ),
        m_size( other.m_size )
    {}

    StringRef::StringRef( StringRef&amp;&amp; other ) noexcept
    :   m_start( other.m_start ),
        m_size( other.m_size ),
        m_data( other.m_data )
    {
        other.m_data = nullptr;
    }

    StringRef::StringRef( char const* rawChars ) noexcept
    :   m_start( rawChars ),
        m_size( static_cast&lt;size_type&gt;( std::strlen( rawChars ) ) )
    {
        assert( rawChars != nullptr );
    }

    StringRef::StringRef( char const* rawChars, size_type size ) noexcept
    :   m_start( rawChars ),
        m_size( size )
    {
        size_type rawSize = rawChars == nullptr ? 0 : static_cast&lt;size_type&gt;( std::strlen( rawChars ) );
        if( rawSize &lt; size )
            m_size = rawSize;
    }

    StringRef::StringRef( std::string const&amp; stdString ) noexcept
    :   m_start( stdString.c_str() ),
        m_size( stdString.size() )
    {}

    StringRef::~StringRef() noexcept {
        delete[] m_data;
    }

    auto StringRef::operator = ( StringRef other ) noexcept -&gt; StringRef&amp; {
        swap( other );
        return *this;
    }
    StringRef::operator std::string() const {
        return std::string( m_start, m_size );
    }

    void StringRef::swap( StringRef&amp; other ) noexcept {
        std::swap( m_start, other.m_start );
        std::swap( m_size, other.m_size );
        std::swap( m_data, other.m_data );
    }

    auto StringRef::c_str() const -&gt; char const* {
        if( isSubstring() )
           const_cast&lt;StringRef*&gt;( this )-&gt;takeOwnership();
        return m_start;
    }
    auto StringRef::data() const noexcept -&gt; char const* {
        return m_start;
    }

    auto StringRef::isOwned() const noexcept -&gt; bool {
        return m_data != nullptr;
    }
    auto StringRef::isSubstring() const noexcept -&gt; bool {
        return m_start[m_size] != '\0';
    }

    void StringRef::takeOwnership() {
        if( !isOwned() ) {
            m_data = new char[m_size+1];
            memcpy( m_data, m_start, m_size );
            m_data[m_size] = '\0';
            m_start = m_data;
        }
    }
    auto StringRef::substr( size_type start, size_type size ) const noexcept -&gt; StringRef {
        if( start &lt; m_size )
            return StringRef( m_start+start, size );
        else
            return StringRef();
    }
    auto StringRef::operator == ( StringRef const&amp; other ) const noexcept -&gt; bool {
        return
            size() == other.size() &amp;&amp;
            (std::strncmp( m_start, other.m_start, size() ) == 0);
    }
    auto StringRef::operator != ( StringRef const&amp; other ) const noexcept -&gt; bool {
        return !operator==( other );
    }

    auto StringRef::operator[](size_type index) const noexcept -&gt; char {
        return m_start[index];
    }

    auto StringRef::empty() const noexcept -&gt; bool {
        return m_size == 0;
    }

    auto StringRef::size() const noexcept -&gt; size_type {
        return m_size;
    }
    auto StringRef::numberOfCharacters() const noexcept -&gt; size_type {
        size_type noChars = m_size;
        // Make adjustments for uft encodings
        for( size_type i=0; i &lt; m_size; ++i ) {
            char c = m_start[i];
            if( ( c &amp; 0b11000000 ) == 0b11000000 ) {
                if( ( c &amp; 0b11100000 ) == 0b11000000 )
                    noChars--;
                else if( ( c &amp; 0b11110000 ) == 0b11100000 )
                    noChars-=2;
                else if( ( c &amp; 0b11111000 ) == 0b11110000 )
                    noChars-=3;
            }
        }
        return noChars;
    }

    auto operator + ( StringRef const&amp; lhs, StringRef const&amp; rhs ) -&gt; std::string {
        std::string str;
        str.reserve( lhs.size() + rhs.size() );
        str += lhs;
        str += rhs;
        return str;
    }
    auto operator + ( StringRef const&amp; lhs, const char* rhs ) -&gt; std::string {
        return std::string( lhs ) + std::string( rhs );
    }
    auto operator + ( char const* lhs, StringRef const&amp; rhs ) -&gt; std::string {
        return std::string( lhs ) + std::string( rhs );
    }

    auto operator &lt;&lt; ( std::ostream&amp; os, StringRef const&amp; str ) -&gt; std::ostream&amp; {
        return os &lt;&lt; str.c_str();
    }

} // namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif
// end catch_stringref.cpp
// start catch_tag_alias.cpp

namespace Catch {
    TagAlias::TagAlias(std::string const &amp; _tag, SourceLineInfo _lineInfo): tag(_tag), lineInfo(_lineInfo) {}
}
// end catch_tag_alias.cpp
// start catch_tag_alias_autoregistrar.cpp

namespace Catch {

    RegistrarForTagAliases::RegistrarForTagAliases(char const* alias, char const* tag, SourceLineInfo const&amp; lineInfo) {
        try {
            getMutableRegistryHub().registerTagAlias(alias, tag, lineInfo);
        } catch (...) {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }

}
// end catch_tag_alias_autoregistrar.cpp
// start catch_tag_alias_registry.cpp

namespace Catch {

    TagAliasRegistry::~TagAliasRegistry() {}

    TagAlias const* TagAliasRegistry::find( std::string const&amp; alias ) const {
        auto it = m_registry.find( alias );
        if( it != m_registry.end() )
            return &amp;(it-&gt;second);
        else
            return nullptr;
    }

    std::string TagAliasRegistry::expandAliases( std::string const&amp; unexpandedTestSpec ) const {
        std::string expandedTestSpec = unexpandedTestSpec;
        for( auto const&amp; registryKvp : m_registry ) {
            std::size_t pos = expandedTestSpec.find( registryKvp.first );
            if( pos != std::string::npos ) {
                expandedTestSpec =  expandedTestSpec.substr( 0, pos ) +
                                    registryKvp.second.tag +
                                    expandedTestSpec.substr( pos + registryKvp.first.size() );
            }
        }
        return expandedTestSpec;
    }

    void TagAliasRegistry::add( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) {
        CATCH_ENFORCE( startsWith(alias, "[@") &amp;&amp; endsWith(alias, ']'),
                      "error: tag alias, '" &lt;&lt; alias &lt;&lt; "' is not of the form [@alias name].\n" &lt;&lt; lineInfo );

        CATCH_ENFORCE( m_registry.insert(std::make_pair(alias, TagAlias(tag, lineInfo))).second,
                      "error: tag alias, '" &lt;&lt; alias &lt;&lt; "' already registered.\n"
                      &lt;&lt; "\tFirst seen at: " &lt;&lt; find(alias)-&gt;lineInfo &lt;&lt; "\n"
                      &lt;&lt; "\tRedefined at: " &lt;&lt; lineInfo );
    }

    ITagAliasRegistry::~ITagAliasRegistry() {}

    ITagAliasRegistry const&amp; ITagAliasRegistry::get() {
        return getRegistryHub().getTagAliasRegistry();
    }

} // end namespace Catch
// end catch_tag_alias_registry.cpp
// start catch_test_case_info.cpp

#include &lt;cctype&gt;
#include &lt;exception&gt;
#include &lt;algorithm&gt;

namespace Catch {

    TestCaseInfo::SpecialProperties parseSpecialTag( std::string const&amp; tag ) {
        if( startsWith( tag, '.' ) ||
            tag == "!hide" )
            return TestCaseInfo::IsHidden;
        else if( tag == "!throws" )
            return TestCaseInfo::Throws;
        else if( tag == "!shouldfail" )
            return TestCaseInfo::ShouldFail;
        else if( tag == "!mayfail" )
            return TestCaseInfo::MayFail;
        else if( tag == "!nonportable" )
            return TestCaseInfo::NonPortable;
        else if( tag == "!benchmark" )
            return static_cast&lt;TestCaseInfo::SpecialProperties&gt;( TestCaseInfo::Benchmark | TestCaseInfo::IsHidden );
        else
            return TestCaseInfo::None;
    }
    bool isReservedTag( std::string const&amp; tag ) {
        return parseSpecialTag( tag ) == TestCaseInfo::None &amp;&amp; tag.size() &gt; 0 &amp;&amp; !std::isalnum( tag[0] );
    }
    void enforceNotReservedTag( std::string const&amp; tag, SourceLineInfo const&amp; _lineInfo ) {
        CATCH_ENFORCE( !isReservedTag(tag),
                      "Tag name: [" &lt;&lt; tag &lt;&lt; "] is not allowed.\n"
                      &lt;&lt; "Tag names starting with non alpha-numeric characters are reserved\n"
                      &lt;&lt; _lineInfo );
    }

    TestCase makeTestCase(  ITestInvoker* _testCase,
                            std::string const&amp; _className,
                            std::string const&amp; _name,
                            std::string const&amp; _descOrTags,
                            SourceLineInfo const&amp; _lineInfo )
    {
        bool isHidden = false;

        // Parse out tags
        std::vector&lt;std::string&gt; tags;
        std::string desc, tag;
        bool inTag = false;
        for (char c : _descOrTags) {
            if( !inTag ) {
                if( c == '[' )
                    inTag = true;
                else
                    desc += c;
            }
            else {
                if( c == ']' ) {
                    TestCaseInfo::SpecialProperties prop = parseSpecialTag( tag );
                    if( ( prop &amp; TestCaseInfo::IsHidden ) != 0 )
                        isHidden = true;
                    else if( prop == TestCaseInfo::None )
                        enforceNotReservedTag( tag, _lineInfo );

                    tags.push_back( tag );
                    tag.clear();
                    inTag = false;
                }
                else
                    tag += c;
            }
        }
        if( isHidden ) {
            tags.push_back( "." );
        }

        TestCaseInfo info( _name, _className, desc, tags, _lineInfo );
        return TestCase( _testCase, info );
    }

    void setTags( TestCaseInfo&amp; testCaseInfo, std::vector&lt;std::string&gt; tags ) {
        std::sort(begin(tags), end(tags));
        tags.erase(std::unique(begin(tags), end(tags)), end(tags));
        testCaseInfo.lcaseTags.clear();

        for( auto const&amp; tag : tags ) {
            std::string lcaseTag = toLower( tag );
            testCaseInfo.properties = static_cast&lt;TestCaseInfo::SpecialProperties&gt;( testCaseInfo.properties | parseSpecialTag( lcaseTag ) );
            testCaseInfo.lcaseTags.push_back( lcaseTag );
        }
        testCaseInfo.tags = std::move(tags);
    }

    TestCaseInfo::TestCaseInfo( std::string const&amp; _name,
                                std::string const&amp; _className,
                                std::string const&amp; _description,
                                std::vector&lt;std::string&gt; const&amp; _tags,
                                SourceLineInfo const&amp; _lineInfo )
    :   name( _name ),
        className( _className ),
        description( _description ),
        lineInfo( _lineInfo ),
        properties( None )
    {
        setTags( *this, _tags );
    }

    bool TestCaseInfo::isHidden() const {
        return ( properties &amp; IsHidden ) != 0;
    }
    bool TestCaseInfo::throws() const {
        return ( properties &amp; Throws ) != 0;
    }
    bool TestCaseInfo::okToFail() const {
        return ( properties &amp; (ShouldFail | MayFail ) ) != 0;
    }
    bool TestCaseInfo::expectedToFail() const {
        return ( properties &amp; (ShouldFail ) ) != 0;
    }

    std::string TestCaseInfo::tagsAsString() const {
        std::string ret;
        // '[' and ']' per tag
        std::size_t full_size = 2 * tags.size();
        for (const auto&amp; tag : tags) {
            full_size += tag.size();
        }
        ret.reserve(full_size);
        for (const auto&amp; tag : tags) {
            ret.push_back('[');
            ret.append(tag);
            ret.push_back(']');
        }

        return ret;
    }

    TestCase::TestCase( ITestInvoker* testCase, TestCaseInfo const&amp; info ) : TestCaseInfo( info ), test( testCase ) {}

    TestCase TestCase::withName( std::string const&amp; _newName ) const {
        TestCase other( *this );
        other.name = _newName;
        return other;
    }

    void TestCase::invoke() const {
        test-&gt;invoke();
    }

    bool TestCase::operator == ( TestCase const&amp; other ) const {
        return  test.get() == other.test.get() &amp;&amp;
                name == other.name &amp;&amp;
                className == other.className;
    }

    bool TestCase::operator &lt; ( TestCase const&amp; other ) const {
        return name &lt; other.name;
    }

    TestCaseInfo const&amp; TestCase::getTestCaseInfo() const
    {
        return *this;
    }

} // end namespace Catch
// end catch_test_case_info.cpp
// start catch_test_case_registry_impl.cpp

#include &lt;sstream&gt;

namespace Catch {

    std::vector&lt;TestCase&gt; sortTests( IConfig const&amp; config, std::vector&lt;TestCase&gt; const&amp; unsortedTestCases ) {

        std::vector&lt;TestCase&gt; sorted = unsortedTestCases;

        switch( config.runOrder() ) {
            case RunTests::InLexicographicalOrder:
                std::sort( sorted.begin(), sorted.end() );
                break;
            case RunTests::InRandomOrder:
                seedRng( config );
                RandomNumberGenerator::shuffle( sorted );
                break;
            case RunTests::InDeclarationOrder:
                // already in declaration order
                break;
        }
        return sorted;
    }
    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config ) {
        return testSpec.matches( testCase ) &amp;&amp; ( config.allowThrows() || !testCase.throws() );
    }

    void enforceNoDuplicateTestCases( std::vector&lt;TestCase&gt; const&amp; functions ) {
        std::set&lt;TestCase&gt; seenFunctions;
        for( auto const&amp; function : functions ) {
            auto prev = seenFunctions.insert( function );
            CATCH_ENFORCE( prev.second,
                    "error: TEST_CASE( \"" &lt;&lt; function.name &lt;&lt; "\" ) already defined.\n"
                    &lt;&lt; "\tFirst seen at " &lt;&lt; prev.first-&gt;getTestCaseInfo().lineInfo &lt;&lt; "\n"
                    &lt;&lt; "\tRedefined at " &lt;&lt; function.getTestCaseInfo().lineInfo );
        }
    }

    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config ) {
        std::vector&lt;TestCase&gt; filtered;
        filtered.reserve( testCases.size() );
        for( auto const&amp; testCase : testCases )
            if( matchTest( testCase, testSpec, config ) )
                filtered.push_back( testCase );
        return filtered;
    }
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config ) {
        return getRegistryHub().getTestCaseRegistry().getAllTestsSorted( config );
    }

    void TestRegistry::registerTest( TestCase const&amp; testCase ) {
        std::string name = testCase.getTestCaseInfo().name;
        if( name.empty() ) {
            std::ostringstream oss;
            oss &lt;&lt; "Anonymous test case " &lt;&lt; ++m_unnamedCount;
            return registerTest( testCase.withName( oss.str() ) );
        }
        m_functions.push_back( testCase );
    }

    std::vector&lt;TestCase&gt; const&amp; TestRegistry::getAllTests() const {
        return m_functions;
    }
    std::vector&lt;TestCase&gt; const&amp; TestRegistry::getAllTestsSorted( IConfig const&amp; config ) const {
        if( m_sortedFunctions.empty() )
            enforceNoDuplicateTestCases( m_functions );

        if(  m_currentSortOrder != config.runOrder() || m_sortedFunctions.empty() ) {
            m_sortedFunctions = sortTests( config, m_functions );
            m_currentSortOrder = config.runOrder();
        }
        return m_sortedFunctions;
    }

    ///////////////////////////////////////////////////////////////////////////
    TestInvokerAsFunction::TestInvokerAsFunction( void(*testAsFunction)() ) noexcept : m_testAsFunction( testAsFunction ) {}

    void TestInvokerAsFunction::invoke() const {
        m_testAsFunction();
    }

    std::string extractClassName( std::string const&amp; classOrQualifiedMethodName ) {
        std::string className = classOrQualifiedMethodName;
        if( startsWith( className, '&amp;' ) )
        {
            std::size_t lastColons = className.rfind( "::" );
            std::size_t penultimateColons = className.rfind( "::", lastColons-1 );
            if( penultimateColons == std::string::npos )
                penultimateColons = 1;
            className = className.substr( penultimateColons, lastColons-penultimateColons );
        }
        return className;
    }

} // end namespace Catch
// end catch_test_case_registry_impl.cpp
// start catch_test_case_tracker.cpp

#include &lt;algorithm&gt;
#include &lt;assert.h&gt;
#include &lt;stdexcept&gt;
#include &lt;memory&gt;

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace Catch {
namespace TestCaseTracking {

    NameAndLocation::NameAndLocation( std::string const&amp; _name, SourceLineInfo const&amp; _location )
    :   name( _name ),
        location( _location )
    {}

    ITracker::~ITracker() = default;

    TrackerContext&amp; TrackerContext::instance() {
        static TrackerContext s_instance;
        return s_instance;
    }

    ITracker&amp; TrackerContext::startRun() {
        m_rootTracker = std::make_shared&lt;SectionTracker&gt;( NameAndLocation( "{root}", CATCH_INTERNAL_LINEINFO ), *this, nullptr );
        m_currentTracker = nullptr;
        m_runState = Executing;
        return *m_rootTracker;
    }

    void TrackerContext::endRun() {
        m_rootTracker.reset();
        m_currentTracker = nullptr;
        m_runState = NotStarted;
    }

    void TrackerContext::startCycle() {
        m_currentTracker = m_rootTracker.get();
        m_runState = Executing;
    }
    void TrackerContext::completeCycle() {
        m_runState = CompletedCycle;
    }

    bool TrackerContext::completedCycle() const {
        return m_runState == CompletedCycle;
    }
    ITracker&amp; TrackerContext::currentTracker() {
        return *m_currentTracker;
    }
    void TrackerContext::setCurrentTracker( ITracker* tracker ) {
        m_currentTracker = tracker;
    }

    TrackerBase::TrackerHasName::TrackerHasName( NameAndLocation const&amp; nameAndLocation ) : m_nameAndLocation( nameAndLocation ) {}
    bool TrackerBase::TrackerHasName::operator ()( ITrackerPtr const&amp; tracker ) const {
        return
            tracker-&gt;nameAndLocation().name == m_nameAndLocation.name &amp;&amp;
            tracker-&gt;nameAndLocation().location == m_nameAndLocation.location;
    }

    TrackerBase::TrackerBase( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent )
    :   m_nameAndLocation( nameAndLocation ),
        m_ctx( ctx ),
        m_parent( parent )
    {}

    NameAndLocation const&amp; TrackerBase::nameAndLocation() const {
        return m_nameAndLocation;
    }
    bool TrackerBase::isComplete() const {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }
    bool TrackerBase::isSuccessfullyCompleted() const {
        return m_runState == CompletedSuccessfully;
    }
    bool TrackerBase::isOpen() const {
        return m_runState != NotStarted &amp;&amp; !isComplete();
    }
    bool TrackerBase::hasChildren() const {
        return !m_children.empty();
    }

    void TrackerBase::addChild( ITrackerPtr const&amp; child ) {
        m_children.push_back( child );
    }

    ITrackerPtr TrackerBase::findChild( NameAndLocation const&amp; nameAndLocation ) {
        auto it = std::find_if( m_children.begin(), m_children.end(), TrackerHasName( nameAndLocation ) );
        return( it != m_children.end() )
            ? *it
            : nullptr;
    }
    ITracker&amp; TrackerBase::parent() {
        assert( m_parent ); // Should always be non-null except for root
        return *m_parent;
    }

    void TrackerBase::openChild() {
        if( m_runState != ExecutingChildren ) {
            m_runState = ExecutingChildren;
            if( m_parent )
                m_parent-&gt;openChild();
        }
    }

    bool TrackerBase::isSectionTracker() const { return false; }
    bool TrackerBase::isIndexTracker() const { return false; }

    void TrackerBase::open() {
        m_runState = Executing;
        moveToThis();
        if( m_parent )
            m_parent-&gt;openChild();
    }

    void TrackerBase::close() {

        // Close any still open children (e.g. generators)
        while( &amp;m_ctx.currentTracker() != this )
            m_ctx.currentTracker().close();

        switch( m_runState ) {
            case NeedsAnotherRun:
                break;

            case Executing:
                m_runState = CompletedSuccessfully;
                break;
            case ExecutingChildren:
                if( m_children.empty() || m_children.back()-&gt;isComplete() )
                    m_runState = CompletedSuccessfully;
                break;

            case NotStarted:
            case CompletedSuccessfully:
            case Failed:
                CATCH_INTERNAL_ERROR( "Illogical state: " &lt;&lt; m_runState );

            default:
                CATCH_INTERNAL_ERROR( "Unknown state: " &lt;&lt; m_runState );
        }
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::fail() {
        m_runState = Failed;
        if( m_parent )
            m_parent-&gt;markAsNeedingAnotherRun();
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::markAsNeedingAnotherRun() {
        m_runState = NeedsAnotherRun;
    }

    void TrackerBase::moveToParent() {
        assert( m_parent );
        m_ctx.setCurrentTracker( m_parent );
    }
    void TrackerBase::moveToThis() {
        m_ctx.setCurrentTracker( this );
    }

    SectionTracker::SectionTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent )
    :   TrackerBase( nameAndLocation, ctx, parent )
    {
        if( parent ) {
            while( !parent-&gt;isSectionTracker() )
                parent = &amp;parent-&gt;parent();

            SectionTracker&amp; parentSection = static_cast&lt;SectionTracker&amp;&gt;( *parent );
            addNextFilters( parentSection.m_filters );
        }
    }

    bool SectionTracker::isSectionTracker() const { return true; }

    SectionTracker&amp; SectionTracker::acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation ) {
        std::shared_ptr&lt;SectionTracker&gt; section;

        ITracker&amp; currentTracker = ctx.currentTracker();
        if( ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
            assert( childTracker );
            assert( childTracker-&gt;isSectionTracker() );
            section = std::static_pointer_cast&lt;SectionTracker&gt;( childTracker );
        }
        else {
            section = std::make_shared&lt;SectionTracker&gt;( nameAndLocation, ctx, &amp;currentTracker );
            currentTracker.addChild( section );
        }
        if( !ctx.completedCycle() )
            section-&gt;tryOpen();
        return *section;
    }

    void SectionTracker::tryOpen() {
        if( !isComplete() &amp;&amp; (m_filters.empty() || m_filters[0].empty() ||  m_filters[0] == m_nameAndLocation.name ) )
            open();
    }

    void SectionTracker::addInitialFilters( std::vector&lt;std::string&gt; const&amp; filters ) {
        if( !filters.empty() ) {
            m_filters.push_back(""); // Root - should never be consulted
            m_filters.push_back(""); // Test Case - not a section filter
            m_filters.insert( m_filters.end(), filters.begin(), filters.end() );
        }
    }
    void SectionTracker::addNextFilters( std::vector&lt;std::string&gt; const&amp; filters ) {
        if( filters.size() &gt; 1 )
            m_filters.insert( m_filters.end(), ++filters.begin(), filters.end() );
    }

    IndexTracker::IndexTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent, int size )
    :   TrackerBase( nameAndLocation, ctx, parent ),
        m_size( size )
    {}

    bool IndexTracker::isIndexTracker() const { return true; }

    IndexTracker&amp; IndexTracker::acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation, int size ) {
        std::shared_ptr&lt;IndexTracker&gt; tracker;

        ITracker&amp; currentTracker = ctx.currentTracker();
        if( ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
            assert( childTracker );
            assert( childTracker-&gt;isIndexTracker() );
            tracker = std::static_pointer_cast&lt;IndexTracker&gt;( childTracker );
        }
        else {
            tracker = std::make_shared&lt;IndexTracker&gt;( nameAndLocation, ctx, &amp;currentTracker, size );
            currentTracker.addChild( tracker );
        }

        if( !ctx.completedCycle() &amp;&amp; !tracker-&gt;isComplete() ) {
            if( tracker-&gt;m_runState != ExecutingChildren &amp;&amp; tracker-&gt;m_runState != NeedsAnotherRun )
                tracker-&gt;moveNext();
            tracker-&gt;open();
        }

        return *tracker;
    }

    int IndexTracker::index() const { return m_index; }

    void IndexTracker::moveNext() {
        m_index++;
        m_children.clear();
    }

    void IndexTracker::close() {
        TrackerBase::close();
        if( m_runState == CompletedSuccessfully &amp;&amp; m_index &lt; m_size-1 )
            m_runState = Executing;
    }

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;
using TestCaseTracking::IndexTracker;

} // namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif
// end catch_test_case_tracker.cpp
// start catch_test_registry.cpp

namespace Catch {

    auto makeTestInvoker( void(*testAsFunction)() ) noexcept -&gt; ITestInvoker* {
        return new(std::nothrow) TestInvokerAsFunction( testAsFunction );
    }

    NameAndTags::NameAndTags( StringRef name_ , StringRef tags_ ) noexcept : name( name_ ), tags( tags_ ) {}

    AutoReg::AutoReg( ITestInvoker* invoker, SourceLineInfo const&amp; lineInfo, StringRef classOrMethod, NameAndTags const&amp; nameAndTags ) noexcept {
        try {
            getMutableRegistryHub()
                    .registerTest(
                        makeTestCase(
                            invoker,
                            extractClassName( classOrMethod ),
                            nameAndTags.name,
                            nameAndTags.tags,
                            lineInfo));
        } catch (...) {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }

    AutoReg::~AutoReg() = default;
}
// end catch_test_registry.cpp
// start catch_test_spec.cpp

#include &lt;algorithm&gt;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    TestSpec::Pattern::~Pattern() = default;
    TestSpec::NamePattern::~NamePattern() = default;
    TestSpec::TagPattern::~TagPattern() = default;
    TestSpec::ExcludedPattern::~ExcludedPattern() = default;

    TestSpec::NamePattern::NamePattern( std::string const&amp; name )
    : m_wildcardPattern( toLower( name ), CaseSensitive::No )
    {}
    bool TestSpec::NamePattern::matches( TestCaseInfo const&amp; testCase ) const {
        return m_wildcardPattern.matches( toLower( testCase.name ) );
    }

    TestSpec::TagPattern::TagPattern( std::string const&amp; tag ) : m_tag( toLower( tag ) ) {}
    bool TestSpec::TagPattern::matches( TestCaseInfo const&amp; testCase ) const {
        return std::find(begin(testCase.lcaseTags),
                         end(testCase.lcaseTags),
                         m_tag) != end(testCase.lcaseTags);
    }

    TestSpec::ExcludedPattern::ExcludedPattern( PatternPtr const&amp; underlyingPattern ) : m_underlyingPattern( underlyingPattern ) {}
    bool TestSpec::ExcludedPattern::matches( TestCaseInfo const&amp; testCase ) const { return !m_underlyingPattern-&gt;matches( testCase ); }

    bool TestSpec::Filter::matches( TestCaseInfo const&amp; testCase ) const {
        // All patterns in a filter must match for the filter to be a match
        for( auto const&amp; pattern : m_patterns ) {
            if( !pattern-&gt;matches( testCase ) )
                return false;
        }
        return true;
    }

    bool TestSpec::hasFilters() const {
        return !m_filters.empty();
    }
    bool TestSpec::matches( TestCaseInfo const&amp; testCase ) const {
        // A TestSpec matches if any filter matches
        for( auto const&amp; filter : m_filters )
            if( filter.matches( testCase ) )
                return true;
        return false;
    }
}
// end catch_test_spec.cpp
// start catch_test_spec_parser.cpp

namespace Catch {

    TestSpecParser::TestSpecParser( ITagAliasRegistry const&amp; tagAliases ) : m_tagAliases( &amp;tagAliases ) {}

    TestSpecParser&amp; TestSpecParser::parse( std::string const&amp; arg ) {
        m_mode = None;
        m_exclusion = false;
        m_start = std::string::npos;
        m_arg = m_tagAliases-&gt;expandAliases( arg );
        m_escapeChars.clear();
        for( m_pos = 0; m_pos &lt; m_arg.size(); ++m_pos )
            visitChar( m_arg[m_pos] );
        if( m_mode == Name )
            addPattern&lt;TestSpec::NamePattern&gt;();
        return *this;
    }
    TestSpec TestSpecParser::testSpec() {
        addFilter();
        return m_testSpec;
    }

    void TestSpecParser::visitChar( char c ) {
        if( m_mode == None ) {
            switch( c ) {
            case ' ': return;
            case '~': m_exclusion = true; return;
            case '[': return startNewMode( Tag, ++m_pos );
            case '"': return startNewMode( QuotedName, ++m_pos );
            case '\\': return escape();
            default: startNewMode( Name, m_pos ); break;
            }
        }
        if( m_mode == Name ) {
            if( c == ',' ) {
                addPattern&lt;TestSpec::NamePattern&gt;();
                addFilter();
            }
            else if( c == '[' ) {
                if( subString() == "exclude:" )
                    m_exclusion = true;
                else
                    addPattern&lt;TestSpec::NamePattern&gt;();
                startNewMode( Tag, ++m_pos );
            }
            else if( c == '\\' )
                escape();
        }
        else if( m_mode == EscapedName )
            m_mode = Name;
        else if( m_mode == QuotedName &amp;&amp; c == '"' )
            addPattern&lt;TestSpec::NamePattern&gt;();
        else if( m_mode == Tag &amp;&amp; c == ']' )
            addPattern&lt;TestSpec::TagPattern&gt;();
    }
    void TestSpecParser::startNewMode( Mode mode, std::size_t start ) {
        m_mode = mode;
        m_start = start;
    }
    void TestSpecParser::escape() {
        if( m_mode == None )
            m_start = m_pos;
        m_mode = EscapedName;
        m_escapeChars.push_back( m_pos );
    }
    std::string TestSpecParser::subString() const { return m_arg.substr( m_start, m_pos - m_start ); }

    void TestSpecParser::addFilter() {
        if( !m_currentFilter.m_patterns.empty() ) {
            m_testSpec.m_filters.push_back( m_currentFilter );
            m_currentFilter = TestSpec::Filter();
        }
    }

    TestSpec parseTestSpec( std::string const&amp; arg ) {
        return TestSpecParser( ITagAliasRegistry::get() ).parse( arg ).testSpec();
    }

} // namespace Catch
// end catch_test_spec_parser.cpp
// start catch_timer.cpp

#include &lt;chrono&gt;

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -&gt; uint64_t {
        return std::chrono::duration_cast&lt;std::chrono::nanoseconds&gt;( std::chrono::high_resolution_clock::now().time_since_epoch() ).count();
    }

    auto estimateClockResolution() -&gt; uint64_t {
        uint64_t sum = 0;
        static const uint64_t iterations = 1000000;

        for( std::size_t i = 0; i &lt; iterations; ++i ) {

            uint64_t ticks;
            uint64_t baseTicks = getCurrentNanosecondsSinceEpoch();
            do {
                ticks = getCurrentNanosecondsSinceEpoch();
            }
            while( ticks == baseTicks );

            auto delta = ticks - baseTicks;
            sum += delta;
        }

        // We're just taking the mean, here. To do better we could take the std. dev and exclude outliers
        // - and potentially do more iterations if there's a high variance.
        return sum/iterations;
    }
    auto getEstimatedClockResolution() -&gt; uint64_t {
        static auto s_resolution = estimateClockResolution();
        return s_resolution;
    }

    void Timer::start() {
       m_nanoseconds = getCurrentNanosecondsSinceEpoch();
    }
    auto Timer::getElapsedNanoseconds() const -&gt; unsigned int {
        return static_cast&lt;unsigned int&gt;(getCurrentNanosecondsSinceEpoch() - m_nanoseconds);
    }
    auto Timer::getElapsedMicroseconds() const -&gt; unsigned int {
        return static_cast&lt;unsigned int&gt;(getElapsedNanoseconds()/1000);
    }
    auto Timer::getElapsedMilliseconds() const -&gt; unsigned int {
        return static_cast&lt;unsigned int&gt;(getElapsedMicroseconds()/1000);
    }
    auto Timer::getElapsedSeconds() const -&gt; double {
        return getElapsedMicroseconds()/1000000.0;
    }

} // namespace Catch
// end catch_timer.cpp
// start catch_tostring.cpp

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#    pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

#include &lt;iomanip&gt;

namespace Catch {

namespace Detail {

    const std::string unprintableString = "{?}";

    namespace {
        const int hexThreshold = 255;

        struct Endianness {
            enum Arch { Big, Little };

            static Arch which() {
                union _{
                    int asInt;
                    char asChar[sizeof (int)];
                } u;

                u.asInt = 1;
                return ( u.asChar[sizeof(int)-1] == 1 ) ? Big : Little;
            }
        };
    }

    std::string rawMemoryToString( const void *object, std::size_t size ) {
        // Reverse order for little endian architectures
        int i = 0, end = static_cast&lt;int&gt;( size ), inc = 1;
        if( Endianness::which() == Endianness::Little ) {
            i = end-1;
            end = inc = -1;
        }

        unsigned char const *bytes = static_cast&lt;unsigned char const *&gt;(object);
        std::ostringstream os;
        os &lt;&lt; "0x" &lt;&lt; std::setfill('0') &lt;&lt; std::hex;
        for( ; i != end; i += inc )
             os &lt;&lt; std::setw(2) &lt;&lt; static_cast&lt;unsigned&gt;(bytes[i]);
       return os.str();
    }
}

template&lt;typename T&gt;
std::string fpToString( T value, int precision ) {
    std::ostringstream oss;
    oss &lt;&lt; std::setprecision( precision )
        &lt;&lt; std::fixed
        &lt;&lt; value;
    std::string d = oss.str();
    std::size_t i = d.find_last_not_of( '0' );
    if( i != std::string::npos &amp;&amp; i != d.size()-1 ) {
        if( d[i] == '.' )
            i++;
        d = d.substr( 0, i+1 );
    }
    return d;
}

//// ======================================================= ////
//
//   Out-of-line defs for full specialization of StringMaker
//
//// ======================================================= ////

std::string StringMaker&lt;std::string&gt;::convert(const std::string&amp; str) {
    if (!getCurrentContext().getConfig()-&gt;showInvisibles()) {
        return '"' + str + '"';
    }

    std::string s("\"");
    for (char c : str) {
        switch (c) {
        case '\n':
            s.append("\\n");
            break;
        case '\t':
            s.append("\\t");
            break;
        default:
            s.push_back(c);
            break;
        }
    }
    s.append("\"");
    return s;
}

std::string StringMaker&lt;std::wstring&gt;::convert(const std::wstring&amp; wstr) {
    std::string s;
    s.reserve(wstr.size());
    for (auto c : wstr) {
        s += (c &lt;= 0xff) ? static_cast&lt;char&gt;(c) : '?';
    }
    return ::Catch::Detail::stringify(s);
}

std::string StringMaker&lt;char const*&gt;::convert(char const* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker&lt;char*&gt;::convert(char* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker&lt;wchar_t const*&gt;::convert(wchar_t const * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker&lt;wchar_t *&gt;::convert(wchar_t * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}

std::string StringMaker&lt;int&gt;::convert(int value) {
    return ::Catch::Detail::stringify(static_cast&lt;long long&gt;(value));
}
std::string StringMaker&lt;long&gt;::convert(long value) {
    return ::Catch::Detail::stringify(static_cast&lt;long long&gt;(value));
}
std::string StringMaker&lt;long long&gt;::convert(long long value) {
    std::ostringstream oss;
    oss &lt;&lt; value;
    if (value &gt; Detail::hexThreshold) {
        oss &lt;&lt; " (0x" &lt;&lt; std::hex &lt;&lt; value &lt;&lt; ')';
    }
    return oss.str();
}

std::string StringMaker&lt;unsigned int&gt;::convert(unsigned int value) {
    return ::Catch::Detail::stringify(static_cast&lt;unsigned long long&gt;(value));
}
std::string StringMaker&lt;unsigned long&gt;::convert(unsigned long value) {
    return ::Catch::Detail::stringify(static_cast&lt;unsigned long long&gt;(value));
}
std::string StringMaker&lt;unsigned long long&gt;::convert(unsigned long long value) {
    std::ostringstream oss;
    oss &lt;&lt; value;
    if (value &gt; Detail::hexThreshold) {
        oss &lt;&lt; " (0x" &lt;&lt; std::hex &lt;&lt; value &lt;&lt; ')';
    }
    return oss.str();
}

std::string StringMaker&lt;bool&gt;::convert(bool b) {
    return b ? "true" : "false";
}

std::string StringMaker&lt;char&gt;::convert(char value) {
    if (value == '\r') {
        return "'\\r'";
    } else if (value == '\f') {
        return "'\\f'";
    } else if (value == '\n') {
        return "'\\n'";
    } else if (value == '\t') {
        return "'\\t'";
    } else if ('\0' &lt;= value &amp;&amp; value &lt; ' ') {
        return ::Catch::Detail::stringify(static_cast&lt;unsigned int&gt;(value));
    } else {
        char chstr[] = "' '";
        chstr[1] = value;
        return chstr;
    }
}
std::string StringMaker&lt;signed char&gt;::convert(signed char c) {
    return ::Catch::Detail::stringify(static_cast&lt;char&gt;(c));
}
std::string StringMaker&lt;unsigned char&gt;::convert(unsigned char c) {
    return ::Catch::Detail::stringify(static_cast&lt;char&gt;(c));
}

std::string StringMaker&lt;std::nullptr_t&gt;::convert(std::nullptr_t) {
    return "nullptr";
}

std::string StringMaker&lt;float&gt;::convert(float value) {
    return fpToString(value, 5) + 'f';
}
std::string StringMaker&lt;double&gt;::convert(double value) {
    return fpToString(value, 10);
}

} // end namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif

// end catch_tostring.cpp
// start catch_totals.cpp

namespace Catch {

    Counts Counts::operator - ( Counts const&amp; other ) const {
        Counts diff;
        diff.passed = passed - other.passed;
        diff.failed = failed - other.failed;
        diff.failedButOk = failedButOk - other.failedButOk;
        return diff;
    }

    Counts&amp; Counts::operator += ( Counts const&amp; other ) {
        passed += other.passed;
        failed += other.failed;
        failedButOk += other.failedButOk;
        return *this;
    }

    std::size_t Counts::total() const {
        return passed + failed + failedButOk;
    }
    bool Counts::allPassed() const {
        return failed == 0 &amp;&amp; failedButOk == 0;
    }
    bool Counts::allOk() const {
        return failed == 0;
    }

    Totals Totals::operator - ( Totals const&amp; other ) const {
        Totals diff;
        diff.assertions = assertions - other.assertions;
        diff.testCases = testCases - other.testCases;
        return diff;
    }

    Totals&amp; Totals::operator += ( Totals const&amp; other ) {
        assertions += other.assertions;
        testCases += other.testCases;
        return *this;
    }

    Totals Totals::delta( Totals const&amp; prevTotals ) const {
        Totals diff = *this - prevTotals;
        if( diff.assertions.failed &gt; 0 )
            ++diff.testCases.failed;
        else if( diff.assertions.failedButOk &gt; 0 )
            ++diff.testCases.failedButOk;
        else
            ++diff.testCases.passed;
        return diff;
    }

}
// end catch_totals.cpp
// start catch_version.cpp

#include &lt;ostream&gt;

namespace Catch {

    Version::Version
        (   unsigned int _majorVersion,
            unsigned int _minorVersion,
            unsigned int _patchNumber,
            char const * const _branchName,
            unsigned int _buildNumber )
    :   majorVersion( _majorVersion ),
        minorVersion( _minorVersion ),
        patchNumber( _patchNumber ),
        branchName( _branchName ),
        buildNumber( _buildNumber )
    {}

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Version const&amp; version ) {
        os  &lt;&lt; version.majorVersion &lt;&lt; '.'
            &lt;&lt; version.minorVersion &lt;&lt; '.'
            &lt;&lt; version.patchNumber;
        // branchName is never null -&gt; 0th char is \0 if it is empty
        if (version.branchName[0]) {
            os &lt;&lt; '-' &lt;&lt; version.branchName
               &lt;&lt; '.' &lt;&lt; version.buildNumber;
        }
        return os;
    }

    Version const&amp; libraryVersion() {
        static Version version( 2, 0, 1, "", 0 );
        return version;
    }

}
// end catch_version.cpp
// start catch_wildcard_pattern.cpp

namespace Catch {

    WildcardPattern::WildcardPattern( std::string const&amp; pattern,
                                      CaseSensitive::Choice caseSensitivity )
    :   m_caseSensitivity( caseSensitivity ),
        m_pattern( adjustCase( pattern ) )
    {
        if( startsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 1 );
            m_wildcard = WildcardAtStart;
        }
        if( endsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 0, m_pattern.size()-1 );
            m_wildcard = static_cast&lt;WildcardPosition&gt;( m_wildcard | WildcardAtEnd );
        }
    }

    bool WildcardPattern::matches( std::string const&amp; str ) const {
        switch( m_wildcard ) {
            case NoWildcard:
                return m_pattern == adjustCase( str );
            case WildcardAtStart:
                return endsWith( adjustCase( str ), m_pattern );
            case WildcardAtEnd:
                return startsWith( adjustCase( str ), m_pattern );
            case WildcardAtBothEnds:
                return contains( adjustCase( str ), m_pattern );
            default:
                CATCH_INTERNAL_ERROR( "Unknown enum" );
        }
    }

    std::string WildcardPattern::adjustCase( std::string const&amp; str ) const {
        return m_caseSensitivity == CaseSensitive::No ? toLower( str ) : str;
    }
}
// end catch_wildcard_pattern.cpp
// start catch_xmlwriter.cpp

// start catch_xmlwriter.h

#include &lt;sstream&gt;
#include &lt;vector&gt;

namespace Catch {

    class XmlEncode {
    public:
        enum ForWhat { ForTextNodes, ForAttributes };

        XmlEncode( std::string const&amp; str, ForWhat forWhat = ForTextNodes );

        void encodeTo( std::ostream&amp; os ) const;

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, XmlEncode const&amp; xmlEncode );

    private:
        std::string m_str;
        ForWhat m_forWhat;
    };

    class XmlWriter {
    public:

        class ScopedElement {
        public:
            ScopedElement( XmlWriter* writer );

            ScopedElement( ScopedElement&amp;&amp; other ) noexcept;
            ScopedElement&amp; operator=( ScopedElement&amp;&amp; other ) noexcept;

            ~ScopedElement();

            ScopedElement&amp; writeText( std::string const&amp; text, bool indent = true );

            template&lt;typename T&gt;
            ScopedElement&amp; writeAttribute( std::string const&amp; name, T const&amp; attribute ) {
                m_writer-&gt;writeAttribute( name, attribute );
                return *this;
            }

        private:
            mutable XmlWriter* m_writer = nullptr;
        };

        XmlWriter( std::ostream&amp; os = Catch::cout() );
        ~XmlWriter();

        XmlWriter( XmlWriter const&amp; ) = delete;
        XmlWriter&amp; operator=( XmlWriter const&amp; ) = delete;

        XmlWriter&amp; startElement( std::string const&amp; name );

        ScopedElement scopedElement( std::string const&amp; name );

        XmlWriter&amp; endElement();

        XmlWriter&amp; writeAttribute( std::string const&amp; name, std::string const&amp; attribute );

        XmlWriter&amp; writeAttribute( std::string const&amp; name, bool attribute );

        template&lt;typename T&gt;
        XmlWriter&amp; writeAttribute( std::string const&amp; name, T const&amp; attribute ) {
            m_oss.clear();
            m_oss.str(std::string());
            m_oss &lt;&lt; attribute;
            return writeAttribute( name, m_oss.str() );
        }

        XmlWriter&amp; writeText( std::string const&amp; text, bool indent = true );

        XmlWriter&amp; writeComment( std::string const&amp; text );

        void writeStylesheetRef( std::string const&amp; url );

        XmlWriter&amp; writeBlankLine();

        void ensureTagClosed();

    private:

        void writeDeclaration();

        void newlineIfNecessary();

        bool m_tagIsOpen = false;
        bool m_needsNewline = false;
        std::vector&lt;std::string&gt; m_tags;
        std::string m_indent;
        std::ostream&amp; m_os;
        std::ostringstream m_oss;
    };

}

// end catch_xmlwriter.h
#include &lt;iomanip&gt;

namespace Catch {

    XmlEncode::XmlEncode( std::string const&amp; str, ForWhat forWhat )
    :   m_str( str ),
        m_forWhat( forWhat )
    {}

    void XmlEncode::encodeTo( std::ostream&amp; os ) const {

        // Apostrophe escaping not necessary if we always use " to write attributes
        // (see: http://www.w3.org/TR/xml/#syntax)

        for( std::size_t i = 0; i &lt; m_str.size(); ++ i ) {
            char c = m_str[i];
            switch( c ) {
                case '&lt;':   os &lt;&lt; "&amp;lt;"; break;
                case '&amp;':   os &lt;&lt; "&amp;amp;"; break;

                case '&gt;':
                    // See: http://www.w3.org/TR/xml/#syntax
                    if( i &gt; 2 &amp;&amp; m_str[i-1] == ']' &amp;&amp; m_str[i-2] == ']' )
                        os &lt;&lt; "&amp;gt;";
                    else
                        os &lt;&lt; c;
                    break;

                case '\"':
                    if( m_forWhat == ForAttributes )
                        os &lt;&lt; "&amp;quot;";
                    else
                        os &lt;&lt; c;
                    break;

                default:
                    // Escape control chars - based on contribution by @espenalb in PR #465 and
                    // by @mrpi PR #588
                    if ( ( c &gt;= 0 &amp;&amp; c &lt; '\x09' ) || ( c &gt; '\x0D' &amp;&amp; c &lt; '\x20') || c=='\x7F' ) {
                        // see http://stackoverflow.com/questions/404107/why-are-control-characters-illegal-in-xml-1-0
                        os &lt;&lt; "\\x" &lt;&lt; std::uppercase &lt;&lt; std::hex &lt;&lt; std::setfill('0') &lt;&lt; std::setw(2)
                           &lt;&lt; static_cast&lt;int&gt;( c );
                    }
                    else
                        os &lt;&lt; c;
            }
        }
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, XmlEncode const&amp; xmlEncode ) {
        xmlEncode.encodeTo( os );
        return os;
    }

    XmlWriter::ScopedElement::ScopedElement( XmlWriter* writer )
    :   m_writer( writer )
    {}

    XmlWriter::ScopedElement::ScopedElement( ScopedElement&amp;&amp; other ) noexcept
    :   m_writer( other.m_writer ){
        other.m_writer = nullptr;
    }
    XmlWriter::ScopedElement&amp; XmlWriter::ScopedElement::operator=( ScopedElement&amp;&amp; other ) noexcept {
        if ( m_writer ) {
            m_writer-&gt;endElement();
        }
        m_writer = other.m_writer;
        other.m_writer = nullptr;
        return *this;
    }

    XmlWriter::ScopedElement::~ScopedElement() {
        if( m_writer )
            m_writer-&gt;endElement();
    }

    XmlWriter::ScopedElement&amp; XmlWriter::ScopedElement::writeText( std::string const&amp; text, bool indent ) {
        m_writer-&gt;writeText( text, indent );
        return *this;
    }

    XmlWriter::XmlWriter( std::ostream&amp; os ) : m_os( os )
    {
        writeDeclaration();
    }

    XmlWriter::~XmlWriter() {
        while( !m_tags.empty() )
            endElement();
    }

    XmlWriter&amp; XmlWriter::startElement( std::string const&amp; name ) {
        ensureTagClosed();
        newlineIfNecessary();
        m_os &lt;&lt; m_indent &lt;&lt; '&lt;' &lt;&lt; name;
        m_tags.push_back( name );
        m_indent += "  ";
        m_tagIsOpen = true;
        return *this;
    }

    XmlWriter::ScopedElement XmlWriter::scopedElement( std::string const&amp; name ) {
        ScopedElement scoped( this );
        startElement( name );
        return scoped;
    }

    XmlWriter&amp; XmlWriter::endElement() {
        newlineIfNecessary();
        m_indent = m_indent.substr( 0, m_indent.size()-2 );
        if( m_tagIsOpen ) {
            m_os &lt;&lt; "/&gt;";
            m_tagIsOpen = false;
        }
        else {
            m_os &lt;&lt; m_indent &lt;&lt; "&lt;/" &lt;&lt; m_tags.back() &lt;&lt; "&gt;";
        }
        m_os &lt;&lt; std::endl;
        m_tags.pop_back();
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeAttribute( std::string const&amp; name, std::string const&amp; attribute ) {
        if( !name.empty() &amp;&amp; !attribute.empty() )
            m_os &lt;&lt; ' ' &lt;&lt; name &lt;&lt; "=\"" &lt;&lt; XmlEncode( attribute, XmlEncode::ForAttributes ) &lt;&lt; '"';
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeAttribute( std::string const&amp; name, bool attribute ) {
        m_os &lt;&lt; ' ' &lt;&lt; name &lt;&lt; "=\"" &lt;&lt; ( attribute ? "true" : "false" ) &lt;&lt; '"';
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeText( std::string const&amp; text, bool indent ) {
        if( !text.empty() ){
            bool tagWasOpen = m_tagIsOpen;
            ensureTagClosed();
            if( tagWasOpen &amp;&amp; indent )
                m_os &lt;&lt; m_indent;
            m_os &lt;&lt; XmlEncode( text );
            m_needsNewline = true;
        }
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeComment( std::string const&amp; text ) {
        ensureTagClosed();
        m_os &lt;&lt; m_indent &lt;&lt; "&lt;!--" &lt;&lt; text &lt;&lt; "--&gt;";
        m_needsNewline = true;
        return *this;
    }

    void XmlWriter::writeStylesheetRef( std::string const&amp; url ) {
        m_os &lt;&lt; "&lt;?xml-stylesheet type=\"text/xsl\" href=\"" &lt;&lt; url &lt;&lt; "\"?&gt;\n";
    }

    XmlWriter&amp; XmlWriter::writeBlankLine() {
        ensureTagClosed();
        m_os &lt;&lt; '\n';
        return *this;
    }

    void XmlWriter::ensureTagClosed() {
        if( m_tagIsOpen ) {
            m_os &lt;&lt; "&gt;" &lt;&lt; std::endl;
            m_tagIsOpen = false;
        }
    }

    void XmlWriter::writeDeclaration() {
        m_os &lt;&lt; "&lt;?xml version=\"1.0\" encoding=\"UTF-8\"?&gt;\n";
    }

    void XmlWriter::newlineIfNecessary() {
        if( m_needsNewline ) {
            m_os &lt;&lt; std::endl;
            m_needsNewline = false;
        }
    }
}
// end catch_xmlwriter.cpp
// start catch_reporter_bases.cpp

#include &lt;cstring&gt;
#include &lt;cfloat&gt;
#include &lt;cstdio&gt;
#include &lt;assert.h&gt;
#include &lt;memory&gt;

namespace Catch {
    void prepareExpandedExpression(AssertionResult&amp; result) {
        result.getExpandedExpression();
    }

    // Because formatting using c++ streams is stateful, drop down to C is required
    // Alternatively we could use stringstream, but its performance is... not good.
    std::string getFormattedDuration( double duration ) {
        // Max exponent + 1 is required to represent the whole part
        // + 1 for decimal point
        // + 3 for the 3 decimal places
        // + 1 for null terminator
        const std::size_t maxDoubleSize = DBL_MAX_10_EXP + 1 + 1 + 3 + 1;
        char buffer[maxDoubleSize];

        // Save previous errno, to prevent sprintf from overwriting it
        ErrnoGuard guard;
#ifdef _MSC_VER
        sprintf_s(buffer, "%.3f", duration);
#else
        sprintf(buffer, "%.3f", duration);
#endif
        return std::string(buffer);
    }

    TestEventListenerBase::TestEventListenerBase(ReporterConfig const &amp; _config)
        :StreamingReporterBase(_config) {}

    void TestEventListenerBase::assertionStarting(AssertionInfo const &amp;) {}

    bool TestEventListenerBase::assertionEnded(AssertionStats const &amp;) {
        return false;
    }

} // end namespace Catch
// end catch_reporter_bases.cpp
// start catch_reporter_compact.cpp

namespace {

#ifdef CATCH_PLATFORM_MAC
    const char* failedString() { return "FAILED"; }
    const char* passedString() { return "PASSED"; }
#else
    const char* failedString() { return "failed"; }
    const char* passedString() { return "passed"; }
#endif

    // Colour::LightGrey
    Catch::Colour::Code dimColour() { return Catch::Colour::FileName; }

    std::string bothOrAll( std::size_t count ) {
        return count == 1 ? std::string() :
               count == 2 ? "both " : "all " ;
    }
}

namespace Catch {

    struct CompactReporter : StreamingReporterBase&lt;CompactReporter&gt; {

        using StreamingReporterBase::StreamingReporterBase;

        ~CompactReporter() override;

        static std::string getDescription() {
            return "Reports test results on a single line, suitable for IDEs";
        }

        ReporterPreferences getPreferences() const override {
            ReporterPreferences prefs;
            prefs.shouldRedirectStdOut = false;
            return prefs;
        }

        void noMatchingTestCases( std::string const&amp; spec ) override {
            stream &lt;&lt; "No test cases matched '" &lt;&lt; spec &lt;&lt; '\'' &lt;&lt; std::endl;
        }

        void assertionStarting( AssertionInfo const&amp; ) override {}

        bool assertionEnded( AssertionStats const&amp; _assertionStats ) override {
            AssertionResult const&amp; result = _assertionStats.assertionResult;

            bool printInfoMessages = true;

            // Drop out if result was successful and we're not printing those
            if( !m_config-&gt;includeSuccessfulResults() &amp;&amp; result.isOk() ) {
                if( result.getResultType() != ResultWas::Warning )
                    return false;
                printInfoMessages = false;
            }

            AssertionPrinter printer( stream, _assertionStats, printInfoMessages );
            printer.print();

            stream &lt;&lt; std::endl;
            return true;
        }

        void sectionEnded(SectionStats const&amp; _sectionStats) override {
            if (m_config-&gt;showDurations() == ShowDurations::Always) {
                stream &lt;&lt; getFormattedDuration(_sectionStats.durationInSeconds) &lt;&lt; " s: " &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; std::endl;
            }
        }

        void testRunEnded( TestRunStats const&amp; _testRunStats ) override {
            printTotals( _testRunStats.totals );
            stream &lt;&lt; '\n' &lt;&lt; std::endl;
            StreamingReporterBase::testRunEnded( _testRunStats );
        }

    private:
        class AssertionPrinter {
        public:
            AssertionPrinter&amp; operator= ( AssertionPrinter const&amp; ) = delete;
            AssertionPrinter( AssertionPrinter const&amp; ) = delete;
            AssertionPrinter( std::ostream&amp; _stream, AssertionStats const&amp; _stats, bool _printInfoMessages )
            : stream( _stream )
            , result( _stats.assertionResult )
            , messages( _stats.infoMessages )
            , itMessage( _stats.infoMessages.begin() )
            , printInfoMessages( _printInfoMessages )
            {}

            void print() {
                printSourceInfo();

                itMessage = messages.begin();

                switch( result.getResultType() ) {
                    case ResultWas::Ok:
                        printResultType( Colour::ResultSuccess, passedString() );
                        printOriginalExpression();
                        printReconstructedExpression();
                        if ( ! result.hasExpression() )
                            printRemainingMessages( Colour::None );
                        else
                            printRemainingMessages();
                        break;
                    case ResultWas::ExpressionFailed:
                        if( result.isOk() )
                            printResultType( Colour::ResultSuccess, failedString() + std::string( " - but was ok" ) );
                        else
                            printResultType( Colour::Error, failedString() );
                        printOriginalExpression();
                        printReconstructedExpression();
                        printRemainingMessages();
                        break;
                    case ResultWas::ThrewException:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "unexpected exception with message:" );
                        printMessage();
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::FatalErrorCondition:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "fatal error condition with message:" );
                        printMessage();
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::DidntThrowException:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "expected exception, got none" );
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::Info:
                        printResultType( Colour::None, "info" );
                        printMessage();
                        printRemainingMessages();
                        break;
                    case ResultWas::Warning:
                        printResultType( Colour::None, "warning" );
                        printMessage();
                        printRemainingMessages();
                        break;
                    case ResultWas::ExplicitFailure:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "explicitly" );
                        printRemainingMessages( Colour::None );
                        break;
                    // These cases are here to prevent compiler warnings
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        printResultType( Colour::Error, "** internal error **" );
                        break;
                }
            }

        private:
            void printSourceInfo() const {
                Colour colourGuard( Colour::FileName );
                stream &lt;&lt; result.getSourceInfo() &lt;&lt; ':';
            }

            void printResultType( Colour::Code colour, std::string const&amp; passOrFail ) const {
                if( !passOrFail.empty() ) {
                    {
                        Colour colourGuard( colour );
                        stream &lt;&lt; ' ' &lt;&lt; passOrFail;
                    }
                    stream &lt;&lt; ':';
                }
            }

            void printIssue( std::string const&amp; issue ) const {
                stream &lt;&lt; ' ' &lt;&lt; issue;
            }

            void printExpressionWas() {
                if( result.hasExpression() ) {
                    stream &lt;&lt; ';';
                    {
                        Colour colour( dimColour() );
                        stream &lt;&lt; " expression was:";
                    }
                    printOriginalExpression();
                }
            }

            void printOriginalExpression() const {
                if( result.hasExpression() ) {
                    stream &lt;&lt; ' ' &lt;&lt; result.getExpression();
                }
            }

            void printReconstructedExpression() const {
                if( result.hasExpandedExpression() ) {
                    {
                        Colour colour( dimColour() );
                        stream &lt;&lt; " for: ";
                    }
                    stream &lt;&lt; result.getExpandedExpression();
                }
            }

            void printMessage() {
                if ( itMessage != messages.end() ) {
                    stream &lt;&lt; " '" &lt;&lt; itMessage-&gt;message &lt;&lt; '\'';
                    ++itMessage;
                }
            }

            void printRemainingMessages( Colour::Code colour = dimColour() ) {
                if ( itMessage == messages.end() )
                    return;

                // using messages.end() directly yields (or auto) compilation error:
                std::vector&lt;MessageInfo&gt;::const_iterator itEnd = messages.end();
                const std::size_t N = static_cast&lt;std::size_t&gt;( std::distance( itMessage, itEnd ) );

                {
                    Colour colourGuard( colour );
                    stream &lt;&lt; " with " &lt;&lt; pluralise( N, "message" ) &lt;&lt; ':';
                }

                for(; itMessage != itEnd; ) {
                    // If this assertion is a warning ignore any INFO messages
                    if( printInfoMessages || itMessage-&gt;type != ResultWas::Info ) {
                        stream &lt;&lt; " '" &lt;&lt; itMessage-&gt;message &lt;&lt; '\'';
                        if ( ++itMessage != itEnd ) {
                            Colour colourGuard( dimColour() );
                            stream &lt;&lt; " and";
                        }
                    }
                }
            }

        private:
            std::ostream&amp; stream;
            AssertionResult const&amp; result;
            std::vector&lt;MessageInfo&gt; messages;
            std::vector&lt;MessageInfo&gt;::const_iterator itMessage;
            bool printInfoMessages;
        };

        // Colour, message variants:
        // - white: No tests ran.
        // -   red: Failed [both/all] N test cases, failed [both/all] M assertions.
        // - white: Passed [both/all] N test cases (no assertions).
        // -   red: Failed N tests cases, failed M assertions.
        // - green: Passed [both/all] N tests cases with M assertions.

        void printTotals( const Totals&amp; totals ) const {
            if( totals.testCases.total() == 0 ) {
                stream &lt;&lt; "No tests ran.";
            }
            else if( totals.testCases.failed == totals.testCases.total() ) {
                Colour colour( Colour::ResultError );
                const std::string qualify_assertions_failed =
                    totals.assertions.failed == totals.assertions.total() ?
                        bothOrAll( totals.assertions.failed ) : std::string();
                stream &lt;&lt;
                    "Failed " &lt;&lt; bothOrAll( totals.testCases.failed )
                              &lt;&lt; pluralise( totals.testCases.failed, "test case"  ) &lt;&lt; ", "
                    "failed " &lt;&lt; qualify_assertions_failed &lt;&lt;
                                 pluralise( totals.assertions.failed, "assertion" ) &lt;&lt; '.';
            }
            else if( totals.assertions.total() == 0 ) {
                stream &lt;&lt;
                    "Passed " &lt;&lt; bothOrAll( totals.testCases.total() )
                              &lt;&lt; pluralise( totals.testCases.total(), "test case" )
                              &lt;&lt; " (no assertions).";
            }
            else if( totals.assertions.failed ) {
                Colour colour( Colour::ResultError );
                stream &lt;&lt;
                    "Failed " &lt;&lt; pluralise( totals.testCases.failed, "test case"  ) &lt;&lt; ", "
                    "failed " &lt;&lt; pluralise( totals.assertions.failed, "assertion" ) &lt;&lt; '.';
            }
            else {
                Colour colour( Colour::ResultSuccess );
                stream &lt;&lt;
                    "Passed " &lt;&lt; bothOrAll( totals.testCases.passed )
                              &lt;&lt; pluralise( totals.testCases.passed, "test case"  ) &lt;&lt;
                    " with "  &lt;&lt; pluralise( totals.assertions.passed, "assertion" ) &lt;&lt; '.';
            }
        }
    };

    CompactReporter::~CompactReporter() {}

    CATCH_REGISTER_REPORTER( "compact", CompactReporter )

} // end namespace Catch
// end catch_reporter_compact.cpp
// start catch_reporter_console.cpp

#include &lt;cfloat&gt;
#include &lt;cstdio&gt;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // Not all labels are EXPLICITLY handled in switch
                              // Note that 4062 (not all labels are handled
                              // and default is missing) is enabled
#endif

namespace Catch {

    namespace {
        std::size_t makeRatio( std::size_t number, std::size_t total ) {
            std::size_t ratio = total &gt; 0 ? CATCH_CONFIG_CONSOLE_WIDTH * number/ total : 0;
            return ( ratio == 0 &amp;&amp; number &gt; 0 ) ? 1 : ratio;
        }

        std::size_t&amp; findMax( std::size_t&amp; i, std::size_t&amp; j, std::size_t&amp; k ) {
            if( i &gt; j &amp;&amp; i &gt; k )
                return i;
            else if( j &gt; k )
                return j;
            else
                return k;
        }

        struct ColumnInfo {
            enum Justification { Left, Right };
            std::string name;
            int width;
            Justification justification;
        };
        struct ColumnBreak {};
        struct RowBreak {};

        class TablePrinter {
            std::ostream&amp; m_os;
            std::vector&lt;ColumnInfo&gt; m_columnInfos;
            std::ostringstream m_oss;
            int m_currentColumn = -1;
            bool m_isOpen = false;

        public:
            TablePrinter( std::ostream&amp; os, std::vector&lt;ColumnInfo&gt; const&amp; columnInfos )
            :   m_os( os ),
                m_columnInfos( columnInfos )
            {}

            auto columnInfos() const -&gt; std::vector&lt;ColumnInfo&gt; const&amp; {
                return m_columnInfos;
            }

            void open() {
                if( !m_isOpen ) {
                    m_isOpen = true;
                    *this &lt;&lt; RowBreak();
                    for( auto const&amp; info : m_columnInfos )
                        *this &lt;&lt; info.name &lt;&lt; ColumnBreak();
                    *this &lt;&lt; RowBreak();
                    m_os &lt;&lt; Catch::getLineOfChars&lt;'-'&gt;() &lt;&lt; "\n";
                }
            }
            void close() {
                if( m_isOpen ) {
                    *this &lt;&lt; RowBreak();
                    m_os &lt;&lt; std::endl;
                    m_isOpen = false;
                }
            }

            template&lt;typename T&gt;
            friend TablePrinter&amp; operator &lt;&lt; ( TablePrinter&amp; tp, T const&amp; value ) {
                tp.m_oss &lt;&lt; value;
                return tp;
            }

            friend TablePrinter&amp; operator &lt;&lt; ( TablePrinter&amp; tp, ColumnBreak ) {
                auto colStr = tp.m_oss.str();
                // This takes account of utf8 encodings
                auto strSize = Catch::StringRef( colStr ).numberOfCharacters();
                tp.m_oss.str("");
                tp.open();
                if( tp.m_currentColumn == static_cast&lt;int&gt;(tp.m_columnInfos.size()-1) ) {
                    tp.m_currentColumn = -1;
                    tp.m_os &lt;&lt; "\n";
                }
                tp.m_currentColumn++;

                auto colInfo = tp.m_columnInfos[tp.m_currentColumn];
                auto padding = ( strSize+2 &lt; static_cast&lt;std::size_t&gt;( colInfo.width ) )
                    ? std::string( colInfo.width-(strSize+2), ' ' )
                    : std::string();
                if( colInfo.justification == ColumnInfo::Left )
                    tp.m_os &lt;&lt; colStr &lt;&lt; padding &lt;&lt; " ";
                else
                    tp.m_os &lt;&lt; padding &lt;&lt; colStr &lt;&lt; " ";
                return tp;
            }

            friend TablePrinter&amp; operator &lt;&lt; ( TablePrinter&amp; tp, RowBreak ) {
                if( tp.m_currentColumn &gt; 0 ) {
                    tp.m_os &lt;&lt; "\n";
                    tp.m_currentColumn = -1;
                }
                return tp;
            }
        };

        class Duration {
            enum class Unit {
                Auto,
                Nanoseconds,
                Microseconds,
                Milliseconds,
                Seconds,
                Minutes
            };
            static const uint64_t s_nanosecondsInAMicrosecond = 1000;
            static const uint64_t s_nanosecondsInAMillisecond = 1000*s_nanosecondsInAMicrosecond;
            static const uint64_t s_nanosecondsInASecond = 1000*s_nanosecondsInAMillisecond;
            static const uint64_t s_nanosecondsInAMinute = 60*s_nanosecondsInASecond;

            uint64_t m_inNanoseconds;
            Unit m_units;

        public:
            Duration( uint64_t inNanoseconds, Unit units = Unit::Auto )
            :   m_inNanoseconds( inNanoseconds ),
                m_units( units )
            {
                if( m_units == Unit::Auto ) {
                    if( m_inNanoseconds &lt; s_nanosecondsInAMicrosecond )
                        m_units = Unit::Nanoseconds;
                    else if( m_inNanoseconds &lt; s_nanosecondsInAMillisecond )
                        m_units = Unit::Microseconds;
                    else if( m_inNanoseconds &lt; s_nanosecondsInASecond )
                        m_units = Unit::Milliseconds;
                    else if( m_inNanoseconds &lt; s_nanosecondsInAMinute )
                        m_units = Unit::Seconds;
                    else
                        m_units = Unit::Minutes;
                }

            }

            auto value() const -&gt; double {
                switch( m_units ) {
                    case Unit::Microseconds:
                        return m_inNanoseconds / static_cast&lt;double&gt;( s_nanosecondsInAMicrosecond );
                    case Unit::Milliseconds:
                        return m_inNanoseconds / static_cast&lt;double&gt;( s_nanosecondsInAMillisecond );
                    case Unit::Seconds:
                        return m_inNanoseconds / static_cast&lt;double&gt;( s_nanosecondsInASecond );
                    case Unit::Minutes:
                        return m_inNanoseconds / static_cast&lt;double&gt;( s_nanosecondsInAMinute );
                    default:
                        return static_cast&lt;double&gt;( m_inNanoseconds );
                }
            }
            auto unitsAsString() const -&gt; std::string {
                switch( m_units ) {
                    case Unit::Nanoseconds:
                        return "ns";
                    case Unit::Microseconds:
                        return "µs";
                    case Unit::Milliseconds:
                        return "ms";
                    case Unit::Seconds:
                        return "s";
                    case Unit::Minutes:
                        return "m";
                    default:
                        return "** internal error **";
                }

            }
            friend auto operator &lt;&lt; ( std::ostream&amp; os, Duration const&amp; duration ) -&gt; std::ostream&amp; {
                return os &lt;&lt; duration.value() &lt;&lt; " " &lt;&lt; duration.unitsAsString();
            }
        };
    } // end anon namespace

    struct ConsoleReporter : StreamingReporterBase&lt;ConsoleReporter&gt; {
        TablePrinter m_tablePrinter;

        ConsoleReporter( ReporterConfig const&amp; config )
        :   StreamingReporterBase( config ),
            m_tablePrinter( config.stream(),
                            {
                                { "benchmark name", CATCH_CONFIG_CONSOLE_WIDTH-32, ColumnInfo::Left },
                                { "iters", 8, ColumnInfo::Right },
                                { "elapsed ns", 14, ColumnInfo::Right },
                                { "average", 14, ColumnInfo::Right }
                            } )
        {}
        ~ConsoleReporter() override;
        static std::string getDescription() {
            return "Reports test results as plain lines of text";
        }

        void noMatchingTestCases( std::string const&amp; spec ) override {
            stream &lt;&lt; "No test cases matched '" &lt;&lt; spec &lt;&lt; '\'' &lt;&lt; std::endl;
        }

        void assertionStarting( AssertionInfo const&amp; ) override {
        }

        bool assertionEnded( AssertionStats const&amp; _assertionStats ) override {
            AssertionResult const&amp; result = _assertionStats.assertionResult;

            bool includeResults = m_config-&gt;includeSuccessfulResults() || !result.isOk();

            // Drop out if result was successful but we're not printing them.
            if( !includeResults &amp;&amp; result.getResultType() != ResultWas::Warning )
                return false;

            lazyPrint();

            AssertionPrinter printer( stream, _assertionStats, includeResults );
            printer.print();
            stream &lt;&lt; std::endl;
            return true;
        }

        void sectionStarting( SectionInfo const&amp; _sectionInfo ) override {
            m_headerPrinted = false;
            StreamingReporterBase::sectionStarting( _sectionInfo );
        }
        void sectionEnded( SectionStats const&amp; _sectionStats ) override {
            m_tablePrinter.close();
            if( _sectionStats.missingAssertions ) {
                lazyPrint();
                Colour colour( Colour::ResultError );
                if( m_sectionStack.size() &gt; 1 )
                    stream &lt;&lt; "\nNo assertions in section";
                else
                    stream &lt;&lt; "\nNo assertions in test case";
                stream &lt;&lt; " '" &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; "'\n" &lt;&lt; std::endl;
            }
            if( m_config-&gt;showDurations() == ShowDurations::Always ) {
                stream &lt;&lt; getFormattedDuration(_sectionStats.durationInSeconds) &lt;&lt; " s: " &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; std::endl;
            }
            if( m_headerPrinted ) {
                m_headerPrinted = false;
            }
            StreamingReporterBase::sectionEnded( _sectionStats );
        }

        void benchmarkStarting( BenchmarkInfo const&amp; info ) override {
            lazyPrintWithoutClosingBenchmarkTable();

            auto nameCol = Column( info.name ).width( m_tablePrinter.columnInfos()[0].width-2 );

            bool firstLine = true;
            for( auto line : nameCol ) {
                if( !firstLine )
                    m_tablePrinter &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak();
                else
                    firstLine = false;

                m_tablePrinter &lt;&lt; line &lt;&lt; ColumnBreak();
            }
        }
        void benchmarkEnded( BenchmarkStats const&amp; stats ) override {
            Duration average( stats.elapsedTimeInNanoseconds/stats.iterations );
            m_tablePrinter
                    &lt;&lt; stats.iterations &lt;&lt; ColumnBreak()
                    &lt;&lt; stats.elapsedTimeInNanoseconds &lt;&lt; ColumnBreak()
                    &lt;&lt; average &lt;&lt; ColumnBreak();
        }

        void testCaseEnded( TestCaseStats const&amp; _testCaseStats ) override {
            m_tablePrinter.close();
            StreamingReporterBase::testCaseEnded( _testCaseStats );
            m_headerPrinted = false;
        }
        void testGroupEnded( TestGroupStats const&amp; _testGroupStats ) override {
            if( currentGroupInfo.used ) {
                printSummaryDivider();
                stream &lt;&lt; "Summary for group '" &lt;&lt; _testGroupStats.groupInfo.name &lt;&lt; "':\n";
                printTotals( _testGroupStats.totals );
                stream &lt;&lt; '\n' &lt;&lt; std::endl;
            }
            StreamingReporterBase::testGroupEnded( _testGroupStats );
        }
        void testRunEnded( TestRunStats const&amp; _testRunStats ) override {
            printTotalsDivider( _testRunStats.totals );
            printTotals( _testRunStats.totals );
            stream &lt;&lt; std::endl;
            StreamingReporterBase::testRunEnded( _testRunStats );
        }

    private:

        class AssertionPrinter {
        public:
            AssertionPrinter&amp; operator= ( AssertionPrinter const&amp; ) = delete;
            AssertionPrinter( AssertionPrinter const&amp; ) = delete;
            AssertionPrinter( std::ostream&amp; _stream, AssertionStats const&amp; _stats, bool _printInfoMessages )
            :   stream( _stream ),
                stats( _stats ),
                result( _stats.assertionResult ),
                colour( Colour::None ),
                message( result.getMessage() ),
                messages( _stats.infoMessages ),
                printInfoMessages( _printInfoMessages )
            {
                switch( result.getResultType() ) {
                    case ResultWas::Ok:
                        colour = Colour::Success;
                        passOrFail = "PASSED";
                        //if( result.hasMessage() )
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "with message";
                        if( _stats.infoMessages.size() &gt; 1 )
                            messageLabel = "with messages";
                        break;
                    case ResultWas::ExpressionFailed:
                        if( result.isOk() ) {
                            colour = Colour::Success;
                            passOrFail = "FAILED - but was ok";
                        }
                        else {
                            colour = Colour::Error;
                            passOrFail = "FAILED";
                        }
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "with message";
                        if( _stats.infoMessages.size() &gt; 1 )
                            messageLabel = "with messages";
                        break;
                    case ResultWas::ThrewException:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "due to unexpected exception with ";
                        if (_stats.infoMessages.size() == 1)
                            messageLabel += "message";
                        if (_stats.infoMessages.size() &gt; 1)
                            messageLabel += "messages";
                        break;
                    case ResultWas::FatalErrorCondition:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "due to a fatal error condition";
                        break;
                    case ResultWas::DidntThrowException:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "because no exception was thrown where one was expected";
                        break;
                    case ResultWas::Info:
                        messageLabel = "info";
                        break;
                    case ResultWas::Warning:
                        messageLabel = "warning";
                        break;
                    case ResultWas::ExplicitFailure:
                        passOrFail = "FAILED";
                        colour = Colour::Error;
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "explicitly with message";
                        if( _stats.infoMessages.size() &gt; 1 )
                            messageLabel = "explicitly with messages";
                        break;
                    // These cases are here to prevent compiler warnings
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        passOrFail = "** internal error **";
                        colour = Colour::Error;
                        break;
                }
            }

            void print() const {
                printSourceInfo();
                if( stats.totals.assertions.total() &gt; 0 ) {
                    if( result.isOk() )
                        stream &lt;&lt; '\n';
                    printResultType();
                    printOriginalExpression();
                    printReconstructedExpression();
                }
                else {
                    stream &lt;&lt; '\n';
                }
                printMessage();
            }

        private:
            void printResultType() const {
                if( !passOrFail.empty() ) {
                    Colour colourGuard( colour );
                    stream &lt;&lt; passOrFail &lt;&lt; ":\n";
                }
            }
            void printOriginalExpression() const {
                if( result.hasExpression() ) {
                    Colour colourGuard( Colour::OriginalExpression );
                    stream  &lt;&lt; "  ";
                    stream &lt;&lt; result.getExpressionInMacro();
                    stream &lt;&lt; '\n';
                }
            }
            void printReconstructedExpression() const {
                if( result.hasExpandedExpression() ) {
                    stream &lt;&lt; "with expansion:\n";
                    Colour colourGuard( Colour::ReconstructedExpression );
                    stream &lt;&lt; Column( result.getExpandedExpression() ).indent(2) &lt;&lt; '\n';
                }
            }
            void printMessage() const {
                if( !messageLabel.empty() )
                    stream &lt;&lt; messageLabel &lt;&lt; ':' &lt;&lt; '\n';
                for( auto const&amp; msg : messages ) {
                    // If this assertion is a warning ignore any INFO messages
                    if( printInfoMessages || msg.type != ResultWas::Info )
                        stream &lt;&lt; Column( msg.message ).indent(2) &lt;&lt; '\n';
                }
            }
            void printSourceInfo() const {
                Colour colourGuard( Colour::FileName );
                stream &lt;&lt; result.getSourceInfo() &lt;&lt; ": ";
            }

            std::ostream&amp; stream;
            AssertionStats const&amp; stats;
            AssertionResult const&amp; result;
            Colour::Code colour;
            std::string passOrFail;
            std::string messageLabel;
            std::string message;
            std::vector&lt;MessageInfo&gt; messages;
            bool printInfoMessages;
        };

        void lazyPrint() {

            m_tablePrinter.close();
            lazyPrintWithoutClosingBenchmarkTable();
        }

        void lazyPrintWithoutClosingBenchmarkTable() {

            if( !currentTestRunInfo.used )
                lazyPrintRunInfo();
            if( !currentGroupInfo.used )
                lazyPrintGroupInfo();

            if( !m_headerPrinted ) {
                printTestCaseAndSectionHeader();
                m_headerPrinted = true;
            }
        }
        void lazyPrintRunInfo() {
            stream  &lt;&lt; '\n' &lt;&lt; getLineOfChars&lt;'~'&gt;() &lt;&lt; '\n';
            Colour colour( Colour::SecondaryText );
            stream  &lt;&lt; currentTestRunInfo-&gt;name
                    &lt;&lt; " is a Catch v"  &lt;&lt; libraryVersion() &lt;&lt; " host application.\n"
                    &lt;&lt; "Run with -? for options\n\n";

            if( m_config-&gt;rngSeed() != 0 )
                stream &lt;&lt; "Randomness seeded to: " &lt;&lt; m_config-&gt;rngSeed() &lt;&lt; "\n\n";

            currentTestRunInfo.used = true;
        }
        void lazyPrintGroupInfo() {
            if( !currentGroupInfo-&gt;name.empty() &amp;&amp; currentGroupInfo-&gt;groupsCounts &gt; 1 ) {
                printClosedHeader( "Group: " + currentGroupInfo-&gt;name );
                currentGroupInfo.used = true;
            }
        }
        void printTestCaseAndSectionHeader() {
            assert( !m_sectionStack.empty() );
            printOpenHeader( currentTestCaseInfo-&gt;name );

            if( m_sectionStack.size() &gt; 1 ) {
                Colour colourGuard( Colour::Headers );

                auto
                    it = m_sectionStack.begin()+1, // Skip first section (test case)
                    itEnd = m_sectionStack.end();
                for( ; it != itEnd; ++it )
                    printHeaderString( it-&gt;name, 2 );
            }

            SourceLineInfo lineInfo = m_sectionStack.back().lineInfo;

            if( !lineInfo.empty() ){
                stream &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
                Colour colourGuard( Colour::FileName );
                stream &lt;&lt; lineInfo &lt;&lt; '\n';
            }
            stream &lt;&lt; getLineOfChars&lt;'.'&gt;() &lt;&lt; '\n' &lt;&lt; std::endl;
        }

        void printClosedHeader( std::string const&amp; _name ) {
            printOpenHeader( _name );
            stream &lt;&lt; getLineOfChars&lt;'.'&gt;() &lt;&lt; '\n';
        }
        void printOpenHeader( std::string const&amp; _name ) {
            stream  &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
            {
                Colour colourGuard( Colour::Headers );
                printHeaderString( _name );
            }
        }

        // if string has a : in first line will set indent to follow it on
        // subsequent lines
        void printHeaderString( std::string const&amp; _string, std::size_t indent = 0 ) {
            std::size_t i = _string.find( ": " );
            if( i != std::string::npos )
                i+=2;
            else
                i = 0;
            stream &lt;&lt; Column( _string ).indent( indent+i ).initialIndent( indent ) &lt;&lt; '\n';
        }

        struct SummaryColumn {

            SummaryColumn( std::string const&amp; _label, Colour::Code _colour )
            :   label( _label ),
                colour( _colour )
            {}
            SummaryColumn addRow( std::size_t count ) {
                std::ostringstream oss;
                oss &lt;&lt; count;
                std::string row = oss.str();
                for( auto&amp; oldRow : rows ) {
                    while( oldRow.size() &lt; row.size() )
                        oldRow = ' ' + oldRow;
                    while( oldRow.size() &gt; row.size() )
                        row = ' ' + row;
                }
                rows.push_back( row );
                return *this;
            }

            std::string label;
            Colour::Code colour;
            std::vector&lt;std::string&gt; rows;

        };

        void printTotals( Totals const&amp; totals ) {
            if( totals.testCases.total() == 0 ) {
                stream &lt;&lt; Colour( Colour::Warning ) &lt;&lt; "No tests ran\n";
            }
            else if( totals.assertions.total() &gt; 0 &amp;&amp; totals.testCases.allPassed() ) {
                stream &lt;&lt; Colour( Colour::ResultSuccess ) &lt;&lt; "All tests passed";
                stream &lt;&lt; " ("
                        &lt;&lt; pluralise( totals.assertions.passed, "assertion" ) &lt;&lt; " in "
                        &lt;&lt; pluralise( totals.testCases.passed, "test case" ) &lt;&lt; ')'
                        &lt;&lt; '\n';
            }
            else {

                std::vector&lt;SummaryColumn&gt; columns;
                columns.push_back( SummaryColumn( "", Colour::None )
                                        .addRow( totals.testCases.total() )
                                        .addRow( totals.assertions.total() ) );
                columns.push_back( SummaryColumn( "passed", Colour::Success )
                                        .addRow( totals.testCases.passed )
                                        .addRow( totals.assertions.passed ) );
                columns.push_back( SummaryColumn( "failed", Colour::ResultError )
                                        .addRow( totals.testCases.failed )
                                        .addRow( totals.assertions.failed ) );
                columns.push_back( SummaryColumn( "failed as expected", Colour::ResultExpectedFailure )
                                        .addRow( totals.testCases.failedButOk )
                                        .addRow( totals.assertions.failedButOk ) );

                printSummaryRow( "test cases", columns, 0 );
                printSummaryRow( "assertions", columns, 1 );
            }
        }
        void printSummaryRow( std::string const&amp; label, std::vector&lt;SummaryColumn&gt; const&amp; cols, std::size_t row ) {
            for( auto col : cols ) {
                std::string value = col.rows[row];
                if( col.label.empty() ) {
                    stream &lt;&lt; label &lt;&lt; ": ";
                    if( value != "0" )
                        stream &lt;&lt; value;
                    else
                        stream &lt;&lt; Colour( Colour::Warning ) &lt;&lt; "- none -";
                }
                else if( value != "0" ) {
                    stream  &lt;&lt; Colour( Colour::LightGrey ) &lt;&lt; " | ";
                    stream  &lt;&lt; Colour( col.colour )
                            &lt;&lt; value &lt;&lt; ' ' &lt;&lt; col.label;
                }
            }
            stream &lt;&lt; '\n';
        }

        void printTotalsDivider( Totals const&amp; totals ) {
            if( totals.testCases.total() &gt; 0 ) {
                std::size_t failedRatio = makeRatio( totals.testCases.failed, totals.testCases.total() );
                std::size_t failedButOkRatio = makeRatio( totals.testCases.failedButOk, totals.testCases.total() );
                std::size_t passedRatio = makeRatio( totals.testCases.passed, totals.testCases.total() );
                while( failedRatio + failedButOkRatio + passedRatio &lt; CATCH_CONFIG_CONSOLE_WIDTH-1 )
                    findMax( failedRatio, failedButOkRatio, passedRatio )++;
                while( failedRatio + failedButOkRatio + passedRatio &gt; CATCH_CONFIG_CONSOLE_WIDTH-1 )
                    findMax( failedRatio, failedButOkRatio, passedRatio )--;

                stream &lt;&lt; Colour( Colour::Error ) &lt;&lt; std::string( failedRatio, '=' );
                stream &lt;&lt; Colour( Colour::ResultExpectedFailure ) &lt;&lt; std::string( failedButOkRatio, '=' );
                if( totals.testCases.allPassed() )
                    stream &lt;&lt; Colour( Colour::ResultSuccess ) &lt;&lt; std::string( passedRatio, '=' );
                else
                    stream &lt;&lt; Colour( Colour::Success ) &lt;&lt; std::string( passedRatio, '=' );
            }
            else {
                stream &lt;&lt; Colour( Colour::Warning ) &lt;&lt; std::string( CATCH_CONFIG_CONSOLE_WIDTH-1, '=' );
            }
            stream &lt;&lt; '\n';
        }
        void printSummaryDivider() {
            stream &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
        }

    private:
        bool m_headerPrinted = false;
    };

    CATCH_REGISTER_REPORTER( "console", ConsoleReporter )

    ConsoleReporter::~ConsoleReporter() {}

} // end namespace Catch

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
// end catch_reporter_console.cpp
// start catch_reporter_junit.cpp

#include &lt;assert.h&gt;

#include &lt;ctime&gt;
#include &lt;algorithm&gt;

namespace Catch {

    namespace {
        std::string getCurrentTimestamp() {
            // Beware, this is not reentrant because of backward compatibility issues
            // Also, UTC only, again because of backward compatibility (%z is C++11)
            time_t rawtime;
            std::time(&amp;rawtime);
            auto const timeStampSize = sizeof("2017-01-16T17:06:45Z");

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&amp;timeInfo, &amp;rawtime);
#else
            std::tm* timeInfo;
            timeInfo = std::gmtime(&amp;rawtime);
#endif

            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &amp;timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }

        std::string fileNameTag(const std::vector&lt;std::string&gt; &amp;tags) {
            auto it = std::find_if(begin(tags),
                                   end(tags),
                                   [] (std::string const&amp; tag) {return tag.front() == '#'; });
            if (it != tags.end())
                return it-&gt;substr(1);
            return std::string();
        }
    }

    class JunitReporter : public CumulativeReporterBase&lt;JunitReporter&gt; {
    public:
        JunitReporter( ReporterConfig const&amp; _config )
        :   CumulativeReporterBase( _config ),
            xml( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = true;
        }

        ~JunitReporter() override;

        static std::string getDescription() {
            return "Reports test results in an XML format that looks like Ant's junitreport target";
        }

        void noMatchingTestCases( std::string const&amp; /*spec*/ ) override {}

        void testRunStarting( TestRunInfo const&amp; runInfo ) override {
            CumulativeReporterBase::testRunStarting( runInfo );
            xml.startElement( "testsuites" );
        }

        void testGroupStarting( GroupInfo const&amp; groupInfo ) override {
            suiteTimer.start();
            stdOutForSuite.str("");
            stdErrForSuite.str("");
            unexpectedExceptions = 0;
            CumulativeReporterBase::testGroupStarting( groupInfo );
        }

        void testCaseStarting( TestCaseInfo const&amp; testCaseInfo ) override {
            m_okToFail = testCaseInfo.okToFail();
        }
        bool assertionEnded( AssertionStats const&amp; assertionStats ) override {
            if( assertionStats.assertionResult.getResultType() == ResultWas::ThrewException &amp;&amp; !m_okToFail )
                unexpectedExceptions++;
            return CumulativeReporterBase::assertionEnded( assertionStats );
        }

        void testCaseEnded( TestCaseStats const&amp; testCaseStats ) override {
            stdOutForSuite &lt;&lt; testCaseStats.stdOut;
            stdErrForSuite &lt;&lt; testCaseStats.stdErr;
            CumulativeReporterBase::testCaseEnded( testCaseStats );
        }

        void testGroupEnded( TestGroupStats const&amp; testGroupStats ) override {
            double suiteTime = suiteTimer.getElapsedSeconds();
            CumulativeReporterBase::testGroupEnded( testGroupStats );
            writeGroup( *m_testGroups.back(), suiteTime );
        }

        void testRunEndedCumulative() override {
            xml.endElement();
        }

        void writeGroup( TestGroupNode const&amp; groupNode, double suiteTime ) {
            XmlWriter::ScopedElement e = xml.scopedElement( "testsuite" );
            TestGroupStats const&amp; stats = groupNode.value;
            xml.writeAttribute( "name", stats.groupInfo.name );
            xml.writeAttribute( "errors", unexpectedExceptions );
            xml.writeAttribute( "failures", stats.totals.assertions.failed-unexpectedExceptions );
            xml.writeAttribute( "tests", stats.totals.assertions.total() );
            xml.writeAttribute( "hostname", "tbd" ); // !TBD
            if( m_config-&gt;showDurations() == ShowDurations::Never )
                xml.writeAttribute( "time", "" );
            else
                xml.writeAttribute( "time", suiteTime );
            xml.writeAttribute( "timestamp", getCurrentTimestamp() );

            // Write test cases
            for( auto const&amp; child : groupNode.children )
                writeTestCase( *child );

            xml.scopedElement( "system-out" ).writeText( trim( stdOutForSuite.str() ), false );
            xml.scopedElement( "system-err" ).writeText( trim( stdErrForSuite.str() ), false );
        }

        void writeTestCase( TestCaseNode const&amp; testCaseNode ) {
            TestCaseStats const&amp; stats = testCaseNode.value;

            // All test cases have exactly one section - which represents the
            // test case itself. That section may have 0-n nested sections
            assert( testCaseNode.children.size() == 1 );
            SectionNode const&amp; rootSection = *testCaseNode.children.front();

            std::string className = stats.testInfo.className;

            if( className.empty() ) {
                className = fileNameTag(stats.testInfo.tags);
                if ( className.empty() )
                    className = "global";
            }

            if ( !m_config-&gt;name().empty() )
                className = m_config-&gt;name() + "." + className;

            writeSection( className, "", rootSection );
        }

        void writeSection(  std::string const&amp; className,
                            std::string const&amp; rootName,
                            SectionNode const&amp; sectionNode ) {
            std::string name = trim( sectionNode.stats.sectionInfo.name );
            if( !rootName.empty() )
                name = rootName + '/' + name;

            if( !sectionNode.assertions.empty() ||
                !sectionNode.stdOut.empty() ||
                !sectionNode.stdErr.empty() ) {
                XmlWriter::ScopedElement e = xml.scopedElement( "testcase" );
                if( className.empty() ) {
                    xml.writeAttribute( "classname", name );
                    xml.writeAttribute( "name", "root" );
                }
                else {
                    xml.writeAttribute( "classname", className );
                    xml.writeAttribute( "name", name );
                }
                xml.writeAttribute( "time", ::Catch::Detail::stringify( sectionNode.stats.durationInSeconds ) );

                writeAssertions( sectionNode );

                if( !sectionNode.stdOut.empty() )
                    xml.scopedElement( "system-out" ).writeText( trim( sectionNode.stdOut ), false );
                if( !sectionNode.stdErr.empty() )
                    xml.scopedElement( "system-err" ).writeText( trim( sectionNode.stdErr ), false );
            }
            for( auto const&amp; childNode : sectionNode.childSections )
                if( className.empty() )
                    writeSection( name, "", *childNode );
                else
                    writeSection( className, name, *childNode );
        }

        void writeAssertions( SectionNode const&amp; sectionNode ) {
            for( auto const&amp; assertion : sectionNode.assertions )
                writeAssertion( assertion );
        }
        void writeAssertion( AssertionStats const&amp; stats ) {
            AssertionResult const&amp; result = stats.assertionResult;
            if( !result.isOk() ) {
                std::string elementName;
                switch( result.getResultType() ) {
                    case ResultWas::ThrewException:
                    case ResultWas::FatalErrorCondition:
                        elementName = "error";
                        break;
                    case ResultWas::ExplicitFailure:
                        elementName = "failure";
                        break;
                    case ResultWas::ExpressionFailed:
                        elementName = "failure";
                        break;
                    case ResultWas::DidntThrowException:
                        elementName = "failure";
                        break;

                    // We should never see these here:
                    case ResultWas::Info:
                    case ResultWas::Warning:
                    case ResultWas::Ok:
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        elementName = "internalError";
                        break;
                }

                XmlWriter::ScopedElement e = xml.scopedElement( elementName );

                xml.writeAttribute( "message", result.getExpandedExpression() );
                xml.writeAttribute( "type", result.getTestMacroName() );

                std::ostringstream oss;
                if( !result.getMessage().empty() )
                    oss &lt;&lt; result.getMessage() &lt;&lt; '\n';
                for( auto const&amp; msg : stats.infoMessages )
                    if( msg.type == ResultWas::Info )
                        oss &lt;&lt; msg.message &lt;&lt; '\n';

                oss &lt;&lt; "at " &lt;&lt; result.getSourceInfo();
                xml.writeText( oss.str(), false );
            }
        }

        XmlWriter xml;
        Timer suiteTimer;
        std::ostringstream stdOutForSuite;
        std::ostringstream stdErrForSuite;
        unsigned int unexpectedExceptions = 0;
        bool m_okToFail = false;
    };

    JunitReporter::~JunitReporter() {}
    CATCH_REGISTER_REPORTER( "junit", JunitReporter )

} // end namespace Catch
// end catch_reporter_junit.cpp
// start catch_reporter_multi.cpp

namespace Catch {

    void MultipleReporters::add( IStreamingReporterPtr&amp;&amp; reporter ) {
        m_reporters.push_back( std::move( reporter ) );
    }

    ReporterPreferences MultipleReporters::getPreferences() const {
        return m_reporters[0]-&gt;getPreferences();
    }

    std::set&lt;Verbosity&gt; MultipleReporters::getSupportedVerbosities() {
        return std::set&lt;Verbosity&gt;{ };
    }

    void MultipleReporters::noMatchingTestCases( std::string const&amp; spec ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;noMatchingTestCases( spec );
    }

    void MultipleReporters::benchmarkStarting( BenchmarkInfo const&amp; benchmarkInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;benchmarkStarting( benchmarkInfo );
    }
    void MultipleReporters::benchmarkEnded( BenchmarkStats const&amp; benchmarkStats ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;benchmarkEnded( benchmarkStats );
    }

    void MultipleReporters::testRunStarting( TestRunInfo const&amp; testRunInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testRunStarting( testRunInfo );
    }

    void MultipleReporters::testGroupStarting( GroupInfo const&amp; groupInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testGroupStarting( groupInfo );
    }

    void MultipleReporters::testCaseStarting( TestCaseInfo const&amp; testInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testCaseStarting( testInfo );
    }

    void MultipleReporters::sectionStarting( SectionInfo const&amp; sectionInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;sectionStarting( sectionInfo );
    }

    void MultipleReporters::assertionStarting( AssertionInfo const&amp; assertionInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;assertionStarting( assertionInfo );
    }

    // The return value indicates if the messages buffer should be cleared:
    bool MultipleReporters::assertionEnded( AssertionStats const&amp; assertionStats ) {
        bool clearBuffer = false;
        for( auto const&amp; reporter : m_reporters )
            clearBuffer |= reporter-&gt;assertionEnded( assertionStats );
        return clearBuffer;
    }

    void MultipleReporters::sectionEnded( SectionStats const&amp; sectionStats ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;sectionEnded( sectionStats );
    }

    void MultipleReporters::testCaseEnded( TestCaseStats const&amp; testCaseStats ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testCaseEnded( testCaseStats );
    }

    void MultipleReporters::testGroupEnded( TestGroupStats const&amp; testGroupStats ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testGroupEnded( testGroupStats );
    }

    void MultipleReporters::testRunEnded( TestRunStats const&amp; testRunStats ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;testRunEnded( testRunStats );
    }

    void MultipleReporters::skipTest( TestCaseInfo const&amp; testInfo ) {
        for( auto const&amp; reporter : m_reporters )
            reporter-&gt;skipTest( testInfo );
    }

    bool MultipleReporters::isMulti() const {
        return true;
    }

} // end namespace Catch
// end catch_reporter_multi.cpp
// start catch_reporter_xml.cpp

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // Not all labels are EXPLICITLY handled in switch
                              // Note that 4062 (not all labels are handled
                              // and default is missing) is enabled
#endif

namespace Catch {
    class XmlReporter : public StreamingReporterBase&lt;XmlReporter&gt; {
    public:
        XmlReporter( ReporterConfig const&amp; _config )
        :   StreamingReporterBase( _config ),
            m_xml(_config.stream())
        {
            m_reporterPrefs.shouldRedirectStdOut = true;
        }

        ~XmlReporter() override;

        static std::string getDescription() {
            return "Reports test results as an XML document";
        }

        virtual std::string getStylesheetRef() const {
            return std::string();
        }

        void writeSourceInfo( SourceLineInfo const&amp; sourceInfo ) {
            m_xml
                .writeAttribute( "filename", sourceInfo.file )
                .writeAttribute( "line", sourceInfo.line );
        }

    public: // StreamingReporterBase

        void noMatchingTestCases( std::string const&amp; s ) override {
            StreamingReporterBase::noMatchingTestCases( s );
        }

        void testRunStarting( TestRunInfo const&amp; testInfo ) override {
            StreamingReporterBase::testRunStarting( testInfo );
            std::string stylesheetRef = getStylesheetRef();
            if( !stylesheetRef.empty() )
                m_xml.writeStylesheetRef( stylesheetRef );
            m_xml.startElement( "Catch" );
            if( !m_config-&gt;name().empty() )
                m_xml.writeAttribute( "name", m_config-&gt;name() );
        }

        void testGroupStarting( GroupInfo const&amp; groupInfo ) override {
            StreamingReporterBase::testGroupStarting( groupInfo );
            m_xml.startElement( "Group" )
                .writeAttribute( "name", groupInfo.name );
        }

        void testCaseStarting( TestCaseInfo const&amp; testInfo ) override {
            StreamingReporterBase::testCaseStarting(testInfo);
            m_xml.startElement( "TestCase" )
                .writeAttribute( "name", trim( testInfo.name ) )
                .writeAttribute( "description", testInfo.description )
                .writeAttribute( "tags", testInfo.tagsAsString() );

            writeSourceInfo( testInfo.lineInfo );

            if ( m_config-&gt;showDurations() == ShowDurations::Always )
                m_testCaseTimer.start();
            m_xml.ensureTagClosed();
        }

        void sectionStarting( SectionInfo const&amp; sectionInfo ) override {
            StreamingReporterBase::sectionStarting( sectionInfo );
            if( m_sectionDepth++ &gt; 0 ) {
                m_xml.startElement( "Section" )
                    .writeAttribute( "name", trim( sectionInfo.name ) )
                    .writeAttribute( "description", sectionInfo.description );
                writeSourceInfo( sectionInfo.lineInfo );
                m_xml.ensureTagClosed();
            }
        }

        void assertionStarting( AssertionInfo const&amp; ) override { }

        bool assertionEnded( AssertionStats const&amp; assertionStats ) override {

            AssertionResult const&amp; result = assertionStats.assertionResult;

            bool includeResults = m_config-&gt;includeSuccessfulResults() || !result.isOk();

            if( includeResults ) {
                // Print any info messages in &lt;Info&gt; tags.
                for( auto const&amp; msg : assertionStats.infoMessages ) {
                    if( msg.type == ResultWas::Info ) {
                        m_xml.scopedElement( "Info" )
                                .writeText( msg.message );
                    } else if ( msg.type == ResultWas::Warning ) {
                        m_xml.scopedElement( "Warning" )
                                .writeText( msg.message );
                    }
                }
            }

            // Drop out if result was successful but we're not printing them.
            if( !includeResults &amp;&amp; result.getResultType() != ResultWas::Warning )
                return true;

            // Print the expression if there is one.
            if( result.hasExpression() ) {
                m_xml.startElement( "Expression" )
                    .writeAttribute( "success", result.succeeded() )
                    .writeAttribute( "type", result.getTestMacroName() );

                writeSourceInfo( result.getSourceInfo() );

                m_xml.scopedElement( "Original" )
                    .writeText( result.getExpression() );
                m_xml.scopedElement( "Expanded" )
                    .writeText( result.getExpandedExpression() );
            }

            // And... Print a result applicable to each result type.
            switch( result.getResultType() ) {
                case ResultWas::ThrewException:
                    m_xml.startElement( "Exception" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                case ResultWas::FatalErrorCondition:
                    m_xml.startElement( "FatalErrorCondition" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                case ResultWas::Info:
                    m_xml.scopedElement( "Info" )
                        .writeText( result.getMessage() );
                    break;
                case ResultWas::Warning:
                    // Warning will already have been written
                    break;
                case ResultWas::ExplicitFailure:
                    m_xml.startElement( "Failure" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                default:
                    break;
            }

            if( result.hasExpression() )
                m_xml.endElement();

            return true;
        }

        void sectionEnded( SectionStats const&amp; sectionStats ) override {
            StreamingReporterBase::sectionEnded( sectionStats );
            if( --m_sectionDepth &gt; 0 ) {
                XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResults" );
                e.writeAttribute( "successes", sectionStats.assertions.passed );
                e.writeAttribute( "failures", sectionStats.assertions.failed );
                e.writeAttribute( "expectedFailures", sectionStats.assertions.failedButOk );

                if ( m_config-&gt;showDurations() == ShowDurations::Always )
                    e.writeAttribute( "durationInSeconds", sectionStats.durationInSeconds );

                m_xml.endElement();
            }
        }

        void testCaseEnded( TestCaseStats const&amp; testCaseStats ) override {
            StreamingReporterBase::testCaseEnded( testCaseStats );
            XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResult" );
            e.writeAttribute( "success", testCaseStats.totals.assertions.allOk() );

            if ( m_config-&gt;showDurations() == ShowDurations::Always )
                e.writeAttribute( "durationInSeconds", m_testCaseTimer.getElapsedSeconds() );

            if( !testCaseStats.stdOut.empty() )
                m_xml.scopedElement( "StdOut" ).writeText( trim( testCaseStats.stdOut ), false );
            if( !testCaseStats.stdErr.empty() )
                m_xml.scopedElement( "StdErr" ).writeText( trim( testCaseStats.stdErr ), false );

            m_xml.endElement();
        }

        void testGroupEnded( TestGroupStats const&amp; testGroupStats ) override {
            StreamingReporterBase::testGroupEnded( testGroupStats );
            // TODO: Check testGroupStats.aborting and act accordingly.
            m_xml.scopedElement( "OverallResults" )
                .writeAttribute( "successes", testGroupStats.totals.assertions.passed )
                .writeAttribute( "failures", testGroupStats.totals.assertions.failed )
                .writeAttribute( "expectedFailures", testGroupStats.totals.assertions.failedButOk );
            m_xml.endElement();
        }

        void testRunEnded( TestRunStats const&amp; testRunStats ) override {
            StreamingReporterBase::testRunEnded( testRunStats );
            m_xml.scopedElement( "OverallResults" )
                .writeAttribute( "successes", testRunStats.totals.assertions.passed )
                .writeAttribute( "failures", testRunStats.totals.assertions.failed )
                .writeAttribute( "expectedFailures", testRunStats.totals.assertions.failedButOk );
            m_xml.endElement();
        }

    private:
        Timer m_testCaseTimer;
        XmlWriter m_xml;
        int m_sectionDepth = 0;
    };

    XmlReporter::~XmlReporter() {}
    CATCH_REGISTER_REPORTER( "xml", XmlReporter )

} // end namespace Catch

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
// end catch_reporter_xml.cpp

namespace Catch {
    LeakDetector leakDetector;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_impl.hpp
#endif

#ifdef CATCH_CONFIG_MAIN
// start catch_default_main.hpp

#ifndef __OBJC__

#if defined(WIN32) &amp;&amp; defined(_UNICODE) &amp;&amp; !defined(DO_NOT_USE_WMAIN)
// Standard C/C++ Win32 Unicode wmain entry point
extern "C" int wmain (int argc, wchar_t * argv[], wchar_t * []) {
#else
// Standard C/C++ main entry point
int main (int argc, char * argv[]) {
#endif

    return Catch::Session().run( argc, argv );
}

#else // __OBJC__

// Objective-C entry point
int main (int argc, char * const argv[]) {
#if !CATCH_ARC_ENABLED
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#endif

    Catch::registerTestMethods();
    int result = Catch::Session().run( argc, (char**)argv );

#if !CATCH_ARC_ENABLED
    [pool drain];
#endif

    return result;
}

#endif // __OBJC__

// end catch_default_main.hpp
#endif

#ifdef CLARA_CONFIG_MAIN_NOT_DEFINED
#  undef CLARA_CONFIG_MAIN
#endif

#if !defined(CATCH_CONFIG_DISABLE)
//////
// If this config identifier is defined then all CATCH macros are prefixed with CATCH_
#ifdef CATCH_CONFIG_PREFIX_ALL

#define CATCH_REQUIRE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )

#define CATCH_REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "CATCH_REQUIRE_THROWS", Catch::ResultDisposition::Normal, "", __VA_ARGS__ )
#define CATCH_REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#define CATCH_REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif// CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CATCH_CHECK( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CATCH_CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CATCH_CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CATCH_CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CATCH_CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CATCH_CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, "", __VA_ARGS__ )
#define CATCH_CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#define CATCH_CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#define CATCH_REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define CATCH_INFO( msg ) INTERNAL_CATCH_INFO( "CATCH_INFO", msg )
#define CATCH_WARN( msg ) INTERNAL_CATCH_MSG( "CATCH_WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define CATCH_CAPTURE( msg ) INTERNAL_CATCH_INFO( "CATCH_CAPTURE", #msg " := " &lt;&lt; ::Catch::Detail::stringify(msg) )

#define CATCH_TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define CATCH_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define CATCH_REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define CATCH_SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define CATCH_FAIL( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_SUCCEED( ... ) INTERNAL_CATCH_MSG( "CATCH_SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#define CATCH_ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

// "BDD-style" convenience wrappers
#define CATCH_SCENARIO( ... ) CATCH_TEST_CASE( "Scenario: " __VA_ARGS__ )
#define CATCH_SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )
#define CATCH_GIVEN( desc )    CATCH_SECTION( std::string( "Given: ") + desc )
#define CATCH_WHEN( desc )     CATCH_SECTION( std::string( " When: ") + desc )
#define CATCH_AND_WHEN( desc ) CATCH_SECTION( std::string( "  And: ") + desc )
#define CATCH_THEN( desc )     CATCH_SECTION( std::string( " Then: ") + desc )
#define CATCH_AND_THEN( desc ) CATCH_SECTION( std::string( "  And: ") + desc )

// If CATCH_CONFIG_PREFIX_ALL is not defined then the CATCH_ prefix is not required
#else

#define REQUIRE( ... ) INTERNAL_CATCH_TEST( "REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__  )
#define REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )

#define REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "REQUIRE_THROWS", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#define REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CHECK( ... ) INTERNAL_CATCH_TEST( "CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#define CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#define REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define INFO( msg ) INTERNAL_CATCH_INFO( "INFO", msg )
#define WARN( msg ) INTERNAL_CATCH_MSG( "WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define CAPTURE( msg ) INTERNAL_CATCH_INFO( "CAPTURE", #msg " := " &lt;&lt; ::Catch::Detail::stringify(msg) )

#define TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define FAIL( ... ) INTERNAL_CATCH_MSG( "FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define SUCCEED( ... ) INTERNAL_CATCH_MSG( "SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

#endif

#define CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature )

// "BDD-style" convenience wrappers
#define SCENARIO( ... ) TEST_CASE( "Scenario: " __VA_ARGS__ )
#define SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )

#define GIVEN( desc )    SECTION( std::string("   Given: ") + desc )
#define WHEN( desc )     SECTION( std::string("    When: ") + desc )
#define AND_WHEN( desc ) SECTION( std::string("And when: ") + desc )
#define THEN( desc )     SECTION( std::string("    Then: ") + desc )
#define AND_THEN( desc ) SECTION( std::string("     And: ") + desc )

using Catch::Detail::Approx;

#else
//////
// If this config identifier is defined then all CATCH macros are prefixed with CATCH_
#ifdef CATCH_CONFIG_PREFIX_ALL

#define CATCH_REQUIRE( ... )        (void)(0)
#define CATCH_REQUIRE_FALSE( ... )  (void)(0)

#define CATCH_REQUIRE_THROWS( ... ) (void)(0)
#define CATCH_REQUIRE_THROWS_AS( expr, exceptionType ) (void)(0)
#define CATCH_REQUIRE_THROWS_WITH( expr, matcher )     (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif// CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_REQUIRE_NOTHROW( ... ) (void)(0)

#define CATCH_CHECK( ... )         (void)(0)
#define CATCH_CHECK_FALSE( ... )   (void)(0)
#define CATCH_CHECKED_IF( ... )    if (__VA_ARGS__)
#define CATCH_CHECKED_ELSE( ... )  if (!(__VA_ARGS__))
#define CATCH_CHECK_NOFAIL( ... )  (void)(0)

#define CATCH_CHECK_THROWS( ... )  (void)(0)
#define CATCH_CHECK_THROWS_AS( expr, exceptionType ) (void)(0)
#define CATCH_CHECK_THROWS_WITH( expr, matcher )     (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_CHECK_NOTHROW( ... ) (void)(0)

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THAT( arg, matcher )   (void)(0)

#define CATCH_REQUIRE_THAT( arg, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define CATCH_INFO( msg )    (void)(0)
#define CATCH_WARN( msg )    (void)(0)
#define CATCH_CAPTURE( msg ) (void)(0)

#define CATCH_TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_METHOD_AS_TEST_CASE( method, ... )
#define CATCH_REGISTER_TEST_CASE( Function, ... ) (void)(0)
#define CATCH_SECTION( ... )
#define CATCH_FAIL( ... ) (void)(0)
#define CATCH_FAIL_CHECK( ... ) (void)(0)
#define CATCH_SUCCEED( ... ) (void)(0)

#define CATCH_ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))

// "BDD-style" convenience wrappers
#define CATCH_SCENARIO( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), className )
#define CATCH_GIVEN( desc )
#define CATCH_WHEN( desc )
#define CATCH_AND_WHEN( desc )
#define CATCH_THEN( desc )
#define CATCH_AND_THEN( desc )

// If CATCH_CONFIG_PREFIX_ALL is not defined then the CATCH_ prefix is not required
#else

#define REQUIRE( ... )       (void)(0)
#define REQUIRE_FALSE( ... ) (void)(0)

#define REQUIRE_THROWS( ... ) (void)(0)
#define REQUIRE_THROWS_AS( expr, exceptionType ) (void)(0)
#define REQUIRE_THROWS_WITH( expr, matcher ) (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define REQUIRE_NOTHROW( ... ) (void)(0)

#define CHECK( ... ) (void)(0)
#define CHECK_FALSE( ... ) (void)(0)
#define CHECKED_IF( ... ) if (__VA_ARGS__)
#define CHECKED_ELSE( ... ) if (!(__VA_ARGS__))
#define CHECK_NOFAIL( ... ) (void)(0)

#define CHECK_THROWS( ... )  (void)(0)
#define CHECK_THROWS_AS( expr, exceptionType ) (void)(0)
#define CHECK_THROWS_WITH( expr, matcher ) (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CHECK_NOTHROW( ... ) (void)(0)

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THAT( arg, matcher ) (void)(0)

#define REQUIRE_THAT( arg, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define INFO( msg ) (void)(0)
#define WARN( msg ) (void)(0)
#define CAPTURE( msg ) (void)(0)

#define TEST_CASE( ... )  INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define METHOD_AS_TEST_CASE( method, ... )
#define REGISTER_TEST_CASE( Function, ... ) (void)(0)
#define SECTION( ... )
#define FAIL( ... ) (void)(0)
#define FAIL_CHECK( ... ) (void)(0)
#define SUCCEED( ... ) (void)(0)
#define ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))

#endif

#define CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION_NO_REG( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// "BDD-style" convenience wrappers
#define SCENARIO( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ) )
#define SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), className )

#define GIVEN( desc )
#define WHEN( desc )
#define AND_WHEN( desc )
#define THEN( desc )
#define AND_THEN( desc )

using Catch::Detail::Approx;

#endif

// start catch_reenable_warnings.h


#ifdef __clang__
#    ifdef __ICC // icpc defines the __clang__ macro
#        pragma warning(pop)
#    else
#        pragma clang diagnostic pop
#    endif
#elif defined __GNUC__
#    pragma GCC diagnostic pop
#endif

// end catch_reenable_warnings.h
// end catch.hpp
#endif // TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
