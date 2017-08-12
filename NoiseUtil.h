#ifndef NOISE_UTIL_H_
#define NOISE_UTIL_H_

using namespace std;

const float DEFAULT_LACUNARITY = 2.0f;
const float DEFAULT_PERSISTENCE = 0.5f;

class NoiseUtil {
    private:
        int _sizeX, _sizeY;

        float** _getEmpty2dArray() {
            float** arr = new float*[_sizeY];

            for (int i = 0; i < _sizeY; i++) {
                arr[i] = new float[_sizeX];
            }

            return arr;
        }
        
        float** _getWhiteNoise() {
            float** whiteNoise = _getEmpty2dArray();

            for (int i = 0; i < _sizeY; i++) {
                for (int j = 0; j < _sizeX; j++) {
                    whiteNoise[i][j] = 0.01f * (rand() % 100 + 1);
                }
            }

            return whiteNoise;
        }

        float** _getOctave(float** noise, int octaveNumber, float lacunarity) {
            float** octave = _getEmpty2dArray();
            int wlen = pow(lacunarity, octaveNumber);
            float freq = 1.0f / wlen;

            for (int i = 0; i < _sizeY; i++) {
                int i0 = i / wlen * wlen;
                int i1 = (i0 + wlen) % _sizeY;
                float vblend = (i - i0) * freq;

                for (int j = 0; j < _sizeX; j++) {
                    int j0 = j / wlen * wlen;
                    int j1 = (j0 + wlen) % _sizeX;
                    float hblend = (j - j0) * freq;

                    float left = _lerp(noise[i0][j0], noise[i1][j0], vblend);
                    float right = _lerp(noise[i0][j1], noise[i1][j1], vblend);
                    octave[i][j] = _lerp(left, right, hblend);
                }
            }

            return octave;
        }

        float _lerp(float val1, float val2, float alpha) {
            return (1 - alpha)*val1 + alpha*val2;
        }
    public:
        NoiseUtil(int x, int y) : _sizeX(x), _sizeY(y) {}

        void setSize(int sizeX, int sizeY) {
            _sizeX = sizeX;
            _sizeY = sizeY;
        }

        float** getPerlinNoise(int numOctaves, float lacunarity, float persistence) {
            float** whiteNoise = _getWhiteNoise();
            float** perlinNoise = _getEmpty2dArray();
            float*** octaves = new float**[numOctaves];

            float amp = 1.0f;
            float totalAmp = 0.0f;

            for (int o = numOctaves-1; o >= 0; o--) {
                octaves[o] = _getOctave(whiteNoise, o, lacunarity);

                amp *= persistence;
                totalAmp += amp;

                for (int i = 0; i < _sizeY; i++) {
                    for (int j = 0; j < _sizeX; j++) {
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
