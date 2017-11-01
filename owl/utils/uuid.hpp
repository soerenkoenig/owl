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

#include "owl/utils/hash_utils.hpp"

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
      
      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      iterator end() noexcept;
      const_iterator end() const noexcept;
      
      constexpr size_type size() noexcept;
      
      bool is_nil() const noexcept;
      
      bool operator==(uuid const& other) noexcept;
      
      bool operator!=( uuid const& other) noexcept;
      
      bool operator<( uuid const& other) noexcept;
      
      bool operator>(uuid const& other) noexcept;
      
      bool operator<=(uuid const& other) noexcept;
      
      bool operator>=(uuid const& other) noexcept;
      
      enum variant_type
      {
        variant_ncs, // NCS backward compatibility
        variant_rfc_4122, // defined in RFC 4122 document
        variant_microsoft, // Microsoft Corporation backward compatibility
        variant_future // future definition
      };
      
      variant_type variant() const noexcept;
      
      enum version_type
      {
        version_unknown = -1,
        version_time_based = 1,
        version_dce_security = 2,
        version_name_based_md5 = 3,
        version_random_number_based = 4,
        version_name_based_sha1 = 5
      };
      
      version_type version() const noexcept;
      
      std::array<std::uint8_t,16> data;
    };
    
    
   
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
        
        if (is)
        {
          std::copy(data, data+16, u.begin());
        }
      }
      return is;
    }
    
    std::string to_string(uuid const& u);
    
    std::wstring to_wstring(uuid const& u);
   
    uuid random_uuid();
  }
}

namespace std
{
  
  //provide std::hash specialication for std::pair types by combining hashes of first and second
 template<>
  struct hash<owl::utils::uuid>
  {
    std::size_t operator()(const owl::utils::uuid& value) const
    {
      return owl::utils::hash_value(value.begin(), value.end());
    }
  };
}
