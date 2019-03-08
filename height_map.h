// Height map data class.
// TODO: 1) Decouple class from program-specific assumptions
// e.g. the default dimensions of the height map, and the upper
// and lower bounds on height. 2) Define more matrix-like
// operations (esp. matrix-scalar operations).

#ifndef WORLD_MAP_H_
#define WORLD_MAP_H_

#include <vector>

const int DEFAULT_SIZE_X = 100;
const int DEFAULT_SIZE_Y = 100;

class HeightMap {
    protected:
        std::vector<std::vector<float> > _heights;
    public:
        HeightMap(void);
        HeightMap(const HeightMap *hmap);
        HeightMap(int x, int y);
        std::vector<std::vector<float> > getHeights(void) const;
        void setHeights(float height, int x, int y);
        void setHeights(float **heights, int x, int y);
        void setHeights(std::vector<std::vector <float> > *heights);
        int getSizeX(void) const;
        int getSizeY(void) const;
        float operator()(int x, int y) const;
        HeightMap operator+(HeightMap *other);
        void operator+=(HeightMap *other);
};

#endif
