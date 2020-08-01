#pragma once

namespace Entropy
{
	namespace Graphics
	{
		class __declspec(dllexport) UniformBuffer
		{
		public:
			unsigned int UBO;

			UniformBuffer(unsigned int size, const void* data);

			void setSubData(unsigned int offset, unsigned int size, const void* data);
		};
	}
}
