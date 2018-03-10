
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

const float* mesh_vertex_position_data(void * mesh);

void mesh_print_vertex_positions(void * mesh);
