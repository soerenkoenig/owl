
#include "owl/io/off.hpp"
#include <iostream>

namespace owl
{
  namespace io
  {
    off_reader::off_reader()
    {
    }

    off_reader::off_reader(const std::string& filename)
    {
      open(filename);
    }

    void off_reader::open(const std::string& filename)
    {
      file.open(filename, std::ios_base::in);
    }

    bool off_reader::is_open() const
    {
      return file.is_open();
    }

    bool off_reader::listen_2_counts(std::function<void(const std::size_t&, const std::size_t&)> fn)
    {
      if(!is_open())
        return false;
  
      on_counts = fn;
      return true;
    }

    bool off_reader::listen_2_face(std::function<void(const std::vector<std::size_t>&)> fn)
    {
      if(!is_open())
        return false;
  
      on_face = fn;
      return true;
    }

    bool off_reader::listen_2_vertex(std::function<void(const float &, const float&, const float&)> fn)
    {
      if(!is_open())
        return false;
  
      on_vertex = fn;
      return true;
    }

    bool off_reader::read_magic(std::istream& in)
    {
      std::string magic;
      in >> magic;
      if(magic != "OFF")
      {
        in.setstate(std::ios::failbit);
        return false;
      }
      return true;
    }
  
    bool off_reader::read_counts(std::istream& in)
    {
      in >> n_vertices >> n_faces >> n_edges;
      if(!in)
        return false;
  
      if(on_counts)
        on_counts(n_vertices,n_faces);
  
      return true;
    }
    
    bool off_reader::read_vertices(std::istream& in)
    {
      for(std::size_t i = 0; i < n_vertices; ++i)
      {
        float x, y, z;
        in >> x >> y >> z;
        if(!in)
          return false;
      
        if(on_vertex)
          on_vertex(x,y,z);
      }
      return true;
    }
  
    bool off_reader::read_faces(std::istream& in)
    {
      for(std::size_t i = 0; i < n_faces; ++i)
      {
        std::size_t n;
        in >> n;
        if(!in)
          return false;
    
        std::vector<std::size_t> vertices(n);
        for(auto& v: vertices)
          in >> v;
        if(!in)
          return false;
    
        if(on_face)
            on_face(vertices);
      }
      return true;
    }
  
    bool off_reader::read()
    {
      if(!is_open())
        return false;
  
      if(!read_magic(file))
        return false;
  
      if(!read_counts(file))
        return false;
  
      if(!read_vertices(file))
        return false;
  
      if(! read_faces(file))
        return false;
  
      return true;
    }
  }
}
