#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "noise_generator.h"

float** NoiseGenerator::_getEmpty2dArray(int width, int height) {
    float** arr = new float*[width];

    for (int i = 0; i < width; i++) {
        arr[i] = new float[height];
    }

    return arr;
}

float** NoiseGenerator::_getOctave(float** noise, int octaveNumber, float lacunarity, int width, int height) {
    float** octave = NoiseGenerator::_getEmpty2dArray(width, height);
    int wlen = std::pow(lacunarity, octaveNumber);
    float freq = 1.0f / wlen;

    for (int i = 0; i < width; i++) {
        int i0 = i / wlen * wlen;
        int i1 = (i0 + wlen) % width;
        float hblend = (i - i0) * freq;

        for (int j = 0; j < height; j++) {
            int j0 = j / wlen * wlen;
            int j1 = (j0 + wlen) % height;
            float vblend = (j - j0) * freq;

            float bottom = _lerp(noise[i0][j0], noise[i1][j0], hblend);
            float top = _lerp(noise[i0][j1], noise[i1][j1], hblend);
            octave[i][j] = _lerp(bottom, top, vblend);
        }
    }

    return octave;
}

float NoiseGenerator::_lerp(float val1, float val2, float alpha) {
    return (1 - alpha)*val1 + alpha*val2;
}

float** NoiseGenerator::getWhiteNoise(int width, int height) {
    float** whiteNoise = NoiseGenerator::_getEmpty2dArray(width, height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            whiteNoise[i][j] = 0.01f * (rand() % 100 + 1);
        }
    }

    return whiteNoise;
}

float** NoiseGenerator::getPerlinNoise(int numOctaves, float lacunarity, float persistence, int width, int height) {
    float** whiteNoise = NoiseGenerator::getWhiteNoise(width, height);
    return NoiseGenerator::getPerlinNoise(numOctaves, lacunarity, persistence, width, height, whiteNoise);
}

float** NoiseGenerator::getPerlinNoise(int numOctaves, float lacunarity, float persistence, int width, int height, float** noise) {
    numOctaves = std::max(numOctaves, 0);
    lacunarity = std::max(lacunarity, 1.0f);
    persistence = std::max(persistence, 0.01f);

    float** perlinNoise = NoiseGenerator::_getEmpty2dArray(width, height);
    float*** octaves = new float**[numOctaves];

    float amp = 1.0f;
    float totalAmp = 0.0f;

    for (int o = numOctaves-1; o >= 0; o--) {
        octaves[o] = NoiseGenerator::_getOctave(noise, o, lacunarity, width, height);

        amp *= persistence;
        totalAmp += amp;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                perlinNoise[i][j] += octaves[o][i][j] * amp;

                if (o == 0) {
                    perlinNoise[i][j] /= totalAmp;
                }
            }
        }
    }

    return perlinNoise;
}
