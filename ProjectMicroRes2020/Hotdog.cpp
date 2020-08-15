#include "Hotdog.h"

#include <Entropy/Math/Transform2D.h>
#include <Entropy/Math/Converters.h>

#include "EntityManager.h"
#include "ResourceManager.h"

#include <iostream>

using namespace Entropy;

Hotdog::Hotdog(std::string id, Math::Vec2 position, Math::Vec3 color) :
	AnimatedGameObject(id, "char_hotdog", 6, 0, 6, position, Math::Vec2(8.0f, 8.0f),
		Math::Vec2(4.0f, 4.0f), Math::Vec2(1.0f, 1.0f)), color(color)
{
	health = 2;

	hurting = false;
	dieing = false;
	hurtAnim = 0;
}

void Hotdog::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void Hotdog::Update()
{
	animationRenderer.Update();

	if (!hurting && !dieing)
	{
		// Set Movement Pattern
		if (moveTimer <= 0)
		{
			unsigned int direction = rand() % 5;

			switch (direction)
			{
			case 0:
				lastDirection = Direction::LEFT;
				animationRenderer.setRowNumber(0);
				velocity = Math::Vec2(-10.0f, 0.0f);
				break;
			case 1:
				lastDirection = Direction::DOWN;
				animationRenderer.setRowNumber(3);
				velocity = Math::Vec2(0.0f, -10.0f);
				break;
			case 2:
				lastDirection = Direction::RIGHT;
				animationRenderer.setRowNumber(2);
				velocity = Math::Vec2(10.0f, 0.0f);
				break;
			case 3:
				lastDirection = Direction::UP;
				animationRenderer.setRowNumber(1);
				velocity = Math::Vec2(0.0f, 10.0f);
				break;
			}

			moveTimer = (float) (rand() % 4);
		}

		// Move Mustard
		performMovement();

		// Handle Collsions
		for (unsigned int i = 0; i < EntityManager::getLevel().getColliders().size(); i++)
		{
			std::string object = EntityManager::getLevel().getColliders()[i];
			if (object != id && detectCollion(EntityManager::getLevel().getCollider(object)))
			{
				if (EntityManager::getLevel().isWall(object) || EntityManager::getLevel().isLink(object) || EntityManager::getLevel().isEntity(object)) // Wall, WarpPoint or Entity
				{
					undoMovement();// Step Back
					switch (lastDirection)
					{
					case RIGHT:
						lastDirection = Direction::LEFT;
						animationRenderer.setRowNumber(0);
						velocity = Math::Vec2(-10.0f, 0.0f);
						break;
					case DOWN:
						lastDirection = Direction::UP;
						animationRenderer.setRowNumber(1);
						velocity = Math::Vec2(0.0f, 10.0f);
						break;
					case LEFT:
						lastDirection = Direction::RIGHT;
						animationRenderer.setRowNumber(2);
						velocity = Math::Vec2(10.0f, 0.0f);
						break;
					case UP:
						lastDirection = Direction::DOWN;
						animationRenderer.setRowNumber(3);
						velocity = Math::Vec2(0.0f, -10.0f);
						break;
					}
					break;
				}
			}
		}

		// Attack
		if (attackTimer <= 0)
		{
			if (!EntityManager::getHotdogWeapon().isAlive())
			{
#ifdef _DEBUG
				std::cout << this->id << ", shooting" << std::endl;
#endif // _DEBUG
				ResourceManager::playAudio("sfx_enemy_shoot");
				switch (lastDirection)
				{
				case RIGHT:
					EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_weapon", 2, position,
						Math::Vec2(30.0f, 0.0f), Math::Vec2(4.0f, 0.0f),
						Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
					break;
				case DOWN:
					EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_weapon", 3, position,
						Math::Vec2(0.0f, -30.0f), Math::Vec2(0.0f, -4.0f),
						Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
					break;
				case LEFT:
					EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_weapon", 0, position,
						Math::Vec2(-30.0f, 0.0f), Math::Vec2(-4.0f, 0.0f),
						Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
					break;
				case UP:
					EntityManager::setHotdogWeapon(HotdogWeapon("char_hotdog_weapon", 1, position,
						Math::Vec2(0.0f, 30.0f), Math::Vec2(0.0f, 4.0f),
						Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f)));
					break;
				}
				attackTimer = (float)(rand() % 6);
			}
		}

		if (detectCollion(EntityManager::getPlayerWeapon().getCollider()) && EntityManager::getPlayerWeapon().isAlive())
		{
#ifdef _DEBUG
			std::cout << this->id << ", hit by: " << EntityManager::getPlayerWeapon().getID() << std::endl;
#endif // _DEBUG
			ResourceManager::playAudio("sfx_enemy_hurt");
			health--; // take away health if hits player wepon

			switch (lastDirection)
			{
			case RIGHT:
				animationRenderer.setRowNumber(6);
				break;
			case DOWN:
				animationRenderer.setRowNumber(7);
				break;
			case LEFT:
				animationRenderer.setRowNumber(4);
				break;
			case UP:
				animationRenderer.setRowNumber(5);
				break;
			default:
				break;
			}
			animationRenderer.setNumFrames(2);
			animationRenderer.setFPS(8);
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
			switch (lastDirection)
			{
			case RIGHT:
				lastDirection = Direction::RIGHT;
				animationRenderer.setRowNumber(2);
				velocity = Math::Vec2(10.0f, 0.0f);
				
				break;
			case DOWN:
				lastDirection = Direction::DOWN;
				animationRenderer.setRowNumber(3);
				velocity = Math::Vec2(0.0f, -10.0f);
				break;
			case LEFT:
				lastDirection = Direction::LEFT;
				animationRenderer.setRowNumber(0);
				velocity = Math::Vec2(-10.0f, 0.0f);
				break;
			case UP:
				lastDirection = Direction::UP;
				animationRenderer.setRowNumber(1);
				velocity = Math::Vec2(0.0f, 10.0f);
				break;
			default:
				break;
			}
			animationRenderer.setNumFrames(6);
			animationRenderer.setFPS(6);
			animationRenderer.playAnimation();
		}
		else
			animationRenderer.playAnimationOnce();
	}

	if (health == 0 && !hurting && !dieing)
	{
		ResourceManager::playAudio("sfx_enemy_dead");
		dieing = true;
		animationRenderer.setRowNumber(11);
		animationRenderer.setNumFrames(7);
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
