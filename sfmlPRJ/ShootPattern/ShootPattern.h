#pragma once
class Player;
class Boss;

class ShootPattern
{
protected:
public:
    virtual void ShootBullets() = 0;
    virtual void Update(float dt) = 0;
    virtual void SetCharceterAll(Player* player,Boss* boss) = 0; 
};

