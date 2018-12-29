#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "world_map.h"

WorldMap::WorldMap(void) {
    _sizeX = DEFAULT_SIZE_X;
    _sizeY = DEFAULT_SIZE_Y;
    _initMap();
}

WorldMap::WorldMap(int x, int y) {
    _sizeX = std::max(x, 0);
    _sizeY = std::max(y, 0);
    _initMap();
}

void WorldMap::_initMap() {
    _heightMap.resize(_sizeX);
    for (int i = 0; i < _sizeX; i++) _heightMap[i].resize(_sizeY);
}

int WorldMap::getWidth() {
    return _sizeX;
}

int WorldMap::getHeight() {
    return _sizeY;
}

int WorldMap::getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = std::min(x + 1, std::abs(x - _sizeX)),
        distanceY = std::min(y + 1, std::abs(y - _sizeY));
    return std::min(distanceX, distanceY);
}

void WorldMap::setMapFromNoise(float** height) {
    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) _heightMap[x][y] = height[x][y];
    }
}

void WorldMap::printMap(bool useColour) {
    std::stringstream ss;

    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) {
            if (_heightMap[x][y] >= 0.45f) {
                // bg colour = 233; fg colour = 40
                ss << (useColour ?  "\033[48;5;233m\033[38;5;40mG\033[0m" : "G");
            } else {
                // bg colour = 0; fg colour = 27
                ss << (useColour ? "\033[48;5;0m\033[38;5;27m~\033[0m" : "~");
            }
        }
        ss << std::endl;
    }
    std::cout << ss.str();
}
