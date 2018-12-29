#include "window.h"

const char *DEFAULT_WINDOW_TITLE = "CLI Map Generator";
const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 800;

Window::Window(void) {
    _window = SDL_CreateWindow(
        DEFAULT_WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    _windowSurface = SDL_GetWindowSurface(_window);
    _windowContext = SDL_GL_CreateContext(_window);
    _isOpen = true;
    glewInit();
}

Window::Window(std::string title, int width, int height) {
    _window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    _windowSurface = SDL_GetWindowSurface(_window);
    _windowContext = SDL_GL_CreateContext(_window);
    _isOpen = true;
    glewInit();
}

Window::~Window(void) {
    SDL_GL_DeleteContext(_windowContext);
    SDL_FreeSurface(_windowSurface);
    SDL_DestroyWindow(_window);
}

void Window::update() {
    SDL_GL_SwapWindow(_window);
}

void Window::processEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            _isOpen = false;
        }
    }
}

void Window::clear() {
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isOpen() {
    return _isOpen;
}
