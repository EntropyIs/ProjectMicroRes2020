#include "Slime.h"

#include <Entropy/Math/Transform2D.h>
#include <Entropy/Math/Converters.h>

#include "EntityManager.h"
#include "ResourceManager.h"

using namespace Entropy;

Slime::Slime(std::string id, Math::Vec2 position, Math::Vec3 color) :
	AnimatedGameObject(id, "slime_sheet", 3, 0, 6, position, Math::Vec2(8.0f, 8.0f),
		Math::Vec2(4.0f, 4.0f), Math::Vec2(1.0f, 1.0f)), color(color)
{
	angle = (rand() % 62) / 10.0f;
	speed = 0.0f;

	health = 1;

	set = false;
}

void Slime::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void Slime::Update()
{
	animationRenderer.Update();

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

	// Move Slime
	performMovement();

	// Handle Collsions
	for (unsigned int i = 0; i < EntityManager::getLevel().getColliders().size(); i++)
	{
		std::string object = EntityManager::getLevel().getColliders()[i];
		if (object != id &&  detectCollion(EntityManager::getLevel().getCollider(object)))
		{
			if (EntityManager::getLevel().isWall(object) || EntityManager::getLevel().isLink(object) || EntityManager::getLevel().isEntity(object)) // Wall, WarpPoint or Entity
			{
				undoMovement();// Step Back
				angle += Math::Radians(180.0f); // set angle 180 deg from current;
				break;
			}
		}
	}

	// Check if alive
	if (health == 0)
		alive = false;
}
