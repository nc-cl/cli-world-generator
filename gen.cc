#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"
#include "NoiseGenerator.cc"

using namespace std;

int main(int argc, char* argv[]) {
    int width = DEFAULT_SIZE_X;
    int height = DEFAULT_SIZE_Y;

    int octaves = DEFAULT_OCTAVES;
    float lacunarity = DEFAULT_LACUNARITY;
    float persistence = DEFAULT_PERSISTENCE;

    int temperature = 50;

    bool useColor = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-x") == 0) {
            if (i + 1 < argc) {
                try {
                    width = stoi(argv[i+1]);
                    i++;
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--height") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-y") == 0) {
            if (i + 1 < argc) {
                try {
                    height = stoi(argv[i+1]);
                    i++;
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                try {
                    width = stoi(argv[i+1]);
                    i++;

                    if (i + 1 < argc) {
                        height = stoi(argv[i+1]);
                        i++;
                    }
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--octaves") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                try {
                    octaves = stoi(argv[i+1]);
                    i++;
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--persistence") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                try {
                    persistence = stof(argv[i+1]);
                    i++;
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--lacunarity") == 0 || strcmp(argv[i], "-l") == 0) {
            if (i + 1 < argc) {
                try {
                    lacunarity = stof(argv[i+1]);
                    i++;
                } catch (const invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--temperature") == 0 || strcmp(argv[i], "-t") == 0) {
            try {
                temperature = stoi(argv[i+1]);
                i++;
            } catch (const invalid_argument& e) {}
        } else if (strcmp(argv[i], "--no-color") == 0 || strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    srand(time(NULL));

    GenMap gmap(width, height);

    temperature = max(min(temperature, 100), 0);
    float tempMod = (temperature - 50) / 100.0f * 2;

    float** heightNoise = NoiseGenerator::getPerlinNoise(
        octaves,
        lacunarity,
        persistence,
        width,
        height,
        NoiseGenerator::getWhiteNoise(width, height));

    float** rainfallNoise = NoiseGenerator::getPerlinNoise(
        DEFAULT_OCTAVES,
        3.0f,
        DEFAULT_PERSISTENCE,
        width,
        height,
        NoiseGenerator::getWhiteNoise(width,height));

    float** temperatureNoise = NoiseGenerator::getPerlinNoise(
        DEFAULT_OCTAVES,
        3.0f,
        DEFAULT_PERSISTENCE,
        width,
        height,
        NoiseGenerator::getWhiteNoise(width,height));

    int maxDistanceFromBorder = max(min(width, height) / 5, 1);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int distanceFromBorder = gmap.getDistanceFromOutOfBounds(x, y);

            if (distanceFromBorder <= maxDistanceFromBorder) {
                heightNoise[x][y] -= distanceFromBorder == 1 ? 1 : 0.04f * abs(distanceFromBorder - (maxDistanceFromBorder + 1));
            }

            heightNoise[x][y] = max(heightNoise[x][y], 0.0f);

            temperatureNoise[x][y] += tempMod;
            temperatureNoise[x][y] = max(min(temperatureNoise[x][y], 1.0f), 0.0f);
        }
    }

    gmap.setMapFromNoise(heightNoise, rainfallNoise, temperatureNoise);
    gmap.printMap(useColor);

    return 0;
}
