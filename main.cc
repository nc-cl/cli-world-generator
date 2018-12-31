#include <string.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "world_map.h"
#include "noise_generator.h"

#if __has_include(<SDL2/SDL.h>) && __has_include(<GL/glew.h>) && __has_include(<glm/glm.hpp>)
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl_shader_handler.h"
#define HAS_3D_DEPENDENCIES 1
const char *WINDOW_TITLE = "CLI World Generator";
const unsigned int DEFAULT_WINDOW_SIZE_X = 800;
const unsigned int DEFAULT_WINDOW_SIZE_Y = 800;

#else
#define HAS_3D_DEPENDENCIES 0
#endif

int main(int argc, char *argv[]) {
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
        #if HAS_3D_DEPENDENCIES
        SDL_Init(SDL_INIT_EVERYTHING);

        struct {
            unsigned int window_x;
            unsigned int window_y;
            SDL_Window* window;
            SDL_Surface* surface;
            SDL_GLContext context;
        } sdl;

        sdl.window_x = DEFAULT_WINDOW_SIZE_X;
        sdl.window_y = DEFAULT_WINDOW_SIZE_Y;
        sdl.window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            sdl.window_x,
            sdl.window_y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        sdl.surface = SDL_GetWindowSurface(sdl.window);
        sdl.context = SDL_GL_CreateContext(sdl.window);
        glewInit();

        // GL settings
        glEnable(GL_PRIMITIVE_RESTART);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Vertex generation
        const unsigned int v_width = width + 1, v_height = height + 1,
            num_vertices = v_width * v_height;
        std::vector<GLfloat> vertices;

        const float vertex_step = 0.2f;
        for (int i = 0; i < num_vertices; i++) {
            vertices.push_back((i % v_width) * vertex_step);
            vertices.push_back((i / v_width) * vertex_step);
            vertices.push_back(0.0f);
            vertices.push_back(0.00f);
            vertices.push_back(0.25f);
            vertices.push_back(0.00f);
        }

        // Vertex indices
        const unsigned int num_indices = ((v_width * 2) * height) + height;
        std::vector<GLuint> indices;

        GLuint restart_i = 0xFFFFFFFF;
        for (int i = 0; indices.size() < num_indices; i++) {
            indices.push_back(i);
            indices.push_back(i + v_width);

            if ((i + 1) % v_width == 0) {
                indices.push_back(restart_i);
            }
        }
        glPrimitiveRestartIndex(restart_i);


        // Buffer vertex + index data
        GLuint v_buff, e_buff, vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &v_buff);
        glBindBuffer(GL_ARRAY_BUFFER, v_buff);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &e_buff);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_buff);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // Shader compilation + linking
        GlShaderHandler glsh;
        try {
            glsh.compileShader(GL_VERTEX_SHADER, "default.vert");
            glsh.compileShader(GL_FRAGMENT_SHADER, "default.frag");
            glsh.linkShaders();
        } catch (const std::string e) {
            std::cout << e;
            return EXIT_FAILURE;
        }
        GLuint shader = glsh.getProgram();

        SDL_Event e;
        bool running = true;

        float x_center = (float)v_width / 2.0f * -vertex_step,
            y_center = (float)v_height / 2.0f * -vertex_step;

        do {
            glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 model(1), view(1), projection(1);
            // Model matrix
            model = glm::translate(model, glm::vec3(x_center, y_center, -2.0f));

            // View matrix
            view = glm::rotate(view, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, glm::radians( 45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            // Projection matrix
            projection = glm::perspective(glm::radians(80.0f), (float)(sdl.window_x/sdl.window_y), 0.01f, 100.0f);

            glUseProgram(shader);
            GLint model_l = glGetUniformLocation(shader, "model"),
                  view_l = glGetUniformLocation(shader, "view"),
                  projection_l = glGetUniformLocation(shader, "projection");
            glUniformMatrix4fv(model_l, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(view_l, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projection_l, 1, GL_FALSE, glm::value_ptr(projection));

            glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, 0);
            glFinish();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            SDL_GL_SwapWindow(sdl.window);

            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) running = false;
            }
        } while (running);

        SDL_GL_DeleteContext(sdl.context);
        SDL_FreeSurface(sdl.surface);
        SDL_DestroyWindow(sdl.window);
        SDL_Quit();

        #else
        std::cout << "SDL not found." << std::endl;
        return EXIT_FAILURE;
        #endif
    } else {
        wmap.setMapFromNoise(heightNoise);
        wmap.printMap(useColour);
    }

    return EXIT_SUCCESS;
}
