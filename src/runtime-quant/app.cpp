#include "app.h"

CApp::CApp()
{
    m_running = true;
    m_window = nullptr;
    m_renderer = nullptr;
    m_image = nullptr;
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

    m_image = new qbImage();
    m_image->initialize(1280, 720, m_renderer);

    for (int x = 0; x < 1280; x++) {
        for (int y = 0; y < 720; y++) {
            double red = (static_cast<double>(x)/1280.0) * 255;
            double green = (static_cast<double>(y)/720.0) * 255;
            m_image->setPixel(x, y, red, green, 0.0);
        }
    }
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
}

void CApp::onEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT) {
        m_running = false;
    }
}

void CApp::onRender()  {
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    m_image->display();

    SDL_RenderPresent(m_renderer);
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