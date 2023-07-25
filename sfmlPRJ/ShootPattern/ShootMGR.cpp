#include "stdafx.h"
#include "ShootMGR.h"

#include "Pattern1.h"
#include "Pattern2.h"
#include "Pattern3.h"
#include "Pattern4.h"
#include "Pattern5.h"
ShootMGR::ShootMGR() : currentPatternIndex(0)
{
    patterns.push_back(new Pattern1());
    patterns.push_back(new Pattern2());
    patterns.push_back(new Pattern3());
    patterns.push_back(new Pattern4());
    patterns.push_back(new Pattern5());
}

ShootMGR::~ShootMGR()
{
    for (auto pattern : patterns)
    {
        if (pattern != nullptr)
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
        std::cout << "ERR: isNot pattern" << std::endl;
        return;
    }
}

void ShootMGR::Update(float dt)
{
    patterns[currentPatternIndex]->Update(dt);
}

void ShootMGR::ShootBullets()
{
    patterns[currentPatternIndex]->ShootBullets();
}

void ShootMGR::SetCharacterAll(Player* player, Boss* boss)
{
    patterns[currentPatternIndex]->SetCharceterAll(player, boss);
}

void ShootMGR::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    patterns[currentPatternIndex]->SetWallBounds(pos, width, height);
}

