#pragma once
#include "ShootPattern.h"
class Boss;
class Player;
class ShootMGR
{
protected:
	std::vector<ShootPattern*> patterns;  // 다양한 슈팅 패턴을 보유하는 컨테이너
	int currentPatternIndex =0;  // 현재 활성화된 슈팅 패턴의 인덱스

  
public:
    ShootMGR();
    ~ShootMGR();

    void ChangePattern(int patternIndex);
    void Update(float dt);
    void ShootBullets();
    void SetCharacterAll(Player* player, Boss* boss);
};
