#include "stdafx.h"
#include "SpriteFontController.h"

void SpriteFontController::AddFont(const SpriteFont& font)
{
	if (clips.find(font.id) == clips.end())
	{
		clips.insert({ font.id,font });
	}
}

void SpriteFontController::SetTarget(const SpriteFontFrame& sprite)
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(sprite.textureId);
	target->setTexture(*tex);
	target->setTextureRect(sprite.texCoord);
}

void SpriteFontController::FindFont(const std::string& fontId)
{
	auto it = clips.find("");
	if (it != clips.end())
	{
		SetTarget(it->second.frames[0]);
	}
	else
	{
		std::cout << "ERR: Not EXIST CLIP" << std::endl;
	}
}

void SpriteFontController::Update(float dt)
{
}
