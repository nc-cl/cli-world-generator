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

void GenMap::_setMapFromNoise(float** height, float** rfall, float** temp) {
    int equatorIndex = _sizeY / 2;
    int tropicRange = abs(equatorIndex - _sizeY/3);

    int equatorDistance;
    float tempMod;

    for (int y = 0; y < _sizeY; y++) {
        equatorDistance = abs(equatorIndex - y);

        if (equatorDistance <= tropicRange) {
            tempMod = max(0.5f - equatorDistance*0.01f, 0.2f);
        } else {
            tempMod = max(0.5f - equatorDistance*0.02f, -0.2f);
        }

        for (int x = 0; x < _sizeX; x++) {
            _map[x][y].setHeight(height[x][y]);
            _map[x][y].setRainfall(rfall[x][y]);
            _map[x][y].setTemperature(max(temp[x][y] + tempMod, 0.0f));
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
        3.0f,
        DEFAULT_PERSISTENCE,
        _sizeX,
        _sizeY,
        NoiseUtil::getWhiteNoise(_sizeX,_sizeY));

    float** temperatureNoise = NoiseUtil::getPerlinNoise(
        DEFAULT_OCTAVES,
        3.0f,
        DEFAULT_PERSISTENCE,
        _sizeX,
        _sizeY,
        NoiseUtil::getWhiteNoise(_sizeX,_sizeY));

    int maxDistanceFromBorder = max(min(_sizeX, _sizeY) / 5, 1);

    for (int x = 0; x < _sizeX; x++) {
        for (int y = 0; y < _sizeY; y++) {
            int distanceFromBorder = _getDistanceFromOutOfBounds(x, y);

            if (distanceFromBorder <= maxDistanceFromBorder) {
                heightNoise[x][y] -= distanceFromBorder == 1 ? 1 : 0.04f * abs(distanceFromBorder - (maxDistanceFromBorder + 1));
            }

            heightNoise[x][y] = max(heightNoise[x][y], 0.0f);
        }
    }

    _setMapFromNoise(heightNoise, rainfallNoise, temperatureNoise);
}

void GenMap::printMap(bool useColor) {
    stringstream strstr;

    for (int y = _sizeY-1; y > -1; y--) {
        for (int x = 0; x < _sizeX; x++) {
            strstr << _map[x][y].getBiomeString(useColor);
        }

        strstr << endl;
    }

    cout << strstr.str();
}
