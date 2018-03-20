#include <stdio.h>

#include "owl/math/mesh.hpp"
#include "owl/math/mesh_triangulation.hpp"
#include "owl/math/mesh_primitives.hpp"
#include "owl/math/mesh_io.hpp"

extern "C" void* mesh_init()
{
  return new owl::math::mesh<float>();
}

extern "C" void mesh_deinit(void* mesh)
{
  delete (owl::math::mesh<float> *) mesh;
}

extern "C" void mesh_create_geosphere(void* mesh, float radius, size_t levels)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float> *)mesh;
  *m = owl::math::create_geodesic_sphere<float>(radius, levels);
}

extern "C" void mesh_create_box(void * mesh)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float>*)mesh;
  *m = owl::math::create_box<float>();
}

extern "C" void mesh_create_torus(void* mesh, float r, float R, std::size_t nsides, std::size_t rings)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float> *)mesh;
  *m = owl::math::create_torus<float>(r, R, nsides, rings);
}

extern "C" void mesh_create_tetrahedron(void* mesh)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float> *)mesh;
  *m = owl::math::create_tetradedron<float>();
}

extern "C" size_t mesh_num_vertices(void* mesh)
{
  return ((owl::math::mesh<float>*)mesh)->num_vertices();
}

extern "C" size_t mesh_num_edges(void * mesh)
{
  return ((owl::math::mesh<float>*)mesh)->num_edges();
}

extern "C" size_t mesh_num_halfedges(void* mesh)
{
  return ((owl::math::mesh<float>*)mesh)->num_halfedges();
}

extern "C" size_t mesh_num_faces(void* mesh)
{
  return ((owl::math::mesh<float>*)mesh)->num_faces();
}

extern "C" size_t mesh_num_triangles(void* mesh)
{
  return ((owl::math::mesh<float> *)mesh)->num_triangles();
}

extern "C" size_t mesh_num_quads(void* mesh)
{
  return ((owl::math::mesh<float>*)mesh)->num_quads();
}

extern "C" void mesh_edge_indices(void* mesh, int* indices)
{
  owl::math::mesh<float>& m = *((owl::math::mesh<float>*) mesh);
  for(auto e: m.edges())
  {
    *indices++ = (int)m.origin(e).index();
  }
}

extern "C" void mesh_triangle_indices(void* mesh, int* indices)
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

extern "C" void mesh_quad_indices(void* mesh, int* indices)
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

extern "C" void mesh_print_vertex_positions(void* mesh)
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

extern "C" void mesh_halfedge_normal_data_deinit(void* nmls)
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
    for(auto he: m->inner_halfedges(f))
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

extern "C" void mesh_triangulate(void* mesh)
{
  owl::math::mesh<float>* m = (owl::math::mesh<float>*)mesh;
  triangulate_monoton(*m);
}


extern "C" bool mesh_load_ply(void* mesh, const char* filename)
{
   owl::math::mesh<float>* m = (owl::math::mesh<float>*)mesh;
   bool success =  owl::math::read_ply(*m,filename);
  std::cout << m->bounds()<<std::endl;
   return success;
}


#include "owl/graphics/image.hpp"

extern "C" void* image_init()
{
  return new owl::graphics::rgb8u_image();
}

extern "C" void* image_init2(int width, int height)
{
  return new owl::graphics::rgb8u_image(width, height);
}

extern "C" void image_deinit(void* img)
{
  delete (owl::graphics::rgb8u_image*) img;
}

extern "C" int image_width(void* img)
{
  owl::graphics::rgb8u_image* im = (owl::graphics::rgb8u_image*) img;
  return (int)im->width();
}

extern "C" int image_height(void* img)
{
  owl::graphics::rgb8u_image* im = (owl::graphics::rgb8u_image*) img;
  return (int)im->height();
}

extern "C" void* image_raw_data(void* img)
{
  owl::graphics::rgb8u_image* im = (owl::graphics::rgb8u_image*) img;
  return (void*)im->data();
}

extern "C" void image_create_grid(void* img, int nx, int ny, int spacing)
{
  owl::graphics::rgb8u_image* im = (owl::graphics::rgb8u_image*) img;
  *im = owl::graphics::create_grid(nx,ny,spacing);
}

extern "C" void image_create_grid_color(void* img, int nx, int ny, int spacing, uint32_t xcolor, uint32_t ycolor)
{
  owl::graphics::rgb8u_image* im = (owl::graphics::rgb8u_image*) img;
  *im = owl::graphics::create_grid_color(nx, ny, spacing, owl::color::rgb8u::hex(xcolor),
  owl::color::rgb8u::hex(ycolor));
}



