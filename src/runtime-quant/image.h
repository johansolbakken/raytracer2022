#pragma once

#include <string>
#include <vector>
#include <SDL.h>

namespace raytracer
{
    class Image;
}

namespace qb
{
    class Image
    {
    public:
        Image();
        ~Image();

        void initialize(int width, int height, SDL_Renderer *renderer);
        void setPixel(int x, int y, double red, double green, double blue);
        void display();

        int width() const;
        int height() const;

    private:
        uint32_t convertColor(double red, double green, double blue);
        void initTexture();
        void computeMaxValues();

    private:
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        double m_maxRed, m_maxGreen, m_maxBlue, m_overallMax;

        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        raytracer::Image *m_image;
    };
}