#pragma once
#include "Scene.h"
class SpriteGo;
class TextGo;
class SoundGo;
class SceneTitle :public Scene
{
protected:
	SpriteGo* backGroundGame;
	SoundGo* titleSound;

	TextGo* gameSceneText;
	TextGo* rankSceneText;
	TextGo* exitText;
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

