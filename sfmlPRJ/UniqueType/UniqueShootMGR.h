#pragma once
#include "ShootPattern.h"
class Player;
class Boss;
class UniqueShootMGR
{
protected:
    std::vector<ShootPattern*> patterns; 
    int currentPatternIndex = 0; 

    Player* player=nullptr;
    Boss* boss = nullptr;
public:
    UniqueShootMGR();
    ~UniqueShootMGR();

    void ChangePattern(int patternIndex);
    void Update(float dt);
    void ShootBullets();
    void SetCharacterAll(Player* player, Boss* boss);
    void SetWallBounds(sf::Vector2f pos, float width, float height);
};

