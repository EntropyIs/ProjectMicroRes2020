#pragma once

namespace Entropy
{
	namespace Graphics
	{
		class __declspec(dllexport) InstanceBuffer
		{
		private:
			unsigned int buffer;

		public:
			InstanceBuffer(unsigned int count, size_t elementSize, const void* data);
		};
	}
}
