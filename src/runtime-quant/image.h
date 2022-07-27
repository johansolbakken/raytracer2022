#pragma once

#include <string>
#include <vector>
#include <SDL.h>

class qbImage
{
public:
    qbImage();
    ~qbImage();

    void initialize(int width, int height, SDL_Renderer *renderer);
    void setPixel(int x, int y, double red, double green, double blue);
    void display();

private:
    uint32_t convertColor(double red, double green, double blue);
    void initTexture();

private:
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    int m_width, m_height;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
};