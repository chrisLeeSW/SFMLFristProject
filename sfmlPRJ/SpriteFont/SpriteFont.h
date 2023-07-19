#pragma once
struct SpriteFontFrame
{
	char texworld;
	std::string textureId;
	sf::IntRect texCoord;

	std::function<void()> action;
};
struct SpriteFont
{
	std::string id;
	std::vector<SpriteFontFrame> frames;

	bool LoadFromFile(const std::string path);
};