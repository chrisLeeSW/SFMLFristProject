#pragma once
#include "ShootPattern.h"
class Boss;
class Player;
class ShootMGR
{
protected:
	std::vector<ShootPattern*> patterns;  // �پ��� ���� ������ �����ϴ� �����̳�
	int currentPatternIndex =0;  // ���� Ȱ��ȭ�� ���� ������ �ε���

  
public:
    ShootMGR();
    ~ShootMGR();

    void ChangePattern(int patternIndex);
    void Update(float dt);
    void ShootBullets();
    void SetCharacterAll(Player* player, Boss* boss);
};
