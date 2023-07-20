#pragma once
#include "Scene.h"
#include "SpriteFontController.h"
class Player;
class Boss;
class SpriteGo;
class TextGo;
class SoundGo;

class SceneGame : public Scene
{
protected:
	Player* player;
	Boss* bossCirno;
	TextGo* bossName;
	SpriteGo* background;
	SpriteGo* gameBackground;
	SpriteGo* miniUi;
	SpriteGo* titleNameHong;
	sf::Vector2f gameWallSize;

	bool isTalking;
	SpriteGo* cirnoTalking;
	sf::RectangleShape shape;
	TextGo* talk;
	sf::RectangleShape hpBar;
	float hpBarbyX = 0.f;

	sf::Clock clock;
	sf::Time frameTime;
	int frames = 0;

	SoundGo* music1;
	float musicVolum = 25.f;

	float soundTime;
	bool soundPlay;

	std::vector<sf::IntRect> numberFont;

	SpriteGo* numberX1Sprite;
	int numberX1Current=0;
	SpriteGo* numberX2Sprite;
	int numberX2Current=0;

	

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void increaseScore() { numberX1Current++; }
};

