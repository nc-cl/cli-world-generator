#include <vector>
#include <array>
#include "GenMapNode.h"

#ifndef GEN_MAP_H_
#define GEN_MAP_H_

using namespace std;

const int DEFAULT_SIZE_X = 120;
const int DEFAULT_SIZE_Y = 40;

const int DIRECTION_N = 0;
const int DIRECTION_E = 1;
const int DIRECTION_S = 2;
const int DIRECTION_W = 3;

const array<int, 4> DIRECTIONS = {
    DIRECTION_N,
    DIRECTION_E,
    DIRECTION_S,
    DIRECTION_W
};

class GenMap {
    private:
        int _sizeX, _sizeY;
        vector<vector<GenMapNode> > _map;
        void _initMap(void);
        GenMapNode _getAdjacent(int, int, int);
        int _getDistanceFromOutOfBounds(int, int);
    public:
        GenMap(void) : _sizeX(DEFAULT_SIZE_X), _sizeY(DEFAULT_SIZE_Y) { _initMap(); }
        GenMap(int x, int y) : _sizeX(x), _sizeY(y) { _initMap(); }
        int getWidth(void);
        int getHeight(void);
        int getArea(void);
        void generateLand(void);
        void printMap(bool);
};

#endif
