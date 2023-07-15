#pragma once
#include "ShootPattern.h"
#include "Shoot.h"

#include "ObjectPool.h"
class Player;
class Boss;

class Pattern1: public ShootPattern
{
protected:
    Player* player;
    Boss* boss;


	ObjectPool<Shoot> bossShootPool;
public:
	Pattern1();
	void ShootBullets() override;
    void SetCharceterAll(Player* player, Boss* boss) { this->player = player;this->boss = boss; }
};
