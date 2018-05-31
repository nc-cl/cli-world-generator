#include "gl_window.h"

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
