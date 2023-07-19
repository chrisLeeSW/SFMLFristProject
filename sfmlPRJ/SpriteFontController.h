#pragma once
#include "SpriteFont.h"
class SpriteFontController
{
protected:
	std::unordered_map<std::string, SpriteFont> clips;
	sf::Sprite* target = nullptr;
public:
	void AddFont(const SpriteFont& font);
	void SetTarget(const SpriteFontFrame& sprite);
	void FindFont(const std::string& fontId);
	void Update(float dt);
};

