#include "stdafx.h"
#include "UniqueShootMGR.h"
#include "Player.h"
#include "Boss.h"

#include "Pattern7.h"
UniqueShootMGR::UniqueShootMGR()
{
	//patterns.push_back(new Pattern7());
}

UniqueShootMGR::~UniqueShootMGR()
{
	for (auto& pattern : patterns)
	{
		if (pattern != nullptr)
			delete pattern;
	}
}

void UniqueShootMGR::ChangePattern(int patternIndex)
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

void UniqueShootMGR::Update(float dt)
{
    patterns[currentPatternIndex]->ShootBullets();
}

void UniqueShootMGR::ShootBullets()
{
    patterns[currentPatternIndex]->SetCharceterAll(player, boss);
}

void UniqueShootMGR::SetCharacterAll(Player* player, Boss* boss)
{
    patterns[currentPatternIndex]->SetCharceterAll(player, boss);
}
