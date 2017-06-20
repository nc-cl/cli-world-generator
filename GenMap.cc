#include <iostream>
#include <string>
#include <sstream>
#include "GenMap.h"

using namespace std;

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

int GenMap::getSize() {
    return _sizeX * _sizeY;
}

void GenMap::setSizeX(int sizeX) {
    _sizeX = sizeX;
}

void GenMap::setSizeY(int sizeY) {
    _sizeY = sizeY;
}

void GenMap::populate() {
    int size = getSize();
    _map = new int[size];
    
    int val = 0;

    for (int i = 0; i < size; i++) {
        _map[i] = val;
        val++;
    }
}

void GenMap::printMapValues() {
    std::stringstream strstr;

    strstr << "map:";
    
    for (int i = 0; i < getSize(); i++) {
        strstr << " " << _map[i];
    }

    cout << strstr.str() << endl;
}

