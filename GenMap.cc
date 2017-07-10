#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "GenMap.h"

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
        case DIRECTION_NE:
        case DIRECTION_E:
        case DIRECTION_SE:
            adjX++;
            break;
        case DIRECTION_SW:
        case DIRECTION_W:
        case DIRECTION_NW:
            adjX--;
    }

    switch (dir) {
        case DIRECTION_NW:
        case DIRECTION_N:
        case DIRECTION_NE:
            adjY++;
            break;
        case DIRECTION_SE:
        case DIRECTION_S:
        case DIRECTION_SW:
            adjY--;
            break;
    }

    GenMapNode node;

    try {
        node = _map.at(adjY).at(adjX);
    } catch (const out_of_range& e) {
        node = GenMapNode(BIOME_NULL);
    }

    return node;
}

int GenMap::_getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = min(x + 1, abs(x - _sizeX));
    int distanceY = min(y + 1, abs(y - _sizeY));
    return min(distanceX, distanceY);
}

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

int GenMap::getArea() {
    return _sizeX * _sizeY;
}

void GenMap::generateLand() {
    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            if (_map[i][j].getBiome() == BIOME_GRASSLAND) {
                continue;
            }

            int adjBiome;
            int adjLandCount = 0;

            for (unsigned int k = 0; k < DIRECTIONS.size(); k++) {
                adjBiome = _getAdjacent(j, i, DIRECTIONS[k]).getBiome();

                if (adjBiome == BIOME_GRASSLAND) {
                    adjLandCount++;
                }
            }

            int distanceFromOob = _getDistanceFromOutOfBounds(j, i);

            float landChance = 0.0;

            if (distanceFromOob > 1) {
                if (distanceFromOob < 4) {
                    landChance -= 0.6 / distanceFromOob;
                }

                landChance = max(landChance + min(adjLandCount*0.475, 0.99), 0.01);
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

    for (int i = _sizeY - 1; i > -1; i--) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[i][j].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
