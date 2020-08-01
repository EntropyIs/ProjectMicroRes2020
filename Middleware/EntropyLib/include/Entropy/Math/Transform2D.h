#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"

namespace Entropy
{
	namespace Math
	{
		Vec3 __declspec(dllexport) operator* (const Mat3& left, const Vec3& right);

		// Scale
		Mat3 __declspec(dllexport) Scale(float scale);
		Mat3 __declspec(dllexport) Scale(const Vec3& scale);
		Mat3 __declspec(dllexport) Scale(const Vec2& scale);
		Mat3 __declspec(dllexport) Scale(float sX, float sY);

		// Translation
		Mat3 __declspec(dllexport) Translate(const Vec3& translation);
		Mat3 __declspec(dllexport) Translate(const Vec2& translation);
		Mat3 __declspec(dllexport) Translate(float dX, float dY);

		// Roatation
		Mat3 __declspec(dllexport) Rotate(float angle);
	}
}
