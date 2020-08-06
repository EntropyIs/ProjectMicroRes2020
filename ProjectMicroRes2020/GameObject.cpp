#include "GameObject.h"

#include "ResourceManager.h"

using namespace Entropy;

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.Draw(position + texture_offset, ResourceManager::getTexture(texture_name), sprite_index, ResourceManager::getSpriteSizeData(texture_name));
}

void GameObject::Update()
{
	position += velocity * ResourceManager::getTimeElapsed();
}

void GameObject::undoUpdate()
{
	position -= velocity * ResourceManager::getTimeElapsed();
}

void GameObject::setVelocity(Entropy::Math::Vec2 velocity)
{
	this->velocity = velocity;
}

void GameObject::setVelocityX(float velocity)
{
	this->velocity.X = velocity;
}

void GameObject::setVelocityY(float velocity)
{
	this->velocity.X = velocity;
}

Entropy::Math::Vec2 GameObject::getVelocity()
{
	return velocity;
}

float GameObject::getVelocityX()
{
	return velocity.X;
}

float GameObject::getVelocityY()
{
	return velocity.Y;
}

void GameObject::setPosition(Entropy::Math::Vec2 position)
{
	this->position = position;
}

void GameObject::setSpriteIndex(Entropy::Math::Vec2 spriteIndex)
{
	sprite_index = spriteIndex;
}

void GameObject::setSpriteIndexX(float x)
{
	sprite_index.X = x;
}

void GameObject::setSpriteIndexY(float y)
{
	sprite_index.Y = y;
}

bool GameObject::detectCollions(GameObject& other)
{
	Math::Vec2 otherlower = other.position - other.box_offset;
	Math::Vec2 otherUpper = otherlower + other.box_size;
	Math::Vec2 lower = position - box_offset;
	Math::Vec2 upper = lower + box_size;

	return (lower.X < otherUpper.X && upper.X > otherlower.X &&
		lower.Y < otherUpper.Y&& upper.Y > otherlower.Y);
}

bool GameObject::detectCollions(Tile& other)
{
	Math::Vec2 otherlower = Math::Vec2(other.X * other.box_size.X, other.Y * other.box_size.Y);
	Math::Vec2 otherUpper = otherlower + other.box_size;
	Math::Vec2 lower = position - box_offset;
	Math::Vec2 upper = lower + box_size;

	return (lower.X < otherUpper.X&& upper.X > otherlower.X &&
		lower.Y < otherUpper.Y&& upper.Y > otherlower.Y);
}
