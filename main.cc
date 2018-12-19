#include <string.h>
#include <iostream>
#include <ctime>
#include "world_map.h"
#include "noise_generator.h"

#if __has_include(<SDL2/SDL.h>)
#include "sdl_window.h"
#define SDL_EXISTS 1
#else
#define SDL_EXISTS 0
#endif

int main(int argc, char* argv[]) {
    int width = DEFAULT_SIZE_X;
    int height = DEFAULT_SIZE_Y;

    int octaves = DEFAULT_OCTAVES;
    float lacunarity = DEFAULT_LACUNARITY;
    float persistence = DEFAULT_PERSISTENCE;

    bool useColour = true;
    bool useGui = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-x") == 0) {
            if (i + 1 < argc) {
                try {
                    width = std::stoi(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--height") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-y") == 0) {
            if (i + 1 < argc) {
                try {
                    height = std::stoi(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                try {
                    width = std::stoi(argv[i+1]);
                    i++;

                    if (i + 1 < argc) {
                        height = std::stoi(argv[i+1]);
                        i++;
                    }
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--octaves") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                try {
                    octaves = std::stoi(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--persistence") == 0 || strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                try {
                    persistence = std::stof(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--lacunarity") == 0 || strcmp(argv[i], "-l") == 0) {
            if (i + 1 < argc) {
                try {
                    lacunarity = std::stof(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--temperature") == 0 || strcmp(argv[i], "-t") == 0) {
            try {
                // temporarily removed
                //temperature = std::stoi(argv[i+1]);
                i++;
            } catch (const std::invalid_argument& e) {}
        } else if (strcmp(argv[i], "--no-colour") == 0 || strcmp(argv[i], "--no-color") == 0 || strcmp(argv[i], "-nc") == 0) {
            useColour = false;
        } else if (strcmp(argv[i], "--gui") == 0) {
            useGui = true;
        }
    }

    srand(time(NULL));

    WorldMap wmap(width, height);

    float** heightNoise = NoiseGenerator::getPerlinNoise(
        octaves,
        lacunarity,
        persistence,
        width,
        height,
        NoiseGenerator::getWhiteNoise(width, height));

    int maxDistanceFromBorder = std::max(std::min(width, height) / 5, 1);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int distanceFromBorder = wmap.getDistanceFromOutOfBounds(x, y);

            if (distanceFromBorder <= maxDistanceFromBorder) {
                heightNoise[x][y] -= distanceFromBorder == 1 ? 1 : 0.04f * std::abs(distanceFromBorder - (maxDistanceFromBorder + 1));
            }

            heightNoise[x][y] = std::max(heightNoise[x][y], 0.0f);
        }
    }

    if (useGui) {
        #if SDL_EXISTS
        SDL_Init(SDL_INIT_EVERYTHING);
        SDLWindow window("Map Generator", 600, 600);

        while (window.isOpen()) {
            window.clear();
            window.update();
            window.processEvents();
        }

        SDL_Quit();
        #else
        std::cout << "SDL not found." << std::endl;
        #endif
    } else {
        wmap.setMapFromNoise(heightNoise);
        wmap.printMap(useColour);
    }

    return EXIT_SUCCESS;
}
