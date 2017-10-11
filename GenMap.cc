#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "GenMap.h"

void GenMap::_initMap() {
    _map.resize(_sizeX);

    for (int i = 0; i < _sizeX; i++) {
        _map[i].resize(_sizeY);
    }
}

int GenMap::getWidth() {
    return _sizeX;
}

int GenMap::getHeight() {
    return _sizeY;
}

int GenMap::getDistanceFromOutOfBounds(int x, int y) {
    int distanceX = min(x + 1, abs(x - _sizeX));
    int distanceY = min(y + 1, abs(y - _sizeY));
    return min(distanceX, distanceY);
}

void GenMap::setMapFromNoise(float** height, float** rfall, float** temp) {
    int equatorIndex = _sizeY / 2;
    int tropicRange = abs(equatorIndex - _sizeY/3);
    int equatorDistance;

    float yMod = (float) max(1, 10 - (int) floor(_sizeY / 10));
    float tempMod, minTempMod;

    for (int y = 0; y < _sizeY; y++) {
        equatorDistance = abs(equatorIndex - y);
        minTempMod = equatorDistance <= tropicRange ? 0.05f : -0.05f;
        tempMod = max(minTempMod, 0.5f - equatorDistance * yMod * 0.02f);

        for (int x = 0; x < _sizeX; x++) {
            _map[x][y].setHeight(height[x][y]);
            _map[x][y].setRainfall(rfall[x][y]);
            _map[x][y].setTemperature(max(0.0f, temp[x][y] + tempMod));
        }
    }
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
