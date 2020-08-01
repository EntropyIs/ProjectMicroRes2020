#pragma once

#include "Graphics/Window.h"

#include <vector>

namespace Entropy
{
	class GameState
	{
	protected:
		const char* stateName;
		std::vector<GameState*> connectedStates;

		bool renderFlag;
		bool gameFlag;

	public:
		GameState(const char* stateName = "GameState", bool renderFlag = true, bool gameFlag = true) : stateName(stateName), renderFlag(renderFlag), gameFlag(gameFlag) {};
		virtual ~GameState() {};

		void __declspec(dllexport) addConnection(GameState* gamestate);

		virtual bool init() = 0;
		virtual void input(Graphics::Window& window) = 0;
		virtual void render() = 0;
		virtual GameState* update(GameState* gameState) = 0;
	};
}