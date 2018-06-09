#include <string>

#ifndef WORLD_MAP_SECTION_H_
#define WORLD_MAP_SECTION_H_

const int BIOME_SEA = 0;
const int BIOME_COAST = 1;
const int BIOME_MARSH = 2;
const int BIOME_GRASSLAND = 3;
const int BIOME_FOREST = 4;
const int BIOME_DESERT = 5;
const int BIOME_SAVANNA = 6;
const int BIOME_RAINFOREST = 7;
const int BIOME_MOUNTAIN = 8;
const int BIOME_SNOW = 9;
const int BIOME_MOUNTAIN_SNOW = 10;

class WorldMapSection {
    private:
        float _height;
        float _rainfall;
        float _temperature;
    public:
        WorldMapSection(void);
        WorldMapSection(float, float, float);
        int getBiome(void);
        std::string getBiomeString(bool);
        void setHeight(float);
        void setRainfall(float);
        void setTemperature(float);
};

#endif
