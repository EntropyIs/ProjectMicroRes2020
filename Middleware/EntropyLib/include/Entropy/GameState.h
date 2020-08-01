#pragma once

#include "Graphics/Window.h"

namespace Entropy
{
	class _declspec(dllexport) GameState
	{
	protected:
		const char* stateName;
		GameState** connectedStates;

		bool renderFlag;
		bool gameFlag;

	public:
		GameState(const char* stateName = "GameState", unsigned int numConnections = 1, bool renderFlag = true, bool gameFlag = true);
		virtual ~GameState() {};

		void  addConnection(unsigned int index, GameState* gamestate);

		virtual bool init() = 0;
		virtual void input(Graphics::Window& window) = 0;
		virtual void render() = 0;
		virtual GameState* update(GameState* gameState) = 0;
	};
}