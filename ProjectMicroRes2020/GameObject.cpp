#include "GameObject.h"

#include "ResourceManager.h"

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.Draw(position + texture_offset, ResourceManager::getTexture(texture_name), sprite_index, ResourceManager::getSpriteSizeData(texture_name));
}
