#pragma once
#include "ShootPattern.h"

#include "ObjectPool.h"
#include "Shoot.h"

class Player;
class Boss;

class Pattern2 :public ShootPattern
{
protected:
	Player* player;
	Boss* boss;


	ObjectPool<Shoot> bossShootPool;
public:
	Pattern2();
	void ShootBullets() override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player;this->boss = boss; }
};
