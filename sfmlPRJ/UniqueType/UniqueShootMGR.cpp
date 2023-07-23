#include "stdafx.h"
#include "UniqueShootMGR.h"
#include "Player.h"
#include "Boss.h"
#include "UniquPattern0.h"
#include "UniquPattern1.h"
#include "UniquPattern2.h"
#include "UniquPattern3.h"
UniqueShootMGR::UniqueShootMGR()
{
    patterns.push_back(new UniquPattern0());
	patterns.push_back(new UniquPattern1());
    patterns.push_back(new UniquPattern2());
    patterns.push_back(new UniquPattern3());
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
    patterns[currentPatternIndex]->Update(dt);
}

void UniqueShootMGR::ShootBullets()
{
    patterns[currentPatternIndex]->ShootBullets();
}

void UniqueShootMGR::SetCharacterAll(Player* player, Boss* boss)
{
    patterns[currentPatternIndex]->SetCharceterAll(player, boss);
}
void UniqueShootMGR::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    patterns[currentPatternIndex]->SetWallBounds(pos, width, height);
}
