#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
class PlayerTest :public SpriteGo
{
protected:
	AnimationController animation;
	sf::Vector2f direction;
	float jumpFource=1.f;
	float velocity = 0.f;
	bool movePlayer = false;
	bool dontMoveLeftPlayer = false;
	bool dontMoveRigthPlayer = false;
	bool jumpPlayer = false;
	
	float grivaty=2.5f;
public:
	PlayerTest(const std::string& textureId="", const std::string& n="");
	virtual ~PlayerTest() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

};

