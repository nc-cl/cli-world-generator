#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <algorithm>
#include <array>
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
    }

    int randomX, randomY;

    for (int i = 0; i < ceil(getArea() / 50); i++) {
        randomX = max(min(rand() % _sizeX, _sizeX - 2), 1);
        randomY = max(min(rand() % _sizeY, _sizeY - 2), 1);
        _map[randomY][randomX].setBiome(BIOME_GRASSLAND);
    }

    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            if (_map[i][j].getBiome() == BIOME_GRASSLAND) {
                continue;
            }

            array<int, 4> dirs = {
                DIRECTION_N,
                DIRECTION_E,
                DIRECTION_S,
                DIRECTION_W
            };

            int adj;
            int adjLandCount = 0;
            bool hasAdjOutOfBounds = false;

            for (unsigned int k = 0; k < dirs.size(); k++) {
                adj = _getAdjacentBiome(j, i, dirs[k]);

                if (adj == BIOME_GRASSLAND) {
                    adjLandCount++;
                } else if (adj == BIOME_NULL && !hasAdjOutOfBounds) {
                    hasAdjOutOfBounds = true;
                }
            }
            
            float landChance;

            if (hasAdjOutOfBounds) {
                landChance = 0.0;
            } else {
                landChance = max(min(adjLandCount * 0.5, 0.9), 0.01);
            }

            bool isLand = landChance*100 >= (rand() % 100) + 1;

            if (isLand) {
                _map[i][j].setBiome(BIOME_GRASSLAND);
            }
        }
    }
}

void GenMap::printMap(bool useColor) {
    stringstream strstr;

    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[i][j].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}

int GenMap::_getAdjacentBiome(int x, int y, int dir) {
    int adjX = x;
    int adjY = y;

    switch (dir) {
        case DIRECTION_N:
            adjY--;
            break;
        case DIRECTION_E:
            adjX++;
            break;
        case DIRECTION_S:
            adjY++;
            break;
        case DIRECTION_W:
            adjX--;
    }

    int biome;

    try {
        biome = _map.at(adjY).at(adjX).getBiome();
    } catch (const out_of_range& e) {
        biome = BIOME_NULL;
    }

    return biome;
}
