#pragma once
#include "Scene.h"
class Player;
class Boss;
class SceneGame : public Scene
{
protected:
	Player* player;
	Boss* bossCirno;

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

