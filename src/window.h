#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>

class Window {
public:
    Window();
    ~Window();
    bool init();
    void free();

    SDL_Renderer* createRenderer();
    void handleEvent(SDL_Event& e);

    int getWidth();
    int getHeight();

    bool getMouseFocus();
    bool getKeyboardFocus();
    bool getMinimized();
    bool getFullScreen();

private:
    SDL_Window* sdlWindow;

    int width;
    int height;

    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
};

#endif
