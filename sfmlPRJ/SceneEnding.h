#pragma once
#include "Scene.h"

class SpriteGo;
class SceneEnding : public Scene
{
protected:
	SpriteGo* ending;
	float timer;
	std::vector<std::string> textureId;
	int currentTextureId=0;
public:
	SceneEnding();
	virtual ~SceneEnding() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void LoadFromFile(const std::string& path);
};

