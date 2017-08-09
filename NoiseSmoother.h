#ifndef NOISE_SMOOTHER_H_
#define NOISE_SMOOTHER_H_

using namespace std;

const int X = 120;
const int Y = 40;

class NoiseSmoother {
    private:
        static float _lerp(float val1, float val2, float alpha) {
            return (1 - alpha) * val1 + alpha * val2;
        }
        
        static float** _getOctave(float** noise, int octaveNumber, int width, int height) {
            float** octave = _getEmpty2dArray();
            int wlen = 1 << octaveNumber;
            float freq = 1.0f / wlen;

            for (int i = 0; i < height; i++) {
                int i0 = i / wlen * wlen;
                int i1 = (i0 + wlen) % height;
                float vblend = (i - i0) * freq;

                for (int j = 0; j < width; j++) {
                    int j0 = j / wlen * wlen;
                    int j1 = (j0 + wlen) % width;
                    float hblend = (j- j0) * freq;

                    float left = _lerp(noise[i0][j0], noise[i1][j0], vblend);
                    float right = _lerp(noise[i0][j1], noise[i1][j1], vblend);
                    octave[i][j] = _lerp(left, right, hblend);
                }
            }

            return octave;
        }

        static float** _getWhiteNoise() {
            float** whiteNoise = _getEmpty2dArray();
            
            for (int i = 0; i < Y; i++) {
                for (int j = 0; j < X; j++) {
                    whiteNoise[i][j] = 0.01f * (rand() % 100 + 1);
                }
            }

            return whiteNoise;
        }

        static float** _getEmpty2dArray() {
            float** arr = new float*[Y];

            for (int i = 0; i < Y; i++) {
                arr[i] = new float[X];
            }

            return arr;
        }
    public:
        static float** getPerlinNoise(int numOctaves) {
            float** whiteNoise = _getWhiteNoise();
            float** perlinNoise = _getEmpty2dArray();
            float*** octaves = new float**[numOctaves];

            float amp = 1.0f;
            float totalAmp = 0.0f;
            float persistence = 0.5f;

            for (int o = numOctaves-1; o >= 0; o--) {
                octaves[o] = _getOctave(whiteNoise, o, X, Y);

                amp *= persistence;
                totalAmp += amp;

                for (int i = 0; i < Y; i++) {
                    for (int j = 0; j < X; j++) {
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
