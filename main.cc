#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include <chrono>
#include "boost/program_options.hpp"
#include "height_map.h"
#include "height_map_settings_mask.h"
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
    // Map size
    int size_x = DEFAULT_SIZE_X;
    int size_y = DEFAULT_SIZE_Y;

    // Noise settings: have an impact on Perlin noise generation
    int octaves = noise_util::DEFAULT_OCTAVES;
    float lacunarity = noise_util::DEFAULT_LACUNARITY;
    float persistence = noise_util::DEFAULT_PERSISTENCE;

    // Map settings
    float sea_level = 0.45f;
    float border_val = 0.0f;
    float border_falloff = 0.04f;
    bool apply_map_border = true;

    // Additional program settings
    bool print_map = false;
    bool print_map_colourless = false;
    bool use_wireframe_mode = false;


    // Define command line options
    namespace opts = boost::program_options;

    opts::options_description opts_desc("Options");
    opts_desc.add_options()
        ("help", "Display all options")

        (",x", opts::value<int>(), "X dimension")
        (",y", opts::value<int>(), "Y dimension")

        ("octaves,o", opts::value<float>(), "Number of octaves")
        ("lacunarity,l", opts::value<float>(), "Perlin noise lacunarity")
        ("persistence,p", opts::value<float>(), "Perlin noise persistence")

        ("sea-level,s", opts::value<float>(), "Map sea level")
        ("border-value,b", opts::value<float>(), "Map border height")
        ("border-falloff,f", opts::value<float>(), "Map border height falloff")
        ("no-border", "Do not apply a border")

        ("wireframe,w", "Use wireframe mode")
        ("print", "Print map")
        ("print-nocol", "Print colourless map");

    opts::variables_map opts_vm;

    try {
        opts::store(opts::parse_command_line(argc, argv, opts_desc), opts_vm);
        opts::notify(opts_vm);
    } catch (opts::error& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    if (opts_vm.count("help")) {
        std::cout << opts_desc << "\n";
        return EXIT_SUCCESS;
    }

    // Process command line options; modify program variables accordingly
    if (opts_vm.count("-x")) size_x = opts_vm["-x"].as<int>();
    if (opts_vm.count("-y")) size_y = opts_vm["-y"].as<int>();

    if (opts_vm.count("octaves")) octaves = opts_vm["octaves"].as<float>();
    if (opts_vm.count("lacunarity")) lacunarity = opts_vm["lacunarity"].as<float>();
    if (opts_vm.count("persistence")) persistence = opts_vm["persistence"].as<float>();

    if (opts_vm.count("sea-level"))
        sea_level = std::min(std::max(opts_vm["sea-level"].as<float>(), 0.0f), 1.0f);
    if (opts_vm.count("border-value"))
        border_val = std::min(std::max(opts_vm["border-value"].as<float>(), 0.0f), 1.0f);
    if (opts_vm.count("border-falloff"))
        border_falloff = std::min(std::max(opts_vm["border-falloff"].as<float>(), -1.0f), 1.0f);
    if (opts_vm.count("no-border")) apply_map_border = false;

    if (opts_vm.count("wireframe")) use_wireframe_mode = true;
    if (opts_vm.count("print")) print_map = true;
    if (opts_vm.count("print-nocol")) print_map_colourless = true;


    // Begin generating the heightmap
    srand(time(NULL));

    float** hnoise = noise_util::getPerlinNoise(
        octaves,
        lacunarity,
        persistence,
        size_x,
        size_y,
        noise_util::getWhiteNoise(size_x, size_y));

    HeightMap hmap(size_x, size_y);
    hmap.setHeights(hnoise, size_x, size_y);

    // Apply settings that modify the map
    HeightMapSettingsMask hmap_settings(size_x, size_y);

    if (apply_map_border) {
        hmap_settings.applyBorder(border_val, border_falloff, sea_level, std::max(std::min(size_x, size_y) / 4, 1));
        hmap += &hmap_settings;
    }

    // Visualise the map as printed output (old functionality - retired to an option)
    if (print_map || print_map_colourless || !HAS_3D_DEPENDENCIES) {
        std::stringstream ss;

        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                if (hmap(x, y) >= sea_level) {
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

    // Begin setting up SDL and creating the mesh data
    // At this point, the program stops running if the necessary dependencies are missing
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

    // Calculate the center coordinates for the mesh - used in translating the mesh to the center
    // of the screen. TODO: Make the space between vertices (vertex_step) a program option + use
    // it to initialise the mesh, such that it's not repeated in HeightMapMesh
    float vertex_step = 0.2f;
    float x_center = static_cast<float>(size_x) / 2.0f * -vertex_step,
          y_center = static_cast<float>(size_y) / 2.0f * vertex_step;

    // Enter main loop
    SDL_Event e;
    bool running = true;

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
        projection = glm::perspective(
            glm::radians(100.0f),
            static_cast<float>(sdl_state.window_x / sdl_state.window_y),
            0.01f,
            100.0f);

        glUseProgram(shader);

        GLint sea_level_l = glGetUniformLocation(shader, "sea_level");
        glUniform1f(sea_level_l, sea_level);

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
    std::cerr << "\nMissing 3D dependencies - see readme\n";
    return EXIT_FAILURE;
    #endif

    return EXIT_SUCCESS;
}
