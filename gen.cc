#include <iostream>
#include <string.h>
#include "GenMap.cc"
#include "GenMapNode.cc"

using namespace std;

int main(int argc, char* argv[]) {
    int width = DEFAULT_SIZE_X;
    int height = DEFAULT_SIZE_Y;

    int octaves = DEFAULT_OCTAVES;
    float lacunarity = DEFAULT_LACUNARITY;
    float persistence = DEFAULT_PERSISTENCE;

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
        } else if (strcmp(argv[i], "--no-color") == 0 || strcmp(argv[i], "-nc") == 0) {
            useColor = false;
        }
    }

    srand(time(NULL));

    GenMap gmap(width, height);
    gmap.generate(octaves, lacunarity, persistence);
    gmap.printMap(useColor);

    return 0;
}
