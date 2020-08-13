#include <Entropy/Graphics/Window.h>
#include <Entropy/Graphics/Framebuffer.h>
#include <Entropy/Graphics/Shader.h>
#include <Entropy/Graphics/Mesh.h>

#include <iostream>
#include <exception>

#include "StateGame.h"

#include "ResourceManager.h"
#include "EntityManager.h"

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
		Graphics::Window window("Project MicroRes 2020", 600, 600, 1);
		window.setResolution(64, 64);
		window.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Setup framebuffer
		Graphics::FrameBuffer frameBuffer(64, 64);
		frameBuffer.setClearColor(0.1f, 0.1f, 0.1f, 0.1f); // Set to transparent clearing color
		Graphics::QuadMesh quad;

		// Load Resources
		ResourceManager::loadData("Assets/asset_directory.csv");

		// Load Game States
		StateGame game = StateGame();
		game.init();

		GameState * gameState = &game;

		// GameLoop
		while (!window.getShouldClose())
		{
			// Input
			gameState->input(window);

			// Update
			gameState = gameState->update(gameState);

			// Render
			// Render Game Into Framebuffer (for scaling)
			frameBuffer.bind();
			frameBuffer.clear();

			gameState->render();

			// Render to Screen
			window.bind();
			window.clear();
			// Render Quad
			quad.Draw(ResourceManager::getShader("quadShader"), frameBuffer);

			// Finish Frame
			window.processEvents();
			ResourceManager::pollClock();
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