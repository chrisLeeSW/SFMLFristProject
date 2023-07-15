#include "stdafx.h"
#include "Pattern2.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern2::Pattern2()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
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
		//shoot->BossNormalFirePatten1(boss->GetPosition(), additionalAngle, "BossNormalShooting2");
		shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, boss->GetPosition(), additionalAngle, str);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}
