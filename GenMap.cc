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
    
    int val = 1;
    
    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            _map[i].resize(_sizeX);
            _map[i][j] = val;
            val++;
        }
    }
}

void GenMap::printMapValues() {
    stringstream strstr;

    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[i][j];
            strstr << ((_map[i][j] < 10) ? "   " : ((_map[i][j] < 100) ? "  " : " "));
        }

        strstr << endl;
    }

    cout << strstr.str();
}

