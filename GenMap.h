#include <vector>
#include <array>
#include "GenMapNode.h"

#ifndef GEN_MAP_H_
#define GEN_MAP_H_

using namespace std;

const int DEFAULT_SIZE_X = 120;
const int DEFAULT_SIZE_Y = 40;

class GenMap {
    private:
        int _sizeX, _sizeY;
        vector<vector<GenMapNode> > _map;
        void _initMap(void);
        int _getDistanceFromOutOfBounds(int, int);
        void _setMapFromNoise(float**, float**);
    public:
        GenMap(void) :
            _sizeX(DEFAULT_SIZE_X),
            _sizeY(DEFAULT_SIZE_Y) {
                _initMap();
            }

        GenMap(int x, int y) {
            _sizeX = max(x, 0);
            _sizeY = max(y, 0);
            _initMap();
        }

        int getWidth(void);
        int getHeight(void);
        void generate(int, float, float);
        void printMap(bool);
};

#endif
