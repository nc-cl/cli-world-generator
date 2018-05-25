#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "world_map.h"

void WorldMap::_initMap() {
    _map.resize(_sizeX);

    for (int i = 0; i < _sizeX; i++) {
        _map[i].resize(_sizeY);
    }
}

int WorldMap::getWidth() {
    return _sizeX;
}

int WorldMap::getHeight() {
    return _sizeY;
}

int WorldMap::getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = std::min(x + 1, abs(x - _sizeX));
    int distanceY = std::min(y + 1, abs(y - _sizeY));
    return std::min(distanceX, distanceY);
}

void WorldMap::setMapFromNoise(float** height, float** rfall, float** temp) {
    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) {
            _map[x][y].setHeight(height[x][y]);
            _map[x][y].setRainfall(rfall[x][y]);
            _map[x][y].setTemperature(temp[x][y]);
        }
    }
}

void WorldMap::printMap(bool useColor) {
    std::stringstream ss;

    for (int y = _sizeY-1; y > -1; y--) {
        for (int x = 0; x < _sizeX; x++) {
            ss << _map[x][y].getBiomeString(useColor);
        }

        ss << std::endl;
    }

    std::cout << ss.str();
}
