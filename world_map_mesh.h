#ifndef WORLD_MAP_MESH_H_
#define WORLD_MAP_MESH_H_

#include "mesh.h"
#include "world_map.h"

class WorldMapMesh : public Mesh {
    public:
        WorldMapMesh(const WorldMap *wmap);
        void draw(void);
};

#endif
