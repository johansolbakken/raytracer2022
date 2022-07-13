#pragma once

#include <cstdlib>
#include <string>
#include <future>

namespace raytracer
{
	class Image
	{
	public:
		explicit Image(uint32_t width, uint32_t height, uint32_t channels = 4, std::string filename = "image.png");

		~Image();

		void setFilename(const std::string& filename);

		void setData(const uint32_t* data);

		void flipHorizontal();

		void resize(uint32_t width, uint32_t height);

		void allocate();

		void release();

		[[nodiscard]] uint32_t width() const
		{
			return m_width;
		}

		[[nodiscard]] uint32_t height() const
		{
			return m_height;
		}

		[[nodiscard]] uint32_t comp() const
		{
			return m_channels;
		}

		[[nodiscard]] uint32_t stride() const
		{
			return m_width * m_channels;
		}

		uint32_t* data()
        {
			return m_data;
		}

		void save() const;

		std::mutex& mutex() const
		{
			return m_image_mutex;
		}

	private:
		std::string m_filename;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channels;
		uint32_t* m_data{};

		mutable std::mutex m_image_mutex;
	};
}
