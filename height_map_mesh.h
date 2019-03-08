// Mesh data class for the height map class.
// There are no functions to manipulate the mesh, as the mesh data
// is currently entirely dependent on the given height map data.

#ifndef WORLD_MAP_MESH_H_
#define WORLD_MAP_MESH_H_

#include "mesh.h"
#include "height_map.h"

class HeightMapMesh : public Mesh {
    public:
        HeightMapMesh (const HeightMap *hmap);
        void draw(void);
};

#endif
