#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include <chrono>
#include "height_map.h"
#include "noise_util.h"

#if __has_include(<SDL2/SDL.h>) && __has_include(<GL/glew.h>) && __has_include(<glm/glm.hpp>)
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_handler.h"
#include "height_map_mesh.h"
#define HAS_3D_DEPENDENCIES 1
const char *WINDOW_TITLE = "CLI World Generator";
const unsigned int DEFAULT_WINDOW_SIZE_X = 800;
const unsigned int DEFAULT_WINDOW_SIZE_Y = 800;

#else
#define HAS_3D_DEPENDENCIES 0
#endif

int main(int argc, char *argv[]) {
    int size_x = DEFAULT_SIZE_X;
    int size_y = DEFAULT_SIZE_Y;

    int octaves = noise_util::DEFAULT_OCTAVES;
    float lacunarity = noise_util::DEFAULT_LACUNARITY;
    float persistence = noise_util::DEFAULT_PERSISTENCE;

    bool print_map = false;
    bool print_map_colourless = false;
    bool use_wireframe_mode = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-x") == 0) {
            if (i + 1 < argc) {
                try {
                    size_x = std::stoi(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "-y") == 0) {
            if (i + 1 < argc) {
                try {
                    size_y = std::stoi(argv[i+1]);
                    i++;
                } catch (const std::invalid_argument& e) {}
            }
        } else if (strcmp(argv[i], "--size") == 0 || strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                try {
                    size_x = std::stoi(argv[i+1]);
                    i++;

                    if (i + 1 < argc) {
                        size_y = std::stoi(argv[i+1]);
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
        } else if (strcmp(argv[i], "--print") == 0) {
            print_map = true;
        } else if (strcmp(argv[i], "--print-colourless") == 0) {
            print_map_colourless = true;
        } else if (strcmp(argv[i], "-f") == 0) {
            use_wireframe_mode = true;
        }
    }

    srand(time(NULL));

    HeightMap hmap(size_x, size_y);

    float** heightNoise = noise_util::getPerlinNoise(
        octaves,
        lacunarity,
        persistence,
        size_x,
        size_y,
        noise_util::getWhiteNoise(size_x, size_y));

    int max_border_dist = std::max(std::min(size_x, size_y) / 5, 1);

    for (int x = 0; x < size_x; x++) {
        for (int y = 0; y < size_y; y++) {
            int distanceFromBorder = hmap.getDistanceFromOutOfBounds(x, y);

            if (distanceFromBorder <= max_border_dist) {
                heightNoise[x][y] -= distanceFromBorder == 1 ? 1 : 0.04f * std::abs(distanceFromBorder - (max_border_dist + 1));
            }

            heightNoise[x][y] = std::max(heightNoise[x][y], 0.0f);
        }
    }

    hmap.setHeights(heightNoise);

    if (print_map || print_map_colourless || !HAS_3D_DEPENDENCIES) {
        std::stringstream ss;

        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                if (hmap(x, y) >= 0.45f) {
                    // bg colour = 233; fg colour = 40
                    ss << (print_map_colourless ? "GG" : "\033[48;5;233m\033[38;5;40mGG\033[0m");
                } else {
                    // bg colour = 0; fg colour = 27
                    ss << (print_map_colourless ? "~~" : "\033[48;5;0m\033[38;5;27m~~\033[0m");
                }
            }
            ss << "\n";
        }
        std::cout << ss.str();
    }

    #if HAS_3D_DEPENDENCIES
    SDL_Init(SDL_INIT_EVERYTHING);

    struct {
        unsigned int window_x;
        unsigned int window_y;
        SDL_Window* window;
        SDL_Surface* surface;
        SDL_GLContext context;
    } sdl_state;

    sdl_state.window_x = DEFAULT_WINDOW_SIZE_X;
    sdl_state.window_y = DEFAULT_WINDOW_SIZE_Y;
    sdl_state.window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        sdl_state.window_x,
        sdl_state.window_y,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    sdl_state.surface = SDL_GetWindowSurface(sdl_state.window);
    sdl_state.context = SDL_GL_CreateContext(sdl_state.window);
    glewInit();

    // GL settings
    glEnable(GL_PRIMITIVE_RESTART);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if (use_wireframe_mode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    // Create mesh from map data
    HeightMapMesh hmap_mesh(&hmap);

    // Shader compilation + linking
    ShaderHandler glsh;
    try {
        glsh.compileShader(GL_VERTEX_SHADER, "default.vert");
        glsh.compileShader(GL_FRAGMENT_SHADER, "default.frag");
        glsh.linkShaders();
    } catch (const std::string e) {
        std::cerr << e;
        return EXIT_FAILURE;
    }
    GLuint shader = glsh.getProgram();

    SDL_Event e;
    bool running = true;

    float x_center = static_cast<float>(size_x) / 2.0f * -0.2f,
          y_center = static_cast<float>(size_y) / 2.0f * 0.2f;

    do {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1), view(1), projection(1);

        // Model matrix
        model = glm::translate(model, glm::vec3(x_center, y_center, -2.0f));

        // View matrix
        view = glm::rotate(view, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        // Projection matrix
        projection = glm::perspective(glm::radians(100.0f), static_cast<float>(sdl_state.window_x / sdl_state.window_y), 0.01f, 100.0f);

        glUseProgram(shader);
        GLint model_l = glGetUniformLocation(shader, "model"),
              view_l = glGetUniformLocation(shader, "view"),
              projection_l = glGetUniformLocation(shader, "projection");
        glUniformMatrix4fv(model_l, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_l, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projection_l, 1, GL_FALSE, glm::value_ptr(projection));

        hmap_mesh.draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        SDL_GL_SwapWindow(sdl_state.window);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
    } while (running);

    SDL_GL_DeleteContext(sdl_state.context);
    SDL_FreeSurface(sdl_state.surface);
    SDL_DestroyWindow(sdl_state.window);
    SDL_Quit();

    #else
    std::cerr << "\nMissing 3D dependencies.\n";
    return EXIT_FAILURE;
    #endif

    return EXIT_SUCCESS;
}
