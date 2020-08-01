#pragma once

namespace Entropy
{
	namespace Math
	{
		class __declspec(dllexport) Mat3
		{
		public:
			union
			{
				struct
				{
					float R0C0, R1C0, R2C0;
					float R0C1, R1C1, R2C1;
					float R0C2, R1C2, R2C2;
				};
				float Data[9];
				float Data2[3][3];
			};

			Mat3() :
				R0C0(1.0f), R1C0(0.0f), R2C0(0.0f),
				R0C1(0.0f), R1C1(1.0f), R2C1(0.0f),
				R0C2(0.0f), R1C2(0.0f), R2C2(1.0f) {};

			Mat3(float value) :
				R0C0(value), R1C0(value), R2C0(value),
				R0C1(value), R1C1(value), R2C1(value),
				R0C2(value), R1C2(value), R2C2(value) {};

			Mat3(
				float r0c0, float r1c0, float r2c0,
				float r0c1, float r1c1, float r2c1,
				float r0c2, float r1c2, float r2c2
			) :
				R0C0(r0c0), R1C0(r1c0), R2C0(r2c0),
				R0C1(r0c1), R1C1(r1c1), R2C1(r2c1),
				R0C2(r0c2), R1C2(r1c2), R2C2(r2c2) {};

			Mat3(float* data) :
				R0C0(data[0]), R1C0(data[1]), R2C0(data[2]), 
				R0C1(data[3]), R1C1(data[4]), R2C1(data[5]), 
				R0C2(data[6]), R1C2(data[7]), R2C2(data[8]) {};

			Mat3(float* data[]) :
				R0C0(data[0][0]), R1C0(data[0][1]), R2C0(data[0][2]),
				R0C1(data[1][0]), R1C1(data[1][1]), R2C1(data[1][2]),
				R0C2(data[2][0]), R1C2(data[2][1]), R2C2(data[2][2]) {};
		};

		Mat3 __declspec(dllexport) operator+ (const Mat3& left, const Mat3& right);
		Mat3 __declspec(dllexport) operator- (const Mat3& left, const Mat3& right);
		Mat3 __declspec(dllexport) operator* (const Mat3& left, const Mat3& right);
	}
}