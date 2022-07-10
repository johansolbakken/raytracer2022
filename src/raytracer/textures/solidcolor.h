//
// Created by Johan Solbakken on 7/8/2022.
//

#ifndef RAY_SOLIDCOLOR_H
#define RAY_SOLIDCOLOR_H

#include "texture.h"

namespace raytracer
{

	class SolidColor : public Texture
	{
	public:
		SolidColor() = default;

		explicit SolidColor(Color c);

		SolidColor(float red, float green, float blue);

		[[nodiscard]] Color value(float u, float v, const Vector3& p) const override;

	private:
		Color m_colorValue{};
	};

} // raytracer

#endif //RAY_SOLIDCOLOR_H
