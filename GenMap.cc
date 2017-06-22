#include <iostream>
#include <string>
#include <sstream>
#include "GenMap.h"


int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

int GenMap::getArea() {
    return _sizeX * _sizeY;
}

void GenMap::setSizeX(int sizeX) {
    _sizeX = sizeX;
}

void GenMap::setSizeY(int sizeY) {
    _sizeY = sizeY;
}

void GenMap::populate() {
    _map.resize(_sizeY);
    
    for (int i = 0; i < _sizeY; i++) {
        _map[i].resize(_sizeX);
        
        for (int j = 0; j < _sizeX; j++) {
            _map[i][j].setBiome(BIOME_SEA);
        }
    }
}

void GenMap::printMapValues() {
    stringstream strstr;

    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[i][j].getBiomeChar();
        }

        strstr << endl;
    }

    cout << strstr.str();
}

GenMapNode GenMap::getAtPoint(int x, int y) {
    return _map[y][x];
}

