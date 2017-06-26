#include <stdlib.h>
#include <math.h>
#include <algorithm>
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

            int adjBiome;
            int adjLandCount = 0;
            bool hasAdjOutOfBounds = false;

            for (unsigned int k = 0; k < DIRECTIONS.size(); k++) {
                adjBiome = _getBiomeAtDistance(j, i, DIRECTIONS[k], 1);

                if (adjBiome == BIOME_GRASSLAND) {
                    adjLandCount++;
                } else if (!hasAdjOutOfBounds && adjBiome == BIOME_NULL) {
                    hasAdjOutOfBounds = true;
                }
            }
            
            float landChance;

            if (hasAdjOutOfBounds) {
                landChance = 0.0;
            } else {
                landChance = max(min(adjLandCount * 0.475, 0.99), 0.01);
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

int GenMap::_getBiomeAtDistance(int x, int y, int dir, int dist) {
    int adjX = x;
    int adjY = y;

    switch (dir) {
        case DIRECTION_N:
            adjY -= dist;
            break;
        case DIRECTION_E:
            adjX += dist;
            break;
        case DIRECTION_S:
            adjY += dist;
            break;
        case DIRECTION_W:
            adjX -= dist;
    }

    int biome;

    try {
        biome = _map.at(adjY).at(adjX).getBiome();
    } catch (const out_of_range& e) {
        biome = BIOME_NULL;
    }

    return biome;
}

int GenMap::_getDistanceFromOutOfBounds(int x, int y) {
    int minDistance = max(_sizeX, _sizeY);
    
    for (unsigned int i = 0; i < DIRECTIONS.size(); i++) {
        bool oob = false;
        int distance = 1;

        while (!oob) {
            if (_getBiomeAtDistance(x, y, DIRECTIONS[i], distance) == BIOME_NULL) {
                minDistance = min(distance, minDistance);
                oob = true;
            } else {
                distance++;
            }
        }
    }

    return minDistance;
}
