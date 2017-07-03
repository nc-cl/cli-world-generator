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
    int randomX, randomY;

    for (int i = 0; i < ceil(getArea() / 50); i++) {
        randomX = max(min(rand() % _sizeX, _sizeX - 2), 1);
        randomY = max(min(rand() % _sizeY, _sizeY - 2), 1);
        _map[randomY][randomX].setBiome(BIOME_GRASSLAND);
    }

    int distanceFromOobY, distanceFromOobX, distanceFromOob;

    for (int i = 0; i < _sizeY; i++) {
        distanceFromOobY = min(i + 1, abs(i - _sizeY));

        for (int j = 0; j < _sizeX; j++) {
            if (_map[i][j].getBiome() == BIOME_GRASSLAND) {
                continue;
            }

            int adjBiome;
            int adjLandCount = 0;

            for (unsigned int k = 0; k < DIRECTIONS.size(); k++) {
                adjBiome = _getBiomeAtDistance(j, i, DIRECTIONS[k], 1);

                if (adjBiome == BIOME_GRASSLAND) {
                    adjLandCount++;
                }
            }

            distanceFromOobX = min(j + 1, abs(j - _sizeX));
            distanceFromOob = min(distanceFromOobX, distanceFromOobY);

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

    for (int i = 0; i < _sizeY; i++) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[i][j].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
