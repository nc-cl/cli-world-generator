#include "gl_window.h"

GLWindow::GLWindow(std::string title, int sizeX, int sizeY) {
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

GLWindow::~GLWindow(void) {
    SDL_GL_DeleteContext(_windowContext);
    SDL_DestroyWindow(_window);
}

void GLWindow::update() {
    SDL_GL_SwapWindow(_window);
}

void GLWindow::processEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            _isOpen = false;
        }
    }
}

void GLWindow::clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool GLWindow::isOpen() {
    return _isOpen;
}
