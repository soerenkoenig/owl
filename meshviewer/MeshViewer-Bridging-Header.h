
#include <stdint.h>
#include <stdbool.h>

void * mesh_init();

void mesh_deinit(void * mesh);

void mesh_create_geosphere(void * mesh, float radius, size_t levels);

void mesh_create_box(void * mesh);

size_t mesh_num_vertices(void * mesh);

size_t mesh_num_edges(void * mesh);

size_t mesh_num_halfedges(void * mesh);

size_t mesh_num_faces(void * mesh);

size_t mesh_num_triangles(void * mesh);

size_t mesh_num_quads(void * mesh);

void* mesh_halfedge_position_data_init(void* mesh);
void mesh_halfedge_position_data_deinit(void* pos);

void* mesh_halfedge_normal_data_init(void * mesh);
void mesh_halfedge_normal_data_deinit(void* nmls);

void* mesh_triangle_halfedge_indices_init(void* mesh);
void mesh_triangle_halfedge_indices_deinit(void* indices);

void* mesh_edge_halfedge_indices_init(void* mesh);
void mesh_edge_halfedge_indices_deinit(void* indices);

void mesh_print_vertex_positions(void * mesh);
