#ifndef GEN_MAP_NODE_H_
#define GEN_MAP_NODE_H_

const int BIOME_NULL = 0;
const int BIOME_SEA = 1;
const int BIOME_GRASSLAND = 2;

class GenMapNode {
    private:
        int _biome;
        char _biomeChar;
    public:
        GenMapNode(void) { setBiome(BIOME_NULL); }
        GenMapNode(int biome) { setBiome(biome); }
        int getBiome(void);
        char getBiomeChar(void);
        void setBiome(int);
        bool isLand(void);
};

#endif
