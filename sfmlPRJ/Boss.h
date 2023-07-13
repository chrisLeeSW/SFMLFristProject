#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include "Shoot.h"
class Boss :public SpriteGo
{
protected:
	AnimationController animation;
	sf::Vector2f direction;
	float speed = 500.f;
	bool moveBoss = false;
	bool filpX = false;

	ObjectPool<Shoot> bossShootPool;

	sf::Clock clock;
	float timer;
public:
	Boss(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId, n) {}
	virtual ~Boss() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void BossMove(float dt);
};

