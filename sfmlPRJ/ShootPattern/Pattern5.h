#pragma once
#include "ShootPattern.h"
class Player;
class Boss;
class Pattern5 :public ShootPattern
{
protected:
	Player* player;
	Boss* boss;

public:
	Pattern5();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	virtual void SetWallBounds(sf::Vector2f pos, float width, float height) override;
};

