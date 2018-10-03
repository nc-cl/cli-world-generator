#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#ifndef SDL_WINDOW_H_
#define SDL_WINDOW_H_

class SDLWindow {
    private:
        SDL_Window* _window; 
        SDL_GLContext _windowContext;
        bool _isOpen;
    public:
        SDLWindow(void);
        SDLWindow(std::string, int, int);
        ~SDLWindow(void);
        void update(void);
        void processEvents(void);
        void clear(void);
        bool isOpen(void);
};

#endif
