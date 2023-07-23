#pragma once
#include "ShootPattern.h"
class Player;
class Boss;
class UniqueShootMGR
{
protected:

    std::vector<ShootPattern*> patterns;  // �پ��� ���� ������ �����ϴ� �����̳�
    int currentPatternIndex = 0;  // ���� Ȱ��ȭ�� ���� ������ �ε���

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

