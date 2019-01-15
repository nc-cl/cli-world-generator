#ifndef NOISE_UTIL_H_
#define NOISE_UTIL_H_

#include <stdlib.h>
#include <math.h>
#include <algorithm>

namespace noise_util {
    const int DEFAULT_OCTAVES = 4;
    const float DEFAULT_LACUNARITY = 2.0f;
    const float DEFAULT_PERSISTENCE = 0.4f;

    namespace {
        float** getEmpty2dArray(int size_x, int size_y) {
            float** arr = new float*[size_x];

            for (int i = 0; i < size_x; i++) {
                arr[i] = new float[size_y];
                for (int j = 0; j < size_y; j++) arr[i][j] = 0.0f;
            }

            return arr;
        }

        float lerp(float val1, float val2, float alpha) {
            return (1 - alpha) * val1 + alpha * val2;
        }

        float** getOctave(float** noise, int octave_no, float lacunarity, int size_x, int size_y) {
            float** octave = getEmpty2dArray(size_x, size_y);
            int wlen = std::pow(lacunarity, octave_no);
            float freq = 1.0f / wlen;

            for (int i = 0; i < size_x; i++) {
                int i0 = i / wlen * wlen;
                int i1 = (i0 + wlen) % size_x;
                float hblend = (i - i0) * freq;

                for (int j = 0; j < size_y; j++) {
                    int j0 = j / wlen * wlen;
                    int j1 = (j0 + wlen) % size_y;
                    float vblend = (j - j0) * freq;

                    float bottom = lerp(noise[i0][j0], noise[i1][j0], hblend);
                    float top = lerp(noise[i0][j1], noise[i1][j1], hblend);
                    octave[i][j] = lerp(bottom, top, vblend);
                }
            }

            return octave;
        }
    }

    float** getWhiteNoise(int size_x, int size_y) {
        float** noise = getEmpty2dArray(size_x, size_y);

        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                noise[i][j] = 0.01f * (rand() % 100 + 1);
            }
        }

        return noise;
    }

    float** getPerlinNoise(int num_octaves, float lacunarity, float persistence, int size_x, int size_y, float** noise) {
        num_octaves = std::max(num_octaves, 0);
        lacunarity = std::max(lacunarity, 1.0f);
        persistence = std::max(persistence, 0.01f);

        float** pnoise = getEmpty2dArray(size_x, size_y);
        float*** octaves = new float**[num_octaves];

        float amp = 1.0f;
        float totalAmp = 0.0f;

        for (int o = num_octaves - 1; o >= 0; o--) {
            octaves[o] = getOctave(noise, o, lacunarity, size_x, size_y);

            amp *= persistence;
            totalAmp += amp;

            for (int i = 0; i < size_x; i++) {
                for (int j = 0; j < size_y; j++) {
                    pnoise[i][j] += octaves[o][i][j] * amp;
                    if (o == 0) pnoise[i][j] /= totalAmp;
                }
            }
        }

        return pnoise;
    }

    float** getPerlinNoise(int num_octaves, float lacunarity, float persistence, int size_x, int size_y) {
        float** noise = getWhiteNoise(size_x, size_y);
        return getPerlinNoise(num_octaves, lacunarity, persistence, size_x, size_y, noise);
    }
}

#endif
