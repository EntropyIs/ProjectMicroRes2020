#pragma once

namespace Entropy
{
	namespace Timing
	{
		class __declspec(dllexport) Clock
		{
		private:
			float lastTime;
			float deltaTime;

		public:
			void poll();

			bool initialize();
			bool shutdown();

			float timeElapsed() const;
		};
	}
}



