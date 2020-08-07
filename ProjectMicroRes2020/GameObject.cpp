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
	collider.setPosition(position);
}

void GameObject::undoUpdate()
{
	position -= velocity * ResourceManager::getTimeElapsed();
	collider.setPosition(position);
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

std::string GameObject::getID()
{
	return id;
}

BoxCollider& GameObject::getCollider()
{
	return collider;
}

bool GameObject::detectCollion(GameObject& other)
{
	return collider.detect(other.collider);
}

bool GameObject::detectCollion(BoxCollider& other)
{
	return other.detect(collider);
}
