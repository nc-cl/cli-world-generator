#ifndef NOISE_GENERATOR_H_
#define NOISE_GENERATOR_H_

const int DEFAULT_OCTAVES = 4;
const float DEFAULT_LACUNARITY = 2.0f;
const float DEFAULT_PERSISTENCE = 0.4f;

class NoiseGenerator {
    private:
        static float** _getEmpty2dArray(int width, int height);
        static float** _getOctave(float** noise, int octave_no, float lacunarity, int width, int height);
        static float _lerp(float val1, float val2, float alpha);
    public:
        static float** getWhiteNoise(int width, int height);
        static float** getPerlinNoise(int num_octaves, float lacunarity, float persistence, int width, int height);
        static float** getPerlinNoise(int num_octaves, float lacunarity, float persistence, int width, int height, float** noise);
};

#endif
