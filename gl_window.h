#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#ifndef GL_WINDOW_H_
#define GL_WINDOW_H_

class GLWindow {
    private:
        SDL_Window* _window; 
        SDL_GLContext _windowContext;
        bool _isOpen;
    public:
        GLWindow(std::string title, int sizeX, int sizeY) {
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
        ~GLWindow(void) {
            SDL_GL_DeleteContext(_windowContext);
            SDL_DestroyWindow(_window);
        }

        void update(void);
        void processEvents(void);
        void clear(void);
        bool isOpen(void);
};

#endif
