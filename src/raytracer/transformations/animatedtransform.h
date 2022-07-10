#pragma once

#include "raytracer/base.h"
#include "utils/glmutils.h"

namespace raytracer
{
	class Transform;

	class AnimatedTransform
	{
	public:
		AnimatedTransform(const ref<Transform>& transform1, float time1,
				const ref<Transform>& transform2, float time2);

		void interpolate(float time, ref<Transform>& t) const;

	private:
		static void decompose(const Matrix4& matrix, Vector3* T, Quaternion* Rquat, Matrix4* S);

	private:
		const float m_startTime{}, m_endTime{};
		const ref<Transform> m_startTransform{}, m_endTransform{};
		const bool m_actuallyAnimated;
		Vector3 T[2]{};
		Quaternion R[2]{};
		Matrix4 S[2]{};
	};
}
