#include <stdio.h>

#include "owl/math/mesh.hpp"


extern "C" void * mesh_init()
{
  return new owl::math::mesh<float>();
}

extern "C" void mesh_deinit(void * mesh)
{
    delete (owl::math::mesh<float> *) mesh;
}

extern "C" void mesh_create_geosphere(void * mesh, float radius, size_t levels)
{
  *((owl::math::mesh<float> *)mesh) =
   owl::math::create_geodesic_sphere<float>(radius, levels);
}

extern "C" void mesh_create_box(void * mesh)
{
  *((owl::math::mesh<float> *)mesh) =
   owl::math::create_box<float>();
}

extern "C" size_t mesh_num_vertices(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_vertices();
}

extern "C" size_t mesh_num_edges(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_edges();
}

extern "C" size_t mesh_num_halfedges(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_halfedges();
}

extern "C" size_t mesh_num_faces(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_faces();
}

extern "C" size_t mesh_num_triangles(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_triangles();
}

extern "C" size_t mesh_num_quads(void * mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_quads();
}

extern "C" void mesh_edge_indices(void * mesh, int* indices)
{
  owl::math::mesh<float>& m = *((owl::math::mesh<float>*) mesh);
  for(auto e: m.edges())
  {
    *indices++ = (int)m.origin(e).index();
  }
}

extern "C" void mesh_triangle_indices(void * mesh, int* indices)
{
  owl::math::mesh<float>& m = *((owl::math::mesh<float>*) mesh);
  for(auto f: m.faces())
  {
    if(!m.is_triangle(f))
      continue;
  
    for(auto v: m.vertices(f))
      *indices++ = (int)v.index();
  }
}

extern "C" void mesh_quad_indices(void * mesh, int* indices)
{
  owl::math::mesh<float>& m = *((owl::math::mesh<float>*) mesh);
  for(auto f: m.faces())
  {
    if(!m.is_quad(f))
      continue;
  
    for(auto v: m.vertices(f))
      *indices++ = (int)v.index();
  }
}



extern "C" void mesh_print_vertex_positions(void * mesh)
{
   owl::math::print_vertex_positions(*(const owl::math::mesh<float>*)mesh);
}


extern "C" const float* mesh_vertex_position_data(void * mesh)
{
    return (const float*)(&((const owl::math::mesh<float>*)mesh)->position(owl::math::vertex_handle(0)));
}
/*
extern "C" size_t mesh_vertex_position_count(void * mesh)
{
    return ((const math::mesh<float>*)mesh)->num_vertices();
}

extern "C" bool mesh_load(void * mesh, const char* filename)
{
    return ((math::mesh<MyFloat>*)mesh)->load(filename);
}*/




