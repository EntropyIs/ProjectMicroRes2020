#pragma once

namespace Entropy
{
	namespace Math
	{
		class __declspec(dllexport) Mat4
		{
		public:
			union
			{
				struct
				{
					float R0C0, R1C0, R2C0, R3C0;
					float R0C1, R1C1, R2C1, R3C1;
					float R0C2, R1C2, R2C2, R3C2;
					float R0C3, R1C3, R2C3, R3C3;
				};
				float Data[16];
				float Data2[4][4];
			};

			Mat4() :
				R0C0(1.0f), R1C0(0.0f), R2C0(0.0f), R3C0(0.0f),
				R0C1(0.0f), R1C1(1.0f), R2C1(0.0f), R3C1(0.0f),
				R0C2(0.0f), R1C2(0.0f), R2C2(1.0f), R3C2(0.0f),
				R0C3(0.0f), R1C3(0.0f), R2C3(0.0f), R3C3(1.0f) {};

			Mat4(float value) :
				R0C0(value), R1C0(value), R2C0(value), R3C0(value),
				R0C1(value), R1C1(value), R2C1(value), R3C1(value),
				R0C2(value), R1C2(value), R2C2(value), R3C2(value),
				R0C3(value), R1C3(value), R2C3(value), R3C3(value) {};

			Mat4(
				float r0c0, float r1c0, float r2c0, float r3c0,
				float r0c1, float r1c1, float r2c1, float r3c1,
				float r0c2, float r1c2, float r2c2, float r3c2,
				float r0c3, float r1c3, float r2c3, float r3c3
			) :
				R0C0(r0c0), R1C0(r1c0), R2C0(r2c0), R3C0(r3c0),
				R0C1(r0c1), R1C1(r1c1), R2C1(r2c1), R3C1(r3c1),
				R0C2(r0c2), R1C2(r1c2), R2C2(r2c2), R3C2(r3c2),
				R0C3(r0c3), R1C3(r1c3), R2C3(r2c3), R3C3(r3c3) {};

			Mat4(float* data) :
				R0C0(data[ 0]), R1C0(data[ 1]), R2C0(data[ 2]), R3C0(data[ 3]),
				R0C1(data[ 4]), R1C1(data[ 5]), R2C1(data[ 6]), R3C1(data[ 7]),
				R0C2(data[ 8]), R1C2(data[ 9]), R2C2(data[10]), R3C2(data[11]),
				R0C3(data[12]), R1C3(data[13]), R2C3(data[14]), R3C3(data[15]) {};

			Mat4(float* data[]) :
				R0C0(data[0][0]), R1C0(data[0][1]), R2C0(data[0][2]), R3C0(data[0][3]),
				R0C1(data[1][0]), R1C1(data[1][1]), R2C1(data[1][2]), R3C1(data[1][3]),
				R0C2(data[2][0]), R1C2(data[2][1]), R2C2(data[2][2]), R3C2(data[2][3]),
				R0C3(data[3][0]), R1C3(data[3][1]), R2C3(data[3][2]), R3C3(data[3][3]) {};
		};

		Mat4 __declspec(dllexport) operator+ (const Mat4& left, const Mat4& right);
		Mat4 __declspec(dllexport) operator- (const Mat4& left, const Mat4& right);
		Mat4 __declspec(dllexport) operator* (const Mat4& left, const Mat4& right);
	}
}