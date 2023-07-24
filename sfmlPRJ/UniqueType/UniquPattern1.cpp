#include "stdafx.h"
#include "UniquPattern1.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
UniquPattern1::UniquPattern1()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
}

void UniquPattern1::ShootBullets()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	int bulletCount = Utils::RandomRange(100, 300);
	float triangleWidth = 50.f;
	float triangleHeight = 50.f;
	float angleInterval = 360.f / bulletCount;
	for (int i = 0; i < bulletCount; i++)
	{
		float angle = angleInterval * i;
		float xOffset = std::cos(Utils::DegreesToRadians(angle)) * triangleWidth;
		float yOffset = std::sin(Utils::DegreesToRadians(angle)) * triangleHeight;
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, boss->GetPosition() + sf::Vector2f(xOffset, yOffset), angle, "BossNormalShooting1", 100.f); // angle °ª °¡´É
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}

void UniquPattern1::Update(float dt)
{
}

void UniquPattern1::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
