#pragma once
#include "ShootPattern.h"
class Player;
class Boss;

class UniquPattern2 :
    public ShootPattern
{
protected:
	Player* player;
	Boss* boss;

public:
	UniquPattern2();
	void ShootBullets() override;
	void Update(float dt)override;
	void SetCharceterAll(Player* player, Boss* boss) { this->player = player; this->boss = boss; }
	virtual void SetWallBounds(sf::Vector2f pos, float width, float height) override;

};

