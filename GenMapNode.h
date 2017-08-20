#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

using namespace std;

const int BIOME_SEA = 0;
const int BIOME_COAST = 1;
const int BIOME_MARSH = 2;
const int BIOME_GRASSLAND = 3;
const int BIOME_FOREST = 4;
const int BIOME_MOUNTAIN = 5;
const int BIOME_MOUNTAIN_SNOW = 6;
const int BIOME_MOUNTAIN_FOREST = 7;

class GenMapNode {
    private:
        float _height;
        float _rainfall;
    public:
        GenMapNode(void) : _height(0.0f), _rainfall(0.0f) {}
        GenMapNode(float height, float rfall) : _height(height), _rainfall(rfall) {}

        int getBiome(void);
        string getBiomeString(bool);
        void setHeight(float);
        void setRainfall(float);
};

#endif
