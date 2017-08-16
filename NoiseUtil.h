#ifndef NOISE_UTIL_H_
#define NOISE_UTIL_H_

using namespace std;

const int DEFAULT_OCTAVES = 4;
const float DEFAULT_LACUNARITY = 2.0f;
const float DEFAULT_PERSISTENCE = 0.5f;

class NoiseUtil {
    private:
        static float** _getEmpty2dArray(int width, int height) {
            float** arr = new float*[width];

            for (int i = 0; i < width; i++) {
                arr[i] = new float[height];
            }

            return arr;
        }

        static float** _getOctave(float** noise, int octaveNumber, float lacunarity, int width, int height) {
            float** octave = NoiseUtil::_getEmpty2dArray(width, height);
            int wlen = pow(lacunarity, octaveNumber);
            float freq = 1.0f / wlen;

            for (int i = 0; i < width; i++) {
                int i0 = i / wlen * wlen;
                int i1 = (i0 + wlen) % width;
                float hblend = (i - i0) * freq;

                for (int j = 0; j < height; j++) {
                    int j0 = j / wlen * wlen;
                    int j1 = (j0 + wlen) % height;
                    float vblend = (j - j0) * freq;

                    float bottom = NoiseUtil::_lerp(noise[i0][j0], noise[i1][j0], hblend);
                    float top = NoiseUtil::_lerp(noise[i0][j1], noise[i1][j1], hblend);
                    octave[i][j] = NoiseUtil::_lerp(bottom, top, vblend);
                }
            }

            return octave;
        }

        static float _lerp(float val1, float val2, float alpha) {
            return (1 - alpha)*val1 + alpha*val2;
        }
    public:
        static float** getWhiteNoise(int width, int height) {
            float** whiteNoise = NoiseUtil::_getEmpty2dArray(width, height);

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    whiteNoise[i][j] = 0.01f * (rand() % 100 + 1);
                }
            }

            return whiteNoise;
        }

        static float** getPerlinNoise(int numOctaves, float lacunarity, float persistence, int width, int height) {
            float** whiteNoise = NoiseUtil::getWhiteNoise(width, height);
            return NoiseUtil::getPerlinNoise(numOctaves, lacunarity, persistence, width, height, whiteNoise);
        }

        static float** getPerlinNoise(int numOctaves, float lacunarity, float persistence, int width, int height, float** noise) {
            numOctaves = max(numOctaves, 0);
            lacunarity = max(lacunarity, 1.0f);
            persistence = max(persistence, 0.01f);


            float** perlinNoise = NoiseUtil::_getEmpty2dArray(width, height);
            float*** octaves = new float**[numOctaves];

            float amp = 1.0f;
            float totalAmp = 0.0f;

            for (int o = numOctaves-1; o >= 0; o--) {
                octaves[o] = NoiseUtil::_getOctave(noise, o, lacunarity, width, height);

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
};

#endif
