#pragma once

#include <SDL.h>

#include "image.h"

class CApp {
public:
    CApp();
    
    int onExecute();
    bool onInit();
    void onEvent(SDL_Event* event);
    void onLoop();
    void onRender();
    void onExit();

private:
    // SDL2
    bool m_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    qbImage* m_image;
};