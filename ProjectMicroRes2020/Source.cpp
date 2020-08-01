#include <Entropy/Graphics/Window.h>
#include <Entropy/Graphics/Framebuffer.h>
#include <Entropy/Graphics/Shader.h>

#include <iostream>
#include <exception>

using namespace Entropy;

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif // _DEBUG
{
	try
	{
		// Setup and Initalize Window
		Graphics::Window window("Project MicroRes 2020", 600, 600);
		window.setResolution(64, 64);
		window.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Setup framebuffer
		Graphics::FrameBuffer frameBuffer(64, 64);
		frameBuffer.setClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		// Define Render Quad
		float QVerts[] =
		{
				1.0f,  1.0f,  1.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f
		};
		unsigned int QInds[] =
		{
			0,1,2,
			1,2,3
		};
		unsigned int QVAO, QVBO, QEBO;
		glGenVertexArrays(1, &QVAO);
		glGenBuffers(1, &QVBO);
		glGenBuffers(1, &QEBO);
		glBindVertexArray(QVAO);
		glBindBuffer(GL_ARRAY_BUFFER, QVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QVerts), &QVerts, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QInds), &QInds, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glBindVertexArray(0);

		// Load Shaders
		Graphics::Shader quadShader("Assets/Shaders/vFBShader.glsl", "Assets/Shaders/fFBShader.glsl");

		// GameLoop
		while (!window.getShouldClose())
		{
			// Input

			// Update

			// Render
			// Render Game Into Framebuffer (for scaling)
			frameBuffer.bind();
			frameBuffer.clear();

			// Render to Screen
			window.bind();
			window.clear();
			// Render Quad
			quadShader.use();
			glBindVertexArray(QVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frameBuffer.ColorBuffer);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Finish Frame
			window.processEvents();
		}
		return 0;
	}
	catch (std::exception e)
	{
		// Handle Exeptions
		std::cout << e.what() << std::endl;
		return -1;
	}
	
}