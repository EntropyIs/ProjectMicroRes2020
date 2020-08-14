#include "Mustard.h"

#include <Entropy/Math/Transform2D.h>
#include <Entropy/Math/Converters.h>

#include "EntityManager.h"
#include "ResourceManager.h"

#include <iostream>

using namespace Entropy;

Mustard::Mustard(std::string id, Math::Vec2 position, Math::Vec3 color) :
	AnimatedGameObject(id, "char_sauce", 3, 0, 6, position, Math::Vec2(8.0f, 8.0f),
		Math::Vec2(4.0f, 4.0f), Math::Vec2(1.0f, 1.0f)), color(color)
{
	angle = (rand() % 62) / 10.0f;
	speed = 0.0f;

	health = 3;

	set = false;

	hurting = false;
	dieing = false;
	hurtAnim = 0;
}

void Mustard::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void Mustard::Update()
{
	animationRenderer.Update();

	if (!hurting && !dieing)
	{
		// Set Movement Pattern
		if (animationRenderer.getFrame() == 1 && !set) // frame 1, begin moveing
		{
			angle += 0.5f;
			speed = 20.0f;
			set = true;
		}
		else if (animationRenderer.getFrame() == 2 && set) // frame 2, stop moving
		{
			speed = 0.0f;
			set = false;
		}

		Entropy::Math::Vec3 slime_velocity = Math::Rotate(angle) * Math::Vec3(speed, 0.0f, 0.0f);
		velocity.X = slime_velocity.X;
		velocity.Y = slime_velocity.Y;

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
					angle += Math::Radians(180.0f); // set angle 180 deg from current;
					break;
				}
			}
		}

		if (detectCollion(EntityManager::getPlayerWeapon().getCollider()) && EntityManager::getPlayerWeapon().isAlive())
		{
#ifdef _DEBUG
			std::cout << this->id << ", hit by: " << EntityManager::getPlayerWeapon().getID() << std::endl;
#endif // _DEBUG
			health--; // take away health if hits player wepon
			animationRenderer.setRowNumber(2);
			animationRenderer.setNumFrames(2);
			hurting = true;
			hurtAnim = 3;
			animationRenderer.playAnimationOnce();
		}
	}

	if (hurting && animationRenderer.isComplete())
	{
		hurtAnim--;
		if (hurtAnim <= 0)
		{
			hurting = false;
			animationRenderer.setRowNumber(0);
			animationRenderer.setNumFrames(3);
			animationRenderer.playAnimation();
		}
		else
			animationRenderer.playAnimationOnce();
	}

	if (health == 0 && !hurting && !dieing)
	{
		dieing = true;
		hurting = false;
		animationRenderer.setRowNumber(4);
		animationRenderer.setNumFrames(7);
		animationRenderer.playAnimationOnce();
	}

	// Check if alive
	if (dieing && animationRenderer.isComplete())
		alive = false;
}
