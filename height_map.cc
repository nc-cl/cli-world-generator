#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "height_map.h"

HeightMap::HeightMap(int x, int y) {
    _size_x = std::max(x, 1);
    _size_y = std::max(y, 1);
    _heights.resize(_size_x);
    for (int i = 0; i < _size_x; i++) _heights[i].resize(_size_y, 0.0f);
}

int HeightMap::getSizeX() const {
    return _size_x;
}

int HeightMap::getSizeY() const {
    return _size_y;
}

int HeightMap::getDistanceFromOutOfBounds(int x, int y) {
    int distance_x = std::min(x + 1, std::abs(x - _size_x)),
        distance_y = std::min(y + 1, std::abs(y - _size_y));
    return std::min(distance_x, distance_y);
}

void HeightMap::setHeights(float** heights) {
    for (int y = 0; y < _size_y; y++) {
        for (int x = 0; x < _size_x; x++) _heights[x][y] = heights[x][y];
    }
}

float HeightMap::operator()(int x, int y) const {
    return _heights.at(x).at(y);
}
