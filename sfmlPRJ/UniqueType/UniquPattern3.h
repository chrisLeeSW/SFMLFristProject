#pragma once
#include "ShootPattern.h"
#include "Shoot.h"
#include "ObjectPool.h"
class Player;
class Boss;
class UniquPattern3 : public ShootPattern
{
protected:
	Player* player;
	Boss* boss;


	ObjectPool<Shoot> bossShootPool;
public:
	UniquPattern3();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	virtual void SetWallBounds(sf::Vector2f pos, float width, float height) override;
};

