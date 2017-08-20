#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "GenMap.h"
#include "NoiseUtil.h"

void GenMap::_initMap() {
    _map.resize(_sizeX);

    for (int i = 0; i < _sizeX; i++) {
        _map[i].resize(_sizeY);
    }
}

int GenMap::_getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = min(x + 1, abs(x - _sizeX));
    int distanceY = min(y + 1, abs(y - _sizeY));
    return min(distanceX, distanceY);
}

void GenMap::_setMapFromNoise(float** height, float** rfall) {
    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            _map[i][j].setHeight(height[i][j]);
            _map[i][j].setRainfall(rfall[i][j]);
        }
    }
}

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

void GenMap::generate(int octaves, float lacunarity, float persistence) {
    float** heightNoise = NoiseUtil::getPerlinNoise(
        octaves,
        lacunarity,
        persistence,
        _sizeX,
        _sizeY,
        NoiseUtil::getWhiteNoise(_sizeX, _sizeY));

    float** rainfallNoise = NoiseUtil::getPerlinNoise(
        DEFAULT_OCTAVES,
        DEFAULT_LACUNARITY,
        DEFAULT_PERSISTENCE,
        _sizeX,
        _sizeY,
        NoiseUtil::getWhiteNoise(_sizeX,_sizeY));

    int maxDistanceFromBorder = max(min(_sizeX, _sizeY) / 5, 1);

    for (int i = 0; i < _sizeX; i++) {
        for (int j = 0; j < _sizeY; j++) {
            int distanceFromBorder = _getDistanceFromOutOfBounds(i, j);

            if (distanceFromBorder <= maxDistanceFromBorder) {
                heightNoise[i][j] -= distanceFromBorder == 1 ? 1 : 0.04f * abs(distanceFromBorder - (maxDistanceFromBorder + 1));
            }

            heightNoise[i][j] = max(heightNoise[i][j], 0.0f);
        }
    }

    _setMapFromNoise(heightNoise, rainfallNoise);
}

void GenMap::printMap(bool useColor) {
    stringstream strstr;

    for (int i = _sizeY-1; i > -1; i--) {
        for (int j = 0; j < _sizeX; j++) {
            strstr << _map[j][i].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
