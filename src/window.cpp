#include <SDL.h>
#include <iostream>
#include <format>
#include "main.h"
#include "window.h"

Window::Window() {
    this->sdlWindow = nullptr ;
    this->mouseFocus = false;
    this->keyboardFocus = false;
    this->fullScreen = false;
    this->minimized = false;
    this->width = 0;
    this->height = 0;
}

Window::~Window() {
    this->free();
}

bool Window::init() {
    this->sdlWindow = SDL_CreateWindow("Tetris",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Global::INIT_WINDOW_WIDTH,
        Global::INIT_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!this->sdlWindow) {
        std::cout << std::format("Failed to create a window! SDL Error: {}\n", SDL_GetError());
        return false;
    }

    this->mouseFocus = true;
    this->keyboardFocus = true;
    this->width = Global::INIT_WINDOW_WIDTH;
    this->height = Global::INIT_WINDOW_HEIGHT;

    return true;
}

void Window::free() {
    if (this->sdlWindow) {
        SDL_DestroyWindow(this->sdlWindow);
    }
    this->mouseFocus = false;
    this->keyboardFocus = false;
    this->width = 0;
    this->height = 0;
}

SDL_Renderer* Window::createRenderer() {
    return SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Window::handleEvent(SDL_Event& e) {
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                this->width = e.window.data1;
                this->height = e.window.data2;
                Global::renderer->renderPresent();
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                Global::renderer->renderPresent();
                break;
            case SDL_WINDOWEVENT_ENTER:
                this->mouseFocus = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                this->mouseFocus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->keyboardFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                this->keyboardFocus = false;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                this->minimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                this->minimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                this->minimized = false;
                break;
        }
    } 
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB) {
        if (this->fullScreen) {
            SDL_SetWindowFullscreen(this->sdlWindow, SDL_FALSE);
            this->fullScreen = false;
        }
        else {
            SDL_SetWindowFullscreen(this->sdlWindow, SDL_TRUE);
            this->fullScreen = true;
            this->minimized = false;
        }
    }
}

int Window::getWidth() { return this->width; }
int Window::getHeight() { return this->height; }
bool Window::getMouseFocus() { return this->mouseFocus; }
bool Window::getKeyboardFocus() { return this->keyboardFocus; }
bool Window::getMinimized() { return this->minimized; }
bool Window::getFullScreen() { return this->fullScreen; }
