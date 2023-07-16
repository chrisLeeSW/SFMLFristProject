#pragma once
#include "ShootPattern.h"

#include "ObjectPool.h"
#include "Shoot.h"

class Player;
class Boss;

class Pattern4 : public ShootPattern
{
protected:
	Player* player;
	Boss* boss;

	ObjectPool<Shoot> bossShootPool;

public:
	Pattern4();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
};

