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
        GLWindow(void);
        GLWindow(std::string, int, int);
        ~GLWindow(void);
        void update(void);
        void processEvents(void);
        void clear(void);
        bool isOpen(void);
};

#endif
