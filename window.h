#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {
    private:
        SDL_Window* _window;
        SDL_Surface* _windowSurface;
        SDL_GLContext _windowContext;
        bool _isOpen;
    public:
        Window(void);
        Window(std::string, int, int);
        ~Window(void);
        void update(void);
        void processEvents(void);
        void clear(void);
        bool isOpen(void);
};

#endif
