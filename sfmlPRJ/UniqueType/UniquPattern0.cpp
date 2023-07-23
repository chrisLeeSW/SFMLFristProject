#include "stdafx.h"
#include "UniquPattern0.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"

UniquPattern0::UniquPattern0()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
}

void UniquPattern0::ShootBullets()
{
	int maxCount = 30;
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	float angleInterval = 360.f / maxCount;
	for (int i = 0; i < 30; ++i)
	{
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		float angle = angleInterval * i;
		shoot->SetPattenInfo(Shoot::NoramalPatten::DelayTimeAttackOneType, boss->GetPosition(), "BossNormalShooting1", angle, 1.f + (i * .5f), 100.f);
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}

void UniquPattern0::Update(float dt)
{
}

void UniquPattern0::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
