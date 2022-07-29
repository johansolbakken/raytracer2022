#pragma once

#include <string>
#include <vector>
#include <SDL.h>

namespace qb {

class Image
{
public:
    Image();
    ~Image();

    void initialize(int width, int height, SDL_Renderer *renderer);
    void setPixel(int x, int y, double red, double green, double blue);
    void display();

    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    uint32_t convertColor(double red, double green, double blue);
    void initTexture();
    void computeMaxValues();

private:
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    double m_maxRed, m_maxGreen, m_maxBlue, m_overallMax;

    int m_width, m_height;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
};

}