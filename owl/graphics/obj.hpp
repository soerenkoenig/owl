#pragma once
#include <vector>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include "owl/utils/file_utils.hpp"



namespace owl
{
  namespace graphics
  {
    struct mtl_info
    {
      std::string name;
      std::array<float,4> ambient;
      std::string ambient_texture_name;
      std::array<float,4> diffuse;
      std::string diffuse_texture_name;
      std::array<float,4> specular;
      std::string specular_texture_name;
      std::array<float,4> emissive;
      std::string emissive_texture_name;
      float shininess;

      mtl_info() :
        ambient_texture_name(""), diffuse_texture_name(""), specular_texture_name(""), emissive_texture_name("")
      {
        ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        diffuse = {0.2f, 0.2f, 0.2f, 1.0f};
        specular = {0.2f, 0.2f, 0.2f, 1.0f};
        emissive = {0.0f, 0.0f, 0.0f, 1.0f};
        shininess = 0;
        name = "default";
      }

    };

    struct polygon
    {
      std::vector<std::size_t> vertex_indices;
      std::vector<std::size_t> normal_indices;
      std::vector<std::size_t> texcoord_indices;
      std::size_t material_index;

      polygon(std::size_t n)
      {
        vertex_indices.resize(n);
        material_index = -1;
      }

    };

    struct group
    {
      std::string name;
      std::vector<std::size_t> face_indices;
    };

    struct obj
    {
      std::vector<std::array<double,3> > colors;
      std::vector<std::array<double,4> > vertices;
      std::vector<std::array<double,3> > normals;
      std::vector<std::array<double,3> > texcoords;
      std::vector<polygon> faces;

      std::vector<mtl_info> materials;
      std::map<std::string, std::size_t> material_index_lut;

      std::vector<group> groups;
      std::map<std::string, std::size_t> group_index_lut;
    
      std::string object_name;
      std::string parent_path;

      std::size_t current_material_index;
      std::vector<std::size_t> current_group_indices;


      void show_stats()
      {
        std::cout << "num vertices " << vertices.size() << std::endl;
        std::cout << "num normals " << normals.size() << std::endl;
        std::cout << "num colors " << colors.size() << std::endl;
        std::cout << "num texcoords " << texcoords.size() << std::endl;
        std::cout << "num faces " << faces.size() << std::endl;
        std::cout << "num materials " << materials.size() << std::endl;
        std::cout << "num groups " << groups.size() << std::endl;
      }

      void tokenize(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens)
      {
        tokens.clear();


        // skip delimiters at beginning.
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

        // find first "non-delimiter".
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
          // found a token, add it to the vector.
          tokens.push_back(str.substr(lastPos, pos - lastPos));

          // skip delimiters.  Note the "not_of"
          lastPos = str.find_first_not_of(delimiters, pos);

          // find next "non-delimiter"
          pos = str.find_first_of(delimiters, lastPos);
        }
      }


      bool read_obj(const std::string& filename)
      {
        this->parent_path = owl::utils::parent_path(filename);
        std::fstream in(filename.c_str(), std::ios::in);

        if (in.is_open())
        {
          std::string line;
          std::vector<std::string> tokens;
          vertices.clear();
          colors.clear();
          normals.clear();
          texcoords.clear();
          faces.clear();
          materials.clear();
          material_index_lut.clear();
          current_material_index = -1;


          std::string::size_type pos;

          while (std::getline(in, line, '\n'))
          {

            pos = line.find(std::string("v "));
            if (std::string::npos != pos)
            {
              read_vertex(line);
              continue;
            }

            pos = line.find("vn ");
            if (std::string::npos != pos)
            {
              read_normal(line);
              continue;
            }

            pos = line.find("vc ");
            if (std::string::npos != pos)
            {
              read_color(line);
              continue;
            }

            pos = line.find("vt ");
            if (std::string::npos != pos)
            {
              read_texcoord(line);
              continue;
            }


            pos = line.find("f ");
            if (std::string::npos != pos)
            {
              read_polygon(line);
              continue;
            }

            pos = line.find("g ");
            if (std::string::npos != pos)
            {
              read_group(line);
              continue;
            }
          
            pos = line.find("o ");
            if(std::string::npos != pos)
            {
              read_object_name(line);
              continue;
            }

            pos = line.find("usemtl ");
            if (std::string::npos != pos)
            {
              read_mtl_info(line);
              continue;
            }

            pos = line.find("mtllib ");
            if (std::string::npos != pos)
            {
              read_mtl_lib(line);
              continue;
            }


          }
          in.close();
          return true;
        }
        return false;
      }

      void read_mtl_lib(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        for (std::size_t i = 1; i < tokens.size(); i++)
          read_mtl(tokens[i]);
      }

      void read_mtl(const std::string& filename)
      {
        std::fstream in(filename.c_str(), std::ios::in);
        if(!in.is_open())
          in.open(parent_path + "/" + filename, std::ios::in);
        if (in.is_open())
        {
          std::string line;
          while (std::getline(in, line, '\n'))
          {

            std::string::size_type pos = line.find("newmtl ");
            if (std::string::npos != pos)
            {
              mtl_info  mtl;

              std::vector<std::string> tokens;
              tokenize(line, " ", tokens);

              mtl.name = tokens[1];
              while (std::getline(in, line, '\n') && line.find("newmtl ") == std::string::npos)
              {


                pos = line.find("map_Ka ");
                if (std::string::npos != pos)
                {
                  read_ambient_map(mtl, line);
                  continue;
                }

                pos = line.find("map_Kd ");
                if (std::string::npos != pos)
                {
                  read_diffuse_map(mtl, line);
                  continue;
                }

                pos = line.find("map_Ks ");
                if (std::string::npos != pos)
                {
                  read_specular_map(mtl, line);
                  continue;
                }

                pos = line.find("map_Ke ");
                if (std::string::npos != pos)
                {
                  read_emissive_map(mtl, line);
                  continue;
                }

                pos = line.find("Ka ");
                if (std::string::npos != pos)
                {
                  read_ambient(mtl, line);
                  continue;
                }

                pos = line.find("Kd ");
                if (std::string::npos != pos)
                {
                  read_diffuse(mtl, line);
                  continue;
                }

                pos = line.find("Ks ");
                if (std::string::npos != pos)
                {
                  read_specular(mtl, line);
                  continue;
                }

                pos = line.find("Ke ");
                if (std::string::npos != pos)
                {
                  read_emissive(mtl, line);
                  continue;
                }

                pos = line.find("Ns ");
                if (std::string::npos != pos)
                {
                  read_shininess(mtl, line);
                  continue;
                }

                pos = line.find("d ");
                if (std::string::npos != pos)
                {
                  read_d(mtl, line);
                  continue;
                }
              }
              materials.push_back(mtl);
              material_index_lut[mtl.name] = materials.size() - 1;

            }
          }

          in.close();

        }
      }

      void read_ambient(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.ambient = {stof(tokens[1]),
          stof(tokens[2]),
          stof(tokens[3]), 1.0f};
      }

      void read_d(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        float d = stof(tokens[1]);
        mtl.ambient[3] = d;
        mtl.diffuse[3] = d;
        mtl.specular[3] = d;
      }

      void read_diffuse(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.diffuse = {stof(tokens[1]),
          stof(tokens[2]),
          stof(tokens[3]), 1.0f};
      }

      void read_specular(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.specular = {stof(tokens[1]),
          stof(tokens[2]),
          stof(tokens[3]), 1.0f};
      }

      void read_emissive(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.emissive = {stof(tokens[1]),
          stof(tokens[2]),
          stof(tokens[3]), 1.0f};
      }

      void read_ambient_map(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.ambient_texture_name = tokens[tokens.size() - 1];
      }

      void read_diffuse_map(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.diffuse_texture_name = tokens[tokens.size() - 1];
      }

      void read_specular_map(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.specular_texture_name = tokens[tokens.size() - 1];
      }

      void read_emissive_map(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.specular_texture_name = tokens[tokens.size() - 1];
      }

      void read_shininess(mtl_info& mtl, const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        mtl.shininess = stof(tokens[1]);
      }

      void read_vertex(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        switch(tokens.size())
        {
        case 4:
          vertices.push_back({stod(tokens[1]), stod(tokens[2]), stod(tokens[3]), 1.0});
        break;
        case 5:
          vertices.push_back({stod(tokens[1]), stod(tokens[2]), stod(tokens[3]), stod(tokens[4])});
        break;
        };
      }

      void read_normal(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        normals.push_back({stod(tokens[1]), stod(tokens[2]), stod(tokens[3])});
      }

      void read_color(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        colors.push_back({stod(tokens[1]), stod(tokens[2]), stod(tokens[3])});
      }

      void read_texcoord(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        switch(tokens.size())
        {
         case 2:
          texcoords.push_back({stod(tokens[1]), 0.0, 1.0});
          break;
        case 3:
          texcoords.push_back({stod(tokens[1]), stod(tokens[2]), 1.0});
          break;
        case 4:
          texcoords.push_back({stod(tokens[1]), stod(tokens[2]), stod(tokens[3])});
          break;
        }
      }

      void read_mtl_info(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);

        auto it = material_index_lut.find(tokens[1]);

        if (it != material_index_lut.end())
          current_material_index = it->second;

      }

      void read_group(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);
        current_group_indices.clear();

        for (std::size_t i = 1; i < tokens.size(); i++)
        {
          auto it = group_index_lut.find(tokens[i]);
          if (it != group_index_lut.end())
          {
            current_group_indices.push_back(it->second);
          }
          else
          {
            group g;
            g.name = tokens[i];
            groups.push_back(g);
            current_group_indices.push_back(groups.size() - 1);
          }
        }
      }
    
      void read_object_name(const std::string& line)
      {
        object_name = line;
      }

      void read_polygon(const std::string& line)
      {
        std::vector<std::string> tokens;
        tokenize(line, " ", tokens);

        polygon poly(tokens.size() - 1);
        poly.material_index = current_material_index;

        for (std::size_t i = 1; i < tokens.size(); i++)
        {
          std::vector<std::string> smaller_tokens;
          tokenize(tokens[i], "//", smaller_tokens);
          poly.vertex_indices[i - 1] = stoi(smaller_tokens[0]) - 1;

          //if texture is not specified but normal
          if (smaller_tokens.size() == 2)
          {


            poly.normal_indices.push_back(stoi(smaller_tokens[1]) - 1);
          }


          //if texture and normals are specified
          if (smaller_tokens.size() == 3)
          {
            poly.texcoord_indices.push_back(stoi(smaller_tokens[1]) - 1);
            poly.normal_indices.push_back(stoi(smaller_tokens[2]) - 1);

          }
        }
        faces.push_back(poly);
        for (unsigned i = 0; i < current_group_indices.size(); i++)
        {
          groups[i].face_indices.push_back(faces.size() - 1);
        }

      }


    };
    }
}







