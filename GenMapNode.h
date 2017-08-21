#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

using namespace std;

const int BIOME_SEA = 0;
const int BIOME_COAST = 1;
const int BIOME_MARSH = 2;
const int BIOME_GRASSLAND = 3;
const int BIOME_FOREST = 4;
const int BIOME_DESERT = 5;
const int BIOME_SAVANNA = 6;
const int BIOME_RAINFOREST = 7;
const int BIOME_MOUNTAIN = 8;
const int BIOME_MOUNTAIN_SNOW = 9;

class GenMapNode {
    private:
        float _height;
        float _rainfall;
        bool _isTropical;
    public:
        GenMapNode(void) :
            _height(0.0f),
            _rainfall(0.0f),
            _isTropical(false) {}
        GenMapNode(float height, float rfall, bool trop) :
            _height(height),
            _rainfall(rfall),
            _isTropical(trop) {}

        int getBiome(void);
        string getBiomeString(bool);
        void setHeight(float);
        void setRainfall(float);
        void setIsTropical(bool);
};

#endif
