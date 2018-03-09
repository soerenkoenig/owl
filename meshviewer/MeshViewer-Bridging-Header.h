
#include <stdint.h>
#include <stdbool.h>

void * mesh_init();

void mesh_deinit(void * mesh);

void mesh_create_geosphere(void * mesh, float radius, size_t levels);

size_t mesh_num_vertices(void * mesh);

size_t mesh_num_edges(void * mesh);

size_t mesh_num_halfedges(void * mesh);

size_t mesh_num_faces(void * mesh);

size_t mesh_num_triangles(void * mesh);

size_t mesh_num_quads(void * mesh);
