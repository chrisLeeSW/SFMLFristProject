#pragma once
#include "ShootPattern.h"

class Boss;
class Player;

class ShootMGR
{
protected:
	std::vector<ShootPattern*> patterns;  
	int currentPatternIndex =0; 
  
public:
    ShootMGR();
    ~ShootMGR();

    void ChangePattern(int patternIndex);
    void Update(float dt);
    void ShootBullets();
    void SetCharacterAll(Player* player, Boss* boss);
    void SetWallBounds(sf::Vector2f pos, float width, float height);
};
