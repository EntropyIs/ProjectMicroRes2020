#pragma once

#include "Model/Image.h"
#include "../Math/Vec4.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Entropy
{
	namespace Graphics
	{
		class __declspec(dllexport) FrameBuffer
		{
		private:
			unsigned int fbo;
			unsigned int rbo;

			bool depthTest;
			bool stencilTest;
			bool faceCulling;

			Math::Vec4 clearColor;

		public:
			unsigned int ColorBuffer;

			unsigned int Width, Height;

			FrameBuffer(unsigned int width, unsigned int height, bool depthTest = true, bool stencilTest = false, bool faceCulling = false);
			~FrameBuffer();

			void bind();
			void clear();

			void setClearColor(float red, float green, float blue, float alpha);

			void enableDepthTest(bool value = true);
			void enableStencilTest(bool value = true);
			void enableFaceCulling(bool value = true);
		};
	}
}