#pragma once

namespace Entropy
{
	namespace Math
	{
		class __declspec(dllexport) Mat2
		{
		public:
			union
			{
				struct
				{
					float R0C0, R1C0;
					float R0C1, R1C1;
				};
				float Data[4];
				float Data2[2][2];
			};

			Mat2() :
				R0C0(1.0f), R1C0(0.0f),
				R0C1(0.0f), R1C1(1.0f) {};

			Mat2(float value) :
				R0C0(value), R1C0(value),
				R0C1(value), R1C1(value) {};

			Mat2(
				float r0c0, float r1c0,
				float r0c1, float r1c1
			) :
				R0C0(r0c0), R1C0(r1c0),
				R0C1(r0c1), R1C1(r1c1) {};

			Mat2(float* data) :
				R0C0(data[0]), R1C0(data[1]),
				R0C1(data[2]), R1C1(data[3]) {};

			Mat2(float* data[]) :
				R0C0(data[0][0]), R1C0(data[0][1]),
				R0C1(data[1][0]), R1C1(data[1][1]) {};
		};

		Mat2 __declspec(dllexport) operator+ (const Mat2& left, const Mat2& right);
		Mat2 __declspec(dllexport) operator- (const Mat2& left, const Mat2& right);
		Mat2 __declspec(dllexport) operator* (const Mat2& left, const Mat2& right);
	}
}