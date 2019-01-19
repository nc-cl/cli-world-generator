#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "height_map.h"

HeightMap::HeightMap() {
    _heights.resize(1);
    _heights[0].resize(1, 0.0f);
}

HeightMap::HeightMap(const HeightMap *hmap) {
    _heights = hmap->getHeights();
}

HeightMap::HeightMap(int x, int y) {
    int size_x = std::max(x, 1),
        size_y = std::max(y, 1);
    _heights.resize(size_x);
    for (int i = 0; i < size_x; i++) _heights[i].resize(size_y, 0.0f);
}

void HeightMap::setHeights(std::vector<std::vector <float> > *heights) {
    _heights = *heights;
}

void HeightMap::setHeights(float **heights, int x, int y) {
    _heights.resize(x);

    for (int i = 0; i < x; i++) {
        _heights[i].resize(y);
        for (int j = 0; j < y; j++) _heights[i][j] = heights[i][j];
    }
}

std::vector<std::vector<float> > HeightMap::getHeights() const {
    return _heights;
}

int HeightMap::getSizeX() const {
    return _heights.size();
}

int HeightMap::getSizeY() const {
    return _heights[0].size();
}

float HeightMap::operator()(int x, int y) const {
    return _heights.at(x).at(y);
}

HeightMap HeightMap::operator+(HeightMap *other) {
    int result_x = other->getSizeX(),
        result_y = other->getSizeY();

    std::vector<std::vector<float> > result_h(result_x);
    HeightMap result;

    for (int i = 0; i < result_x; i++) {
        result_h[i].resize(result_y);
        for (int j = 0; j < result_y; j++)
            result_h[i][j] = std::clamp(_heights[i][j] + (*other)(i, j), 0.0f, 1.0f);
    }

    result.setHeights(&result_h);
    return result;
}