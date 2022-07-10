#pragma once

#include "texture.h"

namespace raytracer
{

	class ImageTexture : public Texture
	{
	public:
		const static int bytes_per_pixel = 3;

		ImageTexture();

		explicit ImageTexture(const std::string& filename);

		~ImageTexture() override;

		[[nodiscard]] Color value(float u, float v, const Vector3& p) const override;

	private:
		unsigned char* m_data;
		int m_width, m_height;
		int m_bytesPerScanline;
	};

} // raytracer
