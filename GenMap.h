#include <vector>
#include "GenMapNode.h"

#ifndef GEN_MAP_H_
#define GEN_MAP_H_

using namespace std;

class GenMap {
    private:
        int _sizeX, _sizeY;
        vector<vector<GenMapNode> > _map;
    public:
        GenMap(void) : _sizeX(25), _sizeY(10) { populate(); }
        GenMap(int x, int y) : _sizeX(x), _sizeY(y) { populate(); }
        int getWidth(void);
        int getHeight(void);
        int getArea(void);
        void setSizeX(int);
        void setSizeY(int);
        void populate(void);
        void printMapValues(void);
        GenMapNode getAtPoint(int, int);
};

#endif

