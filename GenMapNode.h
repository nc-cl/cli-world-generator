#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

using namespace std;

const int BIOME_NULL = 0;
const int BIOME_SEA = 1;
const int BIOME_GRASSLAND = 2;

class GenMapNode {
    private:
        int _biome;
    public:
        GenMapNode(void) { setBiome(BIOME_NULL); }
        GenMapNode(int biome) { setBiome(biome); }
        int getBiome(void);
        string getBiomeString(bool);
        void setBiome(int);
};

#endif
