//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//
#include <stdint.h>
#include <stdbool.h>

void * mesh_init();

void mesh_deinit(void * mesh);

void mesh_create_geosphere(void * mesh, float radius, size_t levels);
