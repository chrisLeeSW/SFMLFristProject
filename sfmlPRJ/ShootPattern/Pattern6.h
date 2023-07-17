#pragma once
#include "ShootPattern.h"
#include "ObjectPool.h"
#include "Shoot.h"
class Player;
class Boss;
class Pattern6 : public ShootPattern
{
protected:
	Player* player;
	Boss* boss;

	ObjectPool<Shoot> bossShootPool;

public:
	Pattern6();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	virtual void SetWallBounds(sf::Vector2f pos, float width, float height) override;
};

