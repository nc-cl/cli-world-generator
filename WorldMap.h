#include <vector>
#include <array>
#include "WorldMapSection.h"

#ifndef GEN_MAP_H_
#define GEN_MAP_H_

using namespace std;

const int DEFAULT_SIZE_X = 120;
const int DEFAULT_SIZE_Y = 40;

class WorldMap {
    private:
        int _sizeX, _sizeY;
        vector<vector<WorldMapSection> > _map;
        void _initMap(void);
    public:
        WorldMap(void) :
            _sizeX(DEFAULT_SIZE_X),
            _sizeY(DEFAULT_SIZE_Y) {
                _initMap();
            }

        WorldMap(int x, int y) {
            _sizeX = max(x, 0);
            _sizeY = max(y, 0);
            _initMap();
        }

        int getWidth(void);
        int getHeight(void);
        int getDistanceFromOutOfBounds(int, int);
        void setMapFromNoise(float**, float**, float**);
        void printMap(bool);
};

#endif
