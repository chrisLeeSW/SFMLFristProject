#pragma once
#include "Scene.h"
class SpriteGo;
class TextGo;
class SceneTitle :public Scene
{
protected:
	sf::Vector2f mousePos;
	SpriteGo* backGroundGame;
	TextGo* gameStartText;

public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

