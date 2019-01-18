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
        HeightMap(int, int);
        std::vector<std::vector<float> > getHeights(void) const;
        void setHeights(float **heights, int x, int y);
        void setHeights(std::vector<std::vector <float> > *heights);
        int getSizeX(void) const;
        int getSizeY(void) const;
        float operator()(int x, int y) const;
        HeightMap operator+(HeightMap *other);
};

#endif
