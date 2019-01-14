#ifndef WORLD_MAP_H_
#define WORLD_MAP_H_

#include <vector>
#include <array>

const int DEFAULT_SIZE_X = 100;
const int DEFAULT_SIZE_Y = 100;

class HeightMap {
    private:
        int _size_x;
        int _size_y;
        std::vector<std::vector<float> > _heights;
    public:
        HeightMap(int, int);
        int getSizeX(void) const;
        int getSizeY(void) const;
        int getDistanceFromOutOfBounds(int, int);
        void setHeights(float**);
        void printMap(bool);
        float operator()(int, int) const;
};

#endif
