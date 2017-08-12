#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "GenMap.h"
#include "NoiseUtil.h"

void GenMap::_initMap() {
    _map.resize(_sizeY);

    for (int i = 0; i < _sizeY; i++) {
        _map[i].resize(_sizeX);
    }
}

GenMapNode GenMap::_getAdjacent(int x, int y, int dir) {
    int adjX = x;
    int adjY = y;

    switch (dir) {
        case DIRECTION_N:
            adjY++;
            break;
        case DIRECTION_E:
            adjX++;
            break;
        case DIRECTION_S:
            adjY--;
            break;
        case DIRECTION_W:
            adjX--;
    }

    GenMapNode node;

    try {
        node = _map.at(adjY).at(adjX);
    } catch (const out_of_range& e) {
        node = GenMapNode(BIOME_SEA);
    }

    return node;
}

int GenMap::_getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = min(x + 1, abs(x - _sizeX));
    int distanceY = min(y + 1, abs(y - _sizeY));
    return min(distanceX, distanceY);
}

void GenMap::_setMapFromPerlinNoise(float** noise) {
    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            _map[i][j].setBiome(floor(noise[i][j] + 0.5));
        }
    }
}

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

void GenMap::generate(float lacunarity, float persistence) {
    NoiseUtil noiseUtil(_sizeX, _sizeY);
    _setMapFromPerlinNoise(noiseUtil.getPerlinNoise(4, lacunarity, persistence));
}

void GenMap::printMap(bool useColor, bool matchMapData) {
    stringstream strstr;
    int yIndexStart = matchMapData ? -(_sizeY - 1) : 0;
    int yIndexEnd = matchMapData ? 1 : _sizeY;

    for (int i = yIndexStart; i < yIndexEnd; i++) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[abs(i)][j].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
