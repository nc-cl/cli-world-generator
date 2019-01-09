#ifndef WORLD_MAP_H_
#define WORLD_MAP_H_

#include <vector>
#include <array>

const int DEFAULT_SIZE_X = 120;
const int DEFAULT_SIZE_Y = 40;

class WorldMap {
    private:
        int _sizeX, _sizeY;
        std::vector<std::vector<float> > _heightMap;
        void _initMap(void);
    public:
        WorldMap(void);
        WorldMap(int, int);
        int getWidth(void);
        int getHeight(void);
        int getDistanceFromOutOfBounds(int, int);
        void setMapFromNoise(float**);
        void printMap(bool);
        float operator()(int, int);
};

#endif
