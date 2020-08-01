#pragma once

#include <vector>

namespace Entropy
{
	class __declspec(dllexport) GameState
	{
	private:
		const char* stateName;
		std::vector<GameState*> connectedStates;

		bool renderFlag;
		bool gameFlag;

	public:
		GameState(const char* stateName = "GameState", bool renderFlag = true, bool gameFlag = true) : stateName(stateName), renderFlag(renderFlag), gameFlag(gameFlag) {};
		virtual ~GameState() {};

		void addConnection(GameState* gamestate);

		virtual bool init() = 0;
		virtual void input() = 0;
		virtual void render() = 0;
		virtual GameState* update() = 0;
	};
}