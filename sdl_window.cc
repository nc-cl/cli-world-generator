#include "sdl_window.h"

SDLWindow::SDLWindow(std::string title, int sizeX, int sizeY) {
    _window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        sizeX,
        sizeY,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    _windowContext = SDL_GL_CreateContext(_window);
    _isOpen = true;
    glewInit();
}

SDLWindow::~SDLWindow(void) {
    SDL_GL_DeleteContext(_windowContext);
    SDL_DestroyWindow(_window);
}

void SDLWindow::update() {
    SDL_GL_SwapWindow(_window);
}

void SDLWindow::processEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            _isOpen = false;
        }
    }
}

void SDLWindow::clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool SDLWindow::isOpen() {
    return _isOpen;
}
