#include <vector>
#include "GenMapNode.h"

#ifndef GEN_MAP_H_
#define GEN_MAP_H_

using namespace std;

const int DIRECTION_N = 0;
const int DIRECTION_E = 1;
const int DIRECTION_S = 2;
const int DIRECTION_W = 3;

class GenMap {
    private:
        int _sizeX, _sizeY;
        vector<vector<GenMapNode> > _map;
        int _getAdjacentBiome(int, int, int);
    public:
        GenMap(void) : _sizeX(60), _sizeY(20) { populate(); }
        GenMap(int x, int y) : _sizeX(x), _sizeY(y) { populate(); }
        int getWidth(void);
        int getHeight(void);
        int getArea(void);
        void setSizeX(int);
        void setSizeY(int);
        void populate(void);
        void printMap(void);
};

#endif
