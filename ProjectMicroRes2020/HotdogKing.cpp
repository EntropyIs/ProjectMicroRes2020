#include "HotdogKing.h"

#include <Entropy/Math/Transform2D.h>
#include <Entropy/Math/Converters.h>

#include "EntityManager.h"
#include "ResourceManager.h"

#include <iostream>

using namespace Entropy;


HotdogKing::HotdogKing(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color) :
	AnimatedGameObject(id, "char_hotdog_king", 8, 0, 8, position, Math::Vec2(12.0, 12.0f),
		Math::Vec2(6.0f, 6.0f), Math::Vec2(2.0f, 2.0f)), color(color)
{
	health = 6;

	hurting = false;
	dieing = false;
	hurtAnim = 0;
}

void HotdogKing::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void HotdogKing::Update()
{
	animationRenderer.Update();

	if (!hurting && !dieing)
	{
		// Set Movement Pattern
		if (moveTimer <= 0)
		{
			// Move
			unsigned int direction = rand() % 3;

			switch (direction)
			{
			case 0: // stop;
				animationRenderer.setRowNumber(0);
				animationRenderer.setNumFrames(8);
				velocity = Math::Vec2(0.0f, 0.0f);
				break;
			case 1: // left;
				animationRenderer.setRowNumber(1);
				animationRenderer.setNumFrames(6);
				velocity = Math::Vec2(-10.0f, 0.0f);
				break;
			case 2: // Right;
				animationRenderer.setRowNumber(1);
				animationRenderer.setNumFrames(6);
				velocity = Math::Vec2(10.0f, 0.0f);
				break;
			default:
				break;
			}
			moveTimer = (float)(rand() % 4);
		}
		// Move Hotdog King
		performMovement();

		// Handle Collisions
		for (unsigned int i = 0; i < EntityManager::getLevel().getColliders().size(); i++)
		{
			std::string object = EntityManager::getLevel().getColliders()[i];
			if (object != id && detectCollion(EntityManager::getLevel().getCollider(object)))
			{
				if (EntityManager::getLevel().isWall(object) || EntityManager::getLevel().isLink(object) || EntityManager::getLevel().isEntity(object)) // Wall, WarpPoint or Entity
				{
					undoMovement();// Step Back
					velocity.X *= -1.0f; // reverse direction
				}
			}
		}

		// Attack
		if (attackTimer <= 0)
		{
	#ifdef _DEBUG
			std::cout << this->id << ", shooting" << std::endl;
	#endif // _DEBUG
			ResourceManager::playAudio("sfx_enemy_shoot");
			EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_king_weapon", 1, position,
				Math::Vec2(0.0f, -30.0f), Math::Vec2(4.0f, 0.0f),
				Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
			EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_king_weapon", 2, position,
				Math::Vec2(-25.0f, -25.0f), Math::Vec2(4.0f, 0.0f),
				Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
			EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_king_weapon", 0, position,
				Math::Vec2(25.0f, -25.0f), Math::Vec2(4.0f, 0.0f),
				Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
			attackTimer = (float)(rand() % 2);
		}

		if (detectCollion(EntityManager::getPlayerWeapon().getCollider()) && EntityManager::getPlayerWeapon().isAlive())
		{
	#ifdef _DEBUG
			std::cout << this->id << ", hit by: " << EntityManager::getPlayerWeapon().getID() << std::endl;
	#endif // _DEBUG
			ResourceManager::playAudio("sfx_boss_hurt");
			health--; // take away health if hits player wepon
			animationRenderer.setRowNumber(3);
			animationRenderer.setNumFrames(2);
			animationRenderer.playAnimationOnce();
			hurting = true;
			hurtAnim = 3;
		}
	}

	if (hurting && animationRenderer.isComplete())
	{
		hurtAnim--;
		if (hurtAnim <= 0)
		{
			hurting = false;
			animationRenderer.setRowNumber(0);
			animationRenderer.setNumFrames(8);
			velocity = Math::Vec2(0.0f, 0.0f);
			animationRenderer.playAnimation();
		}
		else
			animationRenderer.playAnimationOnce();
	}

	if (health == 0 && !hurting && !dieing)
	{
		ResourceManager::playAudio("sfx_boss_dead");
		dieing = true;
		animationRenderer.setRowNumber(4);
		animationRenderer.setNumFrames(30);
		animationRenderer.setFPS(12);
		animationRenderer.playAnimationOnce();
	}

	// Check if alive
	if (dieing && animationRenderer.isComplete())
		alive = false;

	// Update Timers
	moveTimer -= ResourceManager::getTimeElapsed();
	attackTimer -= ResourceManager::getTimeElapsed();
}
