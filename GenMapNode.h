#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

using namespace std;

const int BIOME_SEA = 0;
const int BIOME_COAST = 1;
const int BIOME_GRASSLAND = 2;
const int BIOME_MOUNTAIN = 3;
const int BIOME_SNOW = 4;

class GenMapNode {
    private:
        float _height;
    public:
        GenMapNode(void) { setHeight(0.0f); }
        GenMapNode(float height) { setHeight(height); }
        int getBiome(void);
        string getBiomeString(bool);
        void setHeight(float);
};

#endif
