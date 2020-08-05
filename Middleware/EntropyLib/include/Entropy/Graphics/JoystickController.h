#pragma once

namespace Entropy
{
	namespace Graphics
	{
		class __declspec(dllexport) JoystickController
		{
		public:
			JoystickController();

			const float* getAxisData(int jid, int* count);
			const unsigned char* getButtonsData(int jid, int* count);

			static void joystick_callback(int jid, int event);
		};
	}
}