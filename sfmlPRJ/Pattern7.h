#pragma once
#include "ShootPattern.h"
#include "ObjectPool.h"
#include "Shoot.h"
class Player;
class Boss;
class Pattern7 : public ShootPattern
{
	Player* player;
	Boss* boss;

	ObjectPool<Shoot> bossShootPool;
	sf::Vector2f shootPos = { 0.f,0.f };
public:
	Pattern7();
	void ShootBullets() override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	void Update(float dt)override;
	void SetWallBounds(sf::Vector2f pos, float width, float height);
};

