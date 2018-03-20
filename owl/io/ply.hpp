//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2018 Sören König. All rights reserved.
//

#pragma once

#include <memory>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "owl/math/mesh.hpp"
#include "owl/color/color.hpp"

namespace owl
{
  namespace io
  {
    class ply_reader
    {
    public:
    
      ply_reader();
  
      ply_reader(const boost::filesystem::path& filename);
  
      void open(const boost::filesystem::path& filename);
  
      bool is_open() const;
  
      bool listen_2_element_begin(std::function<void(const std::string&, std::size_t)> fn);
  
      bool listen_2_element_end(std::function<void(const std::string&)> fn);
  
      bool listen_2_element_item_begin(const std::string& element_name,
        std::function<void(const std::size_t i)> fn);
      bool listen_2_element_item_end(const std::string& element_name,
        std::function<void(const std::size_t i)> fn);
  
      bool listen_2_comments(std::function<void(const std::string&)> fn);
  
      template <typename T>
      bool listen_2_element_property(const std::string& element_name,
        const std::string& property_name, std::function<void(const T& v)> fn);
      template <typename T>
      bool listen_2_element_property(const std::string& element_name,
        const std::string& property_name, std::function<void(const std::vector<T>& v)> fn);
  
      bool read();
  
      void close();
    
    private:
      struct ply_property
      {
        std::string name;
    
        virtual std::istream& read_ascii(std::istream& in) = 0;
    
        virtual std::istream& read_binary(std::istream& in, bool swap_endianess) = 0;
    
        ply_property(const std::string& name);
      };
  
      template <typename T>
      struct scalar_property: public ply_property
      {
        std::function<void(const T&)> on_read;
    
        scalar_property(const std::string& name);
    
        std::istream& read_ascii(std::istream& in);
    
        std::istream&  read_binary(std::istream& in, bool swap_endianess);
      };
    
    
      template <typename C, typename T>
      struct list_property: ply_property
      {
        std::function<void(const std::vector<T>&)> on_read;
    
        list_property(const std::string& name);
    
        std::istream& read_ascii(std::istream& in);
    
        std::istream& read_binary(std::istream& in, bool swap_endianess);
      };
    
      struct element
      {
        std::string name;
        std::size_t count;
    
        std::vector<std::shared_ptr<ply_property>> properties;
    
        std::function<void(const std::size_t& i)> on_begin, on_end;
    
        element();
    
        element(const std::string& name, std::size_t count);
    
        template <typename T>
        bool listen(const std::string& property_name, std::function<void(const T& v)> fn);
    
        template <typename T>
        bool listen(const std::string& property_name, std::function<void(const std::vector<T>& v)> fn);
    
        std::shared_ptr<ply_property> get_property(const std::string& name);
    
        std::istream& read_ascii(std::istream& in);
    
        std::istream& read_binary(std::istream& in, bool swap_endianess);
      };
  
      //get element by name returning an optional element
      element* get_element(const std::string& name);
  
      std::istream& read_header(std::istream& in);
  
      std::istream& read_data(std::istream& in);
  
      std::istream& read_magic(std::istream& in);
  
      std::istream& read_comment(std::istream& in);
  
      std::istream& read_format(std::istream& in);
  
      std::istream& read_element(std::istream& in);
  
      std::istream& read_property(std::istream& in);
  
      bool add_scalar_property(const std::string& value_type, const std::string& name);
  
      template <typename C>
      bool add_list_property( const std::string& value_type, const std::string& name);
  
      bool add_list_property(const std::string& size_type,
        const std::string& value_type, const std::string& name);
  
      bool header_complete;
  
      bool format_complete;
  
      std::string version;
  
      enum class encoding_type
      {
        ascii,
        binary_little_endian,
        binary_big_endian
      } file_encoding;
  
      std::vector<element> elements;
      std::vector<std::string> comments;
  
      std::function<void(const std::string&)> on_comment;
  
      std::function<void(const std::string&, std::size_t)> on_element_begin;
  
      std::function<void(const std::string&)> on_element_end;
  
      boost::filesystem::ifstream file;
    };
  
    namespace detail
    {
      template <typename T>
      std::istream& read_ascii(std::istream& in, T& v)
      {
        in >> v;
        return in;
      }
    
      template <>
      inline std::istream& read_ascii<std::uint8_t>(std::istream& in, std::uint8_t& v);
    } 
  
    template <typename T>
    ply_reader::scalar_property<T>::scalar_property(const std::string& name)
      : ply_property(name)
    {}
  
    template <typename T>
    std::istream& ply_reader::scalar_property<T>::read_ascii(std::istream& in)
    {
      T value;
      if(io::detail::read_ascii(in,value))
      {
        if(on_read)
          on_read(value);
      }
      return in;
    }
  
    template <typename T>
    std::istream&  ply_reader::scalar_property<T>::read_binary(std::istream& in,
      bool swap_endianess)
    {
      T value;
      in.read((char*)&value, sizeof(T));
      if(in && swap_endianess)
      {
        if(swap_endianess)
        {
          unsigned char *memp = reinterpret_cast<unsigned char*>(&value);
          std::size_t n = sizeof(T);
          std::reverse(memp, memp + n);
        }
      }
      if(in && on_read)
        on_read(value);
  
      return in;
    }
  
    template <typename C, typename T>
    ply_reader::list_property<C,T>::list_property(const std::string& name)
      : ply_property(name)
    {}
  
    template <typename C, typename T>
    std::istream& ply_reader::list_property<C,T>::read_ascii(std::istream& in)
    {
      C n;
      std::vector<T> values;
  
      if(!io::detail::read_ascii(in, n))
        return in;
      values.resize(n);
  
      for(auto&v: values )
        if(!io::detail::read_ascii(in, v))
          break;
      if(in && on_read)
        on_read(values);
  
      return in;
    }
  
    template <typename C, typename T>
    std::istream& ply_reader::list_property<C,T>::read_binary(std::istream& in,bool swap_endianess)
    {
      C n;
      std::vector<T> values;
      //read count
      in.read((char*)&n,sizeof(C));
    
      if(in && swap_endianess)
      {
        unsigned char *memp = reinterpret_cast<unsigned char*>(&n);
        std::reverse(memp, memp + sizeof(C));
      }
      values.resize((typename std::vector<T>::size_type)n);
  
      in.read((char*)values.data(),sizeof(T)*n);
      swap_endianess = true;
      if(in && swap_endianess)
      {
        for(T& v: values)
        {
          unsigned char *memp = reinterpret_cast<unsigned char*>(&v);
          std::reverse(memp, memp + sizeof(T));
        }
      }
      if(in && on_read)
        on_read(values);
      
      return in;
    }
  
    template <typename T>
    bool ply_reader::element::listen(const std::string& property_name,
      std::function<void(const T& v)> fn)
    {
      std::shared_ptr<ply_property> p = get_property(property_name);
      if(!p)
        return false;
      std::shared_ptr<scalar_property<T>>sp = std::dynamic_pointer_cast<scalar_property<T>>(p);
      if(!sp)
        return false;
      sp->on_read = std::move(fn);
      return true;
    }
  
    template <typename T>
    bool ply_reader::element::listen(const std::string& property_name,
      std::function<void(const std::vector<T>& v)> fn)
    {
      std::shared_ptr<ply_property> p = get_property(property_name);
      if(!p)
        return false;
  
      std::shared_ptr<list_property<std::uint8_t,T>> sp1 = std::dynamic_pointer_cast<list_property<std::uint8_t,T>>(p);
      if(sp1)
      {
        sp1->on_read = std::move(fn);
        return true;
      }
      std::shared_ptr<list_property<std::int8_t,T>> sp2 = std::dynamic_pointer_cast<list_property<std::int8_t,T>>(p);
      if(sp2)
      {
        sp2->on_read = std::move(fn);
        return true;
      }
      std::shared_ptr<list_property<std::uint16_t,T>> sp3 = std::dynamic_pointer_cast<list_property<std::uint16_t,T>>(p);
      if(sp3)
      {
        sp3->on_read = std::move(fn);
        return true;
      }
      std::shared_ptr<list_property<std::int16_t,T>> sp4 = std::dynamic_pointer_cast<list_property<std::int16_t,T>>(p);
      if(sp4)
      {
        sp4->on_read = std::move(fn);
        return true;
      }
      std::shared_ptr<list_property<std::uint32_t,T>> sp5 = std::dynamic_pointer_cast<list_property<std::uint32_t,T>>(p);
      if(sp5)
      {
        sp5->on_read = std::move(fn);
        return true;
      }
      std::shared_ptr<list_property<std::int32_t,T>> sp6 = std::dynamic_pointer_cast<list_property<std::int32_t,T>>(p);
      if(sp6)
      {
        sp6->on_read = std::move(fn);
        return true;
      }
      return false;
    }
  
    template <typename T>
    bool ply_reader::listen_2_element_property(const std::string& element_name,
      const std::string& property_name, std::function<void(const T& v)> fn)
    {
      if(!header_complete)
        return false;
      auto e = get_element(element_name);
      if(!e)
        return false;
  
      return e->listen(property_name, std::move(fn));
    }
  
    template <typename T>
    bool ply_reader::listen_2_element_property(const std::string& element_name,
      const std::string& property_name, std::function<void(const std::vector<T>& v)> fn)
    {
      if(!header_complete)
        return false;
      auto e = get_element(element_name);
      if(!e)
        return false;
  
      return e->listen(property_name,std::move(fn));
    }
  
    template <typename C>
    bool ply_reader::add_list_property( const std::string& value_type, const std::string& name)
    {
      if(elements.empty())
        return false;
  
      if(value_type == "float" || value_type == "float32")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,float>>(name));
        return true;
      }
      if(value_type == "double" || value_type == "float64")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,double>>(name));;
        return true;
      }
      if(value_type == "uint8" || value_type == "uchar")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::uint8_t>>(name));
        return true;
      }
      if(value_type == "int8" || value_type == "char")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::int8_t>>(name));
        return true;
      }
      if(value_type == "uint16" || value_type == "ushort")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::uint16_t>>(name));
        return true;
      }
      if(value_type == "int16" || value_type == "short")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::int16_t>>(name));
        return true;
      }
      if(value_type == "uint32" || value_type == "uint")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::uint32_t>>(name));
        return true;
      }
      if(value_type == "int32" || value_type == "int")
      {
        elements.back().properties.push_back(std::make_shared<list_property<C,std::int32_t>>(name));;
        return true;
      }
      return false;
    }
  
    template <typename Scalar>
    bool read_ply(math::mesh<Scalar>& mesh, const boost::filesystem::path& p)
    {
      if(!exists(p))
        return false;
    
      if(!is_regular_file(p))
        return false;
    
      mesh.clear();
    
      ply_reader my_ply;
    
      my_ply.open(p.string());
      if(!my_ply.is_open())
        return false;
  
      std::vector<math::vector<Scalar,3>> positions;
      std::vector<math::vector<Scalar,3>> normals;
  
      math::vector<Scalar,3> pos, nml;
      color::rgba8u col, back_col;
      std::int32_t material_idx;
    
      my_ply.listen_2_element_begin(
        [&](const std::string& element_name, std::size_t n)
        {
          if(element_name == "vertex")
            mesh.reserve_vertices(n);
          if(element_name == "face")
            mesh.reserve_faces(n);
          if(element_name == "edge")
            return;
          if(element_name == "material")
            return;
        });
  
      my_ply.listen_2_element_property<float>("vertex", "x",
        [&pos](const float& x){ pos.x() = x;} );
      my_ply.listen_2_element_property<float>("vertex", "y",
        [&pos](const float& y){ pos.y() = y; });
      my_ply.listen_2_element_property<float>("vertex", "z",
        [&pos](const float& z){ pos.z() = z; });
    
      my_ply.listen_2_element_property<float>("vertex", "nx",
        [&nml](const float& nx){ nml.x() = nx; });
      my_ply.listen_2_element_property<float>("vertex", "ny",
        [&nml](const float& ny){ nml.y() = ny; });
      my_ply.listen_2_element_property<float>("vertex", "nz",
        [&nml](const float& nz){ nml.z() = nz; });
    
      my_ply.listen_2_element_property<std::uint8_t>("vertex", "red",
        [&col](const std::uint8_t& red){ col.r() = red; });
      my_ply.listen_2_element_property<std::uint8_t>("vertex", "green",
        [&col](const std::uint8_t& green){ col.g() = green; });
      my_ply.listen_2_element_property<std::uint8_t>("vertex", "blue",
        [&col](const std::uint8_t& blue){ col.b() = blue; });
      my_ply.listen_2_element_property<std::uint8_t>("vertex", "alpha",
        [&col](const std::uint8_t& alpha){ col.a() = alpha; });
    
      my_ply.listen_2_element_property<std::uint8_t>("face", "back_red",
        [&back_col](const std::uint8_t& red){ back_col.r() = red; });
      my_ply.listen_2_element_property<std::uint8_t>("face", "back_green",
        [&back_col](const std::uint8_t& green){ back_col.g() = green; });
      my_ply.listen_2_element_property<std::uint8_t>("face", "back_blue",
        [&back_col](const std::uint8_t& blue){ back_col.b() = blue; });
      my_ply.listen_2_element_property<int>("face", "vertex_indices",
        [&](const std::vector<int>& vindices)
        {
          std::vector<math::vertex_handle> vertex_indices;
          for(auto v: vindices)
            vertex_indices.push_back(math::vertex_handle(v));
          mesh.add_face(vertex_indices);
        });
    
      my_ply.listen_2_element_property<std::int32_t>("vertex", "material_index",
        [&material_idx](const std::int32_t& id){ material_idx = id; });
  
      my_ply.listen_2_element_item_end("vertex",
        [&](std::size_t i){ mesh.add_vertex(pos); });
    
      my_ply.listen_2_element_property<std::int32_t>("edge", "vertex1",
        [](const std::int32_t& i){ std::cout << " vertex1 = " << i; });
      my_ply.listen_2_element_property<std::int32_t>("edge", "vertex2",
        [](const std::int32_t& i){ std::cout << " vertex2 = " << i; });
      my_ply.listen_2_element_property<std::uint8_t>("edge", "crease_tag",
        [](const std::uint8_t& i){ std::cout << " create_tag = " << (int)i; });
    
      my_ply.listen_2_element_property<std::uint8_t>("material", "red",
        [](const std::uint8_t& r){ std::cout << " color = " << (int)r <<" "; });
      my_ply.listen_2_element_property<std::uint8_t>("material", "green",
        [](const std::uint8_t& g){ std::cout << (int)g <<" "; });
      my_ply.listen_2_element_property<std::uint8_t>("material", "blue",
        [](const std::uint8_t& b){ std::cout << (int)b <<" "; });
      my_ply.listen_2_element_property<std::uint8_t>("material", "alpha",
        [](const std::uint8_t& a){ std::cout << (int)a; });
  
      my_ply.listen_2_element_property<float>("material", "reflect_coeff",
        [](const float& reflection){ std::cout << reflection << " "; });
      my_ply.listen_2_element_property<float>("material", "refract_coeff",
        [](const float& refraction){ std::cout << refraction << " "; });
      my_ply.listen_2_element_property<float>("material", "refract_index",
        [](const float& refract_index){ std::cout << refract_index << " "; });
      my_ply.listen_2_element_property<float>("material", "extinct_coeff",
        [](const float& extinct_coeff){ std::cout << extinct_coeff << " ";});

      my_ply.read();
      return true;
    }
  
    bool create_ply_cube_ascii(const boost::filesystem::path& filename);
  }
}


