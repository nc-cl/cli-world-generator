#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "world_map.h"

WorldMap::WorldMap(void) {
    _width = DEFAULT_SIZE_X;
    _height = DEFAULT_SIZE_Y;
    _initMap();
}

WorldMap::WorldMap(int x, int y) {
    _width = std::max(x, 1);
    _height = std::max(y, 1);
    _initMap();
}

void WorldMap::_initMap() {
    _hmap.resize(_width);
    for (int i = 0; i < _width; i++) _hmap[i].resize(_height);
}

int WorldMap::getWidth() const {
    return _width;
}

int WorldMap::getHeight() const {
    return _height;
}

int WorldMap::getDistanceFromOutOfBounds(int x, int y) {
    int distance_x = std::min(x + 1, std::abs(x - _width)),
        distance_y = std::min(y + 1, std::abs(y - _height));
    return std::min(distance_x, distance_y);
}

void WorldMap::setMapFromNoise(float** height) {
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) _hmap[x][y] = height[x][y];
    }
}

void WorldMap::printMap(bool use_colour) {
    std::stringstream ss;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_hmap[x][y] >= 0.45f) {
                // bg colour = 233; fg colour = 40
                ss << (use_colour ? "\033[48;5;233m\033[38;5;40mGG\033[0m" : "GG");
            } else {
                // bg colour = 0; fg colour = 27
                ss << (use_colour ? "\033[48;5;0m\033[38;5;27m~~\033[0m" : "~~");
            }
        }
        ss << std::endl;
    }
    std::cout << ss.str();
}

float WorldMap::operator()(int x, int y) const {
    return _hmap.at(x).at(y);
}
