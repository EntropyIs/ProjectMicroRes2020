#pragma once

namespace Entropy
{
	namespace Math
	{
		class __declspec(dllexport) Vec4
		{
		public:
			union
			{
				struct { float I, J, K, L; };
				struct { float X, Y, Z, W; };
				struct { float R, G, B, A; };
				float Data[4];
			};

			Vec4() : I(0.0f), J(0.0f), K(0.0f), L(0.0f) {};
			Vec4(float value) : I(value), J(value), K(value), L(value) {};
			Vec4(float i, float j) : I(i), J(j), K(0.0f), L(0.0f) {};
			Vec4(float i, float j, float k) : I(i), J(j), K(k), L(0.0f) {};
			Vec4(float i, float j, float k, float l) : I(i), J(j), K(k), L(l) {};

			Vec4& operator += (const Vec4& right);
			Vec4& operator -= (const Vec4& right);
		};

		Vec4 __declspec(dllexport) operator+ (const Vec4& left, const Vec4& right);
		Vec4 __declspec(dllexport) operator- (const Vec4& left, const Vec4& right);
		
		Vec4 __declspec(dllexport) operator* (const float left, const Vec4& right);
		Vec4 __declspec(dllexport) operator* (const Vec4& left, const float right);

		float __declspec(dllexport) dot(const Vec4& left, const Vec4& right);
		float __declspec(dllexport) magnitude(const Vec4& vector);
		Vec4 __declspec(dllexport) normalize(const Vec4& vector);
	}
}