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
        int _biome;
    public:
        GenMapNode(void) { setBiome(BIOME_SEA); }
        GenMapNode(int biome) { setBiome(biome); }
        int getBiome(void);
        string getBiomeString(bool);
        void setBiome(int);
        void setComputedBiome(float);
};

#endif
