#include "stdafx.h"
#include "Pattern2.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern2::Pattern2()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
}

void Pattern2::ShootBullets()
{
	std::string str = "BossNormalShooting2";
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	int shootCount = 6;
	float pattenAngle = 360.f / shootCount;
	for (int count = 0; count < shootCount; ++count)
	{
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);

		float additionalAngle = pattenAngle * count;
		shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, boss->GetPosition(), additionalAngle, str);
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}

void Pattern2::Update(float dt)
{
}


void Pattern2::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
