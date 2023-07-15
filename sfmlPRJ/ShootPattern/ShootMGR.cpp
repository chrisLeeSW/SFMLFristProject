#include "stdafx.h"
#include "ShootMGR.h"

#include "Pattern1.h"
#include "Pattern2.h"
#include "Pattern3.h"
ShootMGR::ShootMGR() : currentPatternIndex(0)
{
    patterns.push_back(new Pattern1());
    patterns.push_back(new Pattern2());
    patterns.push_back(new Pattern3());
}

ShootMGR::~ShootMGR()
{
    for (auto pattern : patterns)
    {
        delete pattern;
    }
}

void ShootMGR::ChangePattern(int patternIndex)
{
    if (patternIndex >= 0 && patternIndex < patterns.size())
    {
        currentPatternIndex = patternIndex;
    }
    else
    {
        std::cout << "ERR: Do not use pattern" << std::endl;
        return;
    }
}

void ShootMGR::Update(float dt)
{
   // patterns[currentPatternIndex]->Update(dt);
}

void ShootMGR::ShootBullets()
{
    patterns[currentPatternIndex]->ShootBullets();
}

void ShootMGR::SetCharacterAll(Player* player, Boss* boss)
{
    patterns[currentPatternIndex]->SetCharceterAll(player, boss);
}

