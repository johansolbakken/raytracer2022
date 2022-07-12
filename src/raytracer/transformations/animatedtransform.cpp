//
// Created by Johan Solbakken on 09/07/2022.
//

#include "animatedtransform.h"

#include "transformation.h"

#include <cmath>

namespace raytracer
{

	AnimatedTransform::AnimatedTransform(const ref<Transform>& transform1, double time1,
			const ref<Transform>& transform2, double time2)
			: m_startTime(time1), m_endTime(time2), m_startTransform(transform1), m_endTransform(transform2),
			  m_actuallyAnimated(static_cast<Transform>(*transform1) != static_cast<Transform>(*transform2))
	{
		decompose(m_startTransform->matrix(), &T[0], &R[0], &S[0]);
		decompose(m_endTransform->matrix(), &T[1], &R[1], &S[1]);
	}

	void AnimatedTransform::decompose(const Matrix4& matrix, Vector3* T, Quaternion* Rquat, Matrix4* S)
	{
		// Extract translation T from transformation
		T->x = matrix[0][3];
		T->y = matrix[1][3];
		T->z = matrix[2][3];

		// Compute new transformation matrix M without translation
		Matrix4 M = matrix;
		for (int i = 0; i < 3; i++)
			M[i][3] = M[3][i] = 0.f;
		M[3][3] = 1.f;

		// Extract rotation R form translation matrix
		double norm;
		int count = 0;
		Matrix4 R = M;
		do
		{
			// Compute next matrix Rnext in series
			Matrix4 Rnext;
			Matrix4 Rit = glm::inverse(glm::transpose(R));
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					Rnext[i][j] = 0.5f * (R[i][j] + Rit[i][j]);

			// Compute norm of difference between R and Rnext
			norm = 0.f;
			for (int i = 0; i < 3; i++)
			{
                double n = std::abs(R[i][0] - Rnext[i][0]) +
                          std::abs(R[i][1] - Rnext[i][1]) +
                          std::abs(R[i][2] - Rnext[i][2]);
				norm = std::max(norm, n);
			}

			R = Rnext;
		} while (++count < 100 && norm > 0.0001f);
		*Rquat = Quaternion(R);

		// Compute scale S using rotation and original matrix
		*S = glm::inverse(R) * M;
	}

	void AnimatedTransform::interpolate(double time, ref<Transform>& t) const
	{
		// Handle boundry conditions for matrix interpolation
		if (!m_actuallyAnimated || time <= m_startTime) {
			*t = *m_startTransform;
			return;
		}

		if (time >= m_endTime) {
			*t = *m_endTransform;
			return;
		}

		double dt = (time - m_startTime) / (m_endTime - m_startTime);

		// Interpolate translation at dt
		Vector3 trans = (1.f - dt) * T[0] + dt * T[1];

		// Interpolate rotation at dt
		Quaternion rotate = glm::slerp(R[0], R[1], dt);

		// Interpolate scale at dt
		Matrix4 scale;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				// TODO: Implement an linear interpolation between doubles
				//scale[i][j] = lerp(S[0][i][j], S[1][i][j], dt);
			}

		// Compute interpolated matrix as product of interpolated components
		// TODO: Implement a Transform::fromQuaternion(rotate)
		//*t = glm::translate(Matrix4(1.0f), trans) * Transform(scale);
	}
}
