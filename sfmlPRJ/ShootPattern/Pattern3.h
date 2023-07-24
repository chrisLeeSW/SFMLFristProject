#pragma once
#include "ShootPattern.h"
#include "ObjectPool.h"
#include "Shoot.h"

class Player;
class Boss;
class Pattern3 :public ShootPattern
{

protected:
	Player* player;
	Boss* boss;

	ObjectPool<Shoot> bossShootPool;

public:
	Pattern3();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	virtual void SetWallBounds(sf::Vector2f pos, float width, float height) override;
	void ClearBossShootPool() override { bossShootPool.Clear(); }
	virtual void ReleaseBossShootPool() { bossShootPool.Release(); }
};


