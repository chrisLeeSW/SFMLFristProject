#pragma once
class Player;
class Boss;

class ShootPattern
{
protected:
    sf::Vector2f wallBounds;
    float imgWidth;
    float imgHeight;
public:
    virtual void ShootBullets() = 0;
    virtual void Update(float dt) = 0;
    virtual void SetCharceterAll(Player* player,Boss* boss) = 0; 
    virtual void SetWallBounds(sf::Vector2f pos, float width, float height) = 0;
};

