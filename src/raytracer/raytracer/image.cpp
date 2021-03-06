#include "image.h"

#include <utility>
#include <cstdint>
#include <string>

#include "stb_image_write.h"

namespace raytracer
{
	Image::Image(uint32_t width, uint32_t height, uint32_t channels, std::string filename)
		: m_width(width), m_height(height), m_channels(channels), m_filename(std::move(filename))
	{
		allocate();
		memset(m_data, 0, m_width * m_height * sizeof(uint32_t));
	}

	Image::~Image()
	{
		release();
	}

	void Image::setFilename(const std::string &filename)
	{
		m_filename = filename;
	}

	void Image::allocate()
	{
		m_data = new uint32_t[m_width * m_height];
	}

	void Image::release()
	{
		delete[] m_data;
	}

	void Image::save() const
	{
		stbi_write_png(
			m_filename.c_str(),
			m_width,
			m_height,
			m_channels,
			m_data,
			m_width * m_channels);
	}

	void Image::setData(const uint32_t *data)
	{
		for (uint32_t i = 0; i < m_width * m_height; i++)
		{
			m_data[i] = data[i];
		}
	}

	void Image::setPixel(uint32_t x, uint32_t y, uint32_t color)
	{
		m_data[x + y * m_width] = color;
	}

	void Image::resize(uint32_t width, uint32_t height)
	{
		if (m_data && m_width == width && m_height == height)
			return;

		m_width = width;
		m_height = height;

		release();
		allocate();
	}

	void Image::flipHorizontal()
	{
		uint32_t *old = m_data;
		m_data = new uint32_t[m_width * m_height];

		for (uint32_t y = 0; y < m_height; y++)
		{
			for (uint32_t x = 0; x < m_width; x++)
			{
				uint32_t oldY = m_height - y - 1;
				m_data[x + y * width()] = old[x + oldY * m_width];
			}
		}

		delete old;
	}

}
