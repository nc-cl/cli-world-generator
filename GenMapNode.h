#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

using namespace std;

const int BIOME_SEA = 0;
const int BIOME_GRASSLAND = 1;

class GenMapNode {
    private:
        int _biome;
    public:
        GenMapNode(void) { setBiome(BIOME_SEA); }
        GenMapNode(int biome) { setBiome(biome); }
        int getBiome(void);
        string getBiomeString(bool);
        void setBiome(int);
};

#endif
