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

extern "C"  void* mesh_halfedge_position_data_init(void * mesh)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float>*)mesh;
  float* positions = new float[m->num_halfedges()*3];
 
  std::size_t i = 0;
  for(auto he: m->halfedges())
  {
    positions[i++] = m->position(m->target(he)).x();
    positions[i++] = m->position(m->target(he)).y();
    positions[i++] = m->position(m->target(he)).z();
  }
  return positions;
}

extern "C" void mesh_halfedge_position_data_deinit(float * pos)
{
   delete[] pos;
}

extern "C" void* mesh_halfedge_normal_data_init(void * mesh)
{
  const owl::math::mesh<float>* m = (const owl::math::mesh<float>*)mesh;
  float* normals = new float[m->num_halfedges()*3];
 
  std::size_t i = 0;
  for(auto he: m->halfedges())
  {
    normals[i++] = m->normal(he).x();
    normals[i++] = m->normal(he).y();
    normals[i++] = m->normal(he).z();
  }
  return normals;
}

extern "C" void mesh_halfedge_normal_data_deinit( void * nmls)
{
  delete[] (float*)nmls;
}

extern "C" int* mesh_triangle_halfedge_indices_init(void* mesh)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float>*)mesh;
  int* indices = new int[m->num_faces()*3];
  std::size_t i = 0;
  for(auto f: m->faces())
  {
    std::size_t n = 0;
    for(auto he: m->halfedges(f))
    {
      indices[i++] = (int)he.index();
      n++;
      if(n == 3)
        break;
    }
  }
  return indices;
}

extern "C" void mesh_triangle_halfedge_indices_deinit(void* indices)
{
   delete[] (int*)indices;
}

extern "C" int* mesh_edge_halfedge_indices_init(void* mesh)
{
  const owl::math::mesh<float>* m = (const owl::math::mesh<float>*)mesh;
  int* indices = new int[m->num_edges()*2];
  std::size_t i = 0;
  for(auto e: m->edges())
  {
  
    indices[i++] = (int)m->halfedge(e).index();
    indices[i++] = (int)m->opposite(m->halfedge(e)).index();
  
  }
  return indices;
}

extern "C" void mesh_edge_halfedge_indices_deinit(void* indices)
{
   delete[] (int*)indices;
}


extern "C" const void* mesh_vertex_position_data(void* mesh)
{
    return (const void*)(&((const owl::math::mesh<float>*)mesh)->position(owl::math::vertex_handle(0)));
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




