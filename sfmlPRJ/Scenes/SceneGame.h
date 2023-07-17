#pragma once
#include "Scene.h"
class Player;
class Boss;
class SpriteGo;

class SceneGame : public Scene
{
protected:
	Player* player;
	Boss* bossCirno;
	SpriteGo* background;
	SpriteGo* gameBackground;
	SpriteGo* miniUi;
	SpriteGo* titleNameHong;
	sf::Vector2f gameWallSize;

	sf::Clock clock;
	sf::Time frameTime;
	int frames = 0;
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

