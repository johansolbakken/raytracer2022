#pragma once

#include <SDL.h>

#include "image.h"
#include "scene.h"

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
    void printVector(const qb::Vector3& vec) const;

private:
    // SDL2
    bool m_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    qb::Image* m_image;
    Scene* m_scene;
};