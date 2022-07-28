#include "app.h"

#include <iostream>
#include <iomanip>

CApp::CApp()
{
    m_running = true;
    m_window = nullptr;
    m_renderer = nullptr;
    m_image = nullptr;
    m_scene = nullptr;
}

bool CApp::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    m_window = SDL_CreateWindow("RayTracer runtime", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    m_image = new qb::Image();
    m_image->initialize(1280, 720, m_renderer);

    m_scene = new Scene();

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    m_scene->render(m_image);
    m_image->display();

    SDL_RenderPresent(m_renderer);

    return true;
}

int CApp::onExecute()
{
    SDL_Event event;

    if (onInit() == false)
    {
        return -1;
    }

    while (m_running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            onEvent(&event);
            onLoop();
            onRender();
        }
    }

    onExit();
    return 0;
}

void CApp::onEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        m_running = false;
    }
}

void CApp::onRender()
{
    /*
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    m_scene->render(m_image);
    m_image->display();

    SDL_RenderPresent(m_renderer);*/
}

void CApp::onLoop()
{
}

void CApp::onExit()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    SDL_Quit();
}

void CApp::printVector(const qb::Vector3 &vec) const
{
    std::cout << "(" << std::fixed << std::setprecision(3);
    std::cout << vec[0] << ", ";
    std::cout << vec[1] << ", ";
    std::cout << vec[2] << ")";
}