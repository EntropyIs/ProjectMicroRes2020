#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

namespace Entropy
{
	namespace Math
	{
		Vec4 __declspec(dllexport) operator* (const Mat4& left, const Vec4& right);

		// Scale
		Mat4 __declspec(dllexport) Scale(float scale);
		Mat4 __declspec(dllexport) Scale(const Vec4& scale);
		Mat4 __declspec(dllexport) Scale(const Vec3& scale);
		Mat4 __declspec(dllexport) Scale(float sX, float sY, float sZ);

		// Translation
		Mat4 __declspec(dllexport) Translate(const Vec4& translation);
		Mat4 __declspec(dllexport) Translate(const Vec3& translation);
		Mat4 __declspec(dllexport) Translate(float dX, float dY, float dZ);

		// Rotation
		Mat4 __declspec(dllexport) RotateX(float angle);
		Mat4 __declspec(dllexport) RotateY(float angle);
		Mat4 __declspec(dllexport) RotateZ(float angle);
		Mat4 __declspec(dllexport) Rotate(const Vec3& axis, float angle);

		// Projections
		Mat4 __declspec(dllexport) Ortho(float left, float right, float top, float bottom, float near, float far);
		Mat4 __declspec(dllexport) Perspective(float fov, float aspectRatio, float near, float far);
		Mat4 __declspec(dllexport) Look(Vec3 cameraPos, Vec3 cameraTarget, Vec3 cameraUp);
	}
}