//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once
#include <iostream>
#include <array>
#include <cstdint>
#include <random>
#include <limits>

namespace owl
{
  namespace utils
  {
    struct uuid
    {
    public:
      using container_type = std::array<std::uint8_t, 16>;
      using value_type = container_type::value_type;
      using reference = container_type::reference;
      using const_reference = container_type::const_reference;
      using iterator = container_type::iterator;
      using const_iterator = container_type::const_iterator;
      using size_type = container_type::size_type;
      using difference_type = container_type::difference_type;
      
      iterator begin() noexcept { return data.begin(); }
      const_iterator begin() const noexcept { return data.cbegin(); }
      iterator end() noexcept { return data.end(); }
      const_iterator end() const noexcept { return data.cend(); }
      
      constexpr size_type size() const noexcept { return data.size(); }
      
      bool is_nil() const noexcept
      {
        for (std::size_t i = 0; i < sizeof(data); ++i)
        {
          if (data[i] != 0U)
            return false;
        }
        return true;
      }
      
      bool operator==(uuid const& other) noexcept
      {
        return data == other.data;
      }
      
      bool operator!=( uuid const& other) noexcept
      {
        return data != other.data;
      }
      
      bool operator<( uuid const& other) noexcept
      {
        return data < other.data;
      }
      
      bool operator>(uuid const& other) noexcept
      {
        return data > other.data;
      }
      
      bool operator<=(uuid const& other) noexcept
      {
        return data <= other.data;
      }
      
      bool operator>=(uuid const& other) noexcept
      {
        return data >= data;
      }
      
      enum variant_type
      {
        variant_ncs, // NCS backward compatibility
        variant_rfc_4122, // defined in RFC 4122 document
        variant_microsoft, // Microsoft Corporation backward compatibility
        variant_future // future definition
      };
      
      variant_type variant() const noexcept
      {
        // variant is stored in octet 7
        // which is index 8, since indexes count backwards
        std::uint8_t octet7 = data[8]; // octet 7 is array index 8
        if ( (octet7 & 0x80) == 0x00 )
        { // 0b0xxxxxxx
          return variant_ncs;
        }
        else if ( (octet7 & 0xC0) == 0x80 )
        { // 0b10xxxxxx
          return variant_rfc_4122;
        }
        else if ( (octet7 & 0xE0) == 0xC0 )
        { // 0b110xxxxx
          return variant_microsoft;
        }
        else
        {
          return variant_future;
        }
      }
      
      enum version_type
      {
        version_unknown = -1,
        version_time_based = 1,
        version_dce_security = 2,
        version_name_based_md5 = 3,
        version_random_number_based = 4,
        version_name_based_sha1 = 5
      };
      
      version_type version() const noexcept
      {
        // version is stored in octet 9
        // which is index 6, since indexes count backwards
        std::uint8_t octet9 = data[6];
        if ( (octet9 & 0xF0) == 0x10 )
        {
          return version_time_based;
        }
        else if ( (octet9 & 0xF0) == 0x20 )
        {
          return version_dce_security;
        }
        else if ( (octet9 & 0xF0) == 0x30 )
        {
          return version_name_based_md5;
        }
        else if ( (octet9 & 0xF0) == 0x40 )
        {
          return version_random_number_based;
        }
        else if ( (octet9 & 0xF0) == 0x50 )
        {
          return version_name_based_sha1;
        }
        else
        {
          return version_unknown;
        }
      }
      
      union
      {
        struct
        {
          std::uint32_t data1;
          std::uint16_t data2;
          std::uint16_t data3;
          std::uint8_t  data4[8];
        };
        std::array<std::uint8_t,16> data;
      };
    };
    
    inline std::size_t hash_value(uuid const& u) noexcept
    {
      std::size_t seed = 0;
      for(uuid::const_iterator i=u.begin(), e=u.end(); i != e; ++i)
      {
        seed ^= static_cast<std::size_t>(*i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      
      return seed;
    }
   
    class ios_flags_saver
    {
    public:
      typedef ::std::ios_base            state_type;
      typedef ::std::ios_base::fmtflags  aspect_type;
      
      explicit  ios_flags_saver( state_type &s )
      : s_save_( s ), a_save_( s.flags() )
      {}
      ios_flags_saver( state_type &s, aspect_type const &a )
      : s_save_( s ), a_save_( s.flags(a) )
      {}
      ~ios_flags_saver()
      { this->restore(); }
      
      void  restore()
      { s_save_.flags( a_save_ ); }
      
    private:
      state_type &       s_save_;
      aspect_type const  a_save_;
      
      ios_flags_saver& operator=(const ios_flags_saver&);
    };
    
    template < typename Ch, class Tr >
    class basic_ios_fill_saver
    {
    public:
      typedef ::std::basic_ios<Ch, Tr>        state_type;
      typedef typename state_type::char_type  aspect_type;
      
      explicit  basic_ios_fill_saver( state_type &s )
      : s_save_( s ), a_save_( s.fill() )
      {}
      basic_ios_fill_saver( state_type &s, aspect_type const &a )
      : s_save_( s ), a_save_( s.fill(a) )
      {}
      ~basic_ios_fill_saver()
      { this->restore(); }
      
      void  restore()
      { s_save_.fill( a_save_ ); }
      
    private:
      state_type &       s_save_;
      aspect_type const  a_save_;
      basic_ios_fill_saver& operator=(const basic_ios_fill_saver&);
    };
    
    template <typename ch, typename char_traits>
    std::basic_ostream<ch, char_traits>& operator<<(std::basic_ostream<ch, char_traits> &os, uuid const& u)
    {
      ios_flags_saver flags_saver(os);
      basic_ios_fill_saver<ch, char_traits> fill_saver(os);
      
      const typename std::basic_ostream<ch, char_traits>::sentry ok(os);
      if (ok) {
        const std::streamsize width = os.width(0);
        const std::streamsize uuid_width = 36;
        const std::ios_base::fmtflags flags = os.flags();
        const typename std::basic_ios<ch, char_traits>::char_type fill = os.fill();
        if (flags & (std::ios_base::right | std::ios_base::internal)) {
          for (std::streamsize i=uuid_width; i<width; i++) {
            os << fill;
          }
        }
        
        os << std::hex;
        os.fill(os.widen('0'));
        
        std::size_t i=0;
        for (uuid::const_iterator i_data = u.begin(); i_data!=u.end(); ++i_data, ++i) {
          os.width(2);
          os << static_cast<unsigned int>(*i_data);
          if (i == 3 || i == 5 || i == 7 || i == 9) {
            os << os.widen('-');
          }
        }
        
        if (flags & std::ios_base::left) {
          for (std::streamsize i=uuid_width; i<width; i++) {
            os << fill;
          }
        }
        
        os.width(0); //used the width so reset it
      }
      return os;
    }
    
    template <typename ch, typename char_traits>
    std::basic_istream<ch, char_traits>& operator>>(std::basic_istream<ch, char_traits> &is, uuid &u)
    {
      const typename std::basic_istream<ch, char_traits>::sentry ok(is);
      if (ok) {
        unsigned char data[16];
        
        typedef std::ctype<ch> ctype_t;
        ctype_t const& ctype = std::use_facet<ctype_t>(is.getloc());
        
        ch xdigits[16];
        {
          char szdigits[] = "0123456789ABCDEF";
          ctype.widen(szdigits, szdigits+16, xdigits);
        }
        ch*const xdigits_end = xdigits+16;
        
        ch c;
        for (std::size_t i=0; i<u.size() && is; ++i) {
          is >> c;
          c = ctype.toupper(c);
          
          ch* f = std::find(xdigits, xdigits_end, c);
          if (f == xdigits_end) {
            is.setstate(std::ios_base::failbit);
            break;
          }
          
          unsigned char byte = static_cast<unsigned char>(std::distance(&xdigits[0], f));
          
          is >> c;
          c = ctype.toupper(c);
          f = std::find(xdigits, xdigits_end, c);
          if (f == xdigits_end) {
            is.setstate(std::ios_base::failbit);
            break;
          }
          
          byte <<= 4;
          byte |= static_cast<unsigned char>(std::distance(&xdigits[0], f));
          
          data[i] = byte;
          
          if (is) {
            if (i == 3 || i == 5 || i == 7 || i == 9) {
              is >> c;
              if (c != is.widen('-')) is.setstate(std::ios_base::failbit);
            }
          }
        }
        
        if (is) {
          std::copy(data, data+16, u.begin());
        }
      }
      return is;
    }
    
    namespace detail {
      inline char to_char(size_t i) {
        if (i <= 9) {
          return static_cast<char>('0' + i);
        } else {
          return static_cast<char>('a' + (i-10));
        }
      }
      
      inline wchar_t to_wchar(size_t i) {
        if (i <= 9) {
          return static_cast<wchar_t>(L'0' + i);
        } else {
          return static_cast<wchar_t>(L'a' + (i-10));
        }
      }
      
    } // namespace detail
    
    inline std::string to_string(uuid const& u)
    {
      std::string result;
      result.reserve(36);
      
      std::size_t i=0;
      for (uuid::const_iterator it_data = u.begin(); it_data!=u.end(); ++it_data, ++i) {
        const size_t hi = ((*it_data) >> 4) & 0x0F;
        result += detail::to_char(hi);
        
        const size_t lo = (*it_data) & 0x0F;
        result += detail::to_char(lo);
        
        if (i == 3 || i == 5 || i == 7 || i == 9) {
          result += '-';
        }
      }
      return result;
    }
    

    inline std::wstring to_wstring(uuid const& u)
    {
      std::wstring result;
      result.reserve(36);
      
      std::size_t i=0;
      for (uuid::const_iterator it_data = u.begin(); it_data!=u.end(); ++it_data, ++i)
      {
        const size_t hi = ((*it_data) >> 4) & 0x0F;
        result += detail::to_wchar(hi);
        
        const size_t lo = (*it_data) & 0x0F;
        result += detail::to_wchar(lo);
        
        if (i == 3 || i == 5 || i == 7 || i == 9) {
          result += L'-';
        }
      }
      return result;
    }
    
    inline uuid random_uuid()
    {
      uuid u;
      
      int i=0;
      using Engine = std::mt19937;
      using Distribution = std::uniform_int_distribution<unsigned int>;
    
     
      
        static auto generator = std::bind(Distribution(std::numeric_limits<unsigned int>::min()
                                       , std::numeric_limits<unsigned int>::max()),
            Engine((unsigned int)time(NULL)));
      unsigned long random_value = generator();
      for (uuid::iterator it=u.begin(); it!=u.end(); ++it, ++i) {
        if (i==sizeof(unsigned long)) {
          random_value = generator();
          i = 0;
        }
        
        // static_cast gets rid of warnings of converting unsigned long to boost::uint8_t
        *it = static_cast<uuid::value_type>((random_value >> (i*8)) & 0xFF);
      }
      
      // set variant
      // must be 0b10xxxxxx
      *(u.begin()+8) &= 0xBF;
      *(u.begin()+8) |= 0x80;
      
      // set version
      // must be 0b0100xxxx
      *(u.begin()+6) &= 0x4F; //0b01001111
      *(u.begin()+6) |= 0x40; //0b01000000
      
      return u;
    }
    

   
  }
}
