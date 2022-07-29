#include "image.h"

#include <raytracer/image.h>

namespace qb
{
    Image::Image()
    {
        m_texture = nullptr;
        m_renderer = nullptr;
        m_image = nullptr;
    }

    Image::~Image()
    {
        if (m_texture)
            SDL_DestroyTexture(m_texture);
        if (m_image)
            delete m_image;
    }

    void Image::initialize(int width, int height, SDL_Renderer *renderer)
    {
        m_renderer = renderer;

        m_rChannel.resize(width, std::vector<double>(height, 0.0));
        m_gChannel.resize(width, std::vector<double>(height, 0.0));
        m_bChannel.resize(width, std::vector<double>(height, 0.0));

        if (m_image)
            delete m_image;
        m_image = new raytracer::Image(width, height);

        initTexture();
    }

    void Image::setPixel(int x, int y, double red, double green, double blue)
    {
        m_rChannel[x][y] = red;
        m_gChannel[x][y] = green;
        m_bChannel[x][y] = blue;
    }

    void Image::computeMaxValues()
    {
        m_maxRed = 0.0;
        m_maxGreen = 0.0;
        m_maxBlue = 0.0;
        m_overallMax = 0.0;

        for (int x = 0; x < width(); x++)
        {
            for (int y = 0; y < height(); y++)
            {
                double redValue = m_rChannel[x][y];
                double greenValue = m_gChannel[x][y];
                double blueValue = m_bChannel[x][y];

                m_maxRed = std::max(m_maxRed, redValue);
                m_maxBlue = std::max(m_maxBlue, blueValue);
                m_maxGreen = std::max(m_maxGreen, greenValue);
            }
        }

        m_overallMax = std::max(m_maxRed, std::max(m_maxBlue, m_maxGreen));
    }

    int Image::width() const
    {
        if (!m_image)
            return 0;
        return m_image->width();
    }

    int Image::height() const
    {
        if (!m_image)
            return 0;
        return m_image->height();
    }

    void Image::display()
    {
        computeMaxValues();

        for (int x = 0; x < width(); x++)
        {
            for (int y = 0; y < height(); y++)
            {
                m_image->setPixel(x, y, convertColor(m_rChannel[x][y], m_gChannel[x][y], m_bChannel[x][y]));
            }
        }

        SDL_UpdateTexture(m_texture, nullptr, m_image->data(), m_image->width() * sizeof(uint32_t));

        SDL_Rect srcRect, bounds;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = width();
        srcRect.h = height();
        bounds = srcRect;

        SDL_RenderCopy(m_renderer, m_texture, &srcRect, &bounds);
    }

    uint32_t Image::convertColor(double red, double green, double blue)
    {
        // Convert the colors to unsiged ints
        auto r = static_cast<uint8_t>(red / m_overallMax * 255.0);
        auto g = static_cast<uint8_t>(green / m_overallMax * 255.0);
        auto b = static_cast<uint8_t>(blue / m_overallMax * 255.0);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        uint32_t pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
        uint32_t pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
#endif

        return pixelColor;
    }

    void Image::initTexture()
    {
        uint32_t rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        if (m_texture)
            SDL_DestroyTexture(m_texture);

        SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, width(), height(), 32, rmask, gmask, bmask, amask);
        m_texture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
}