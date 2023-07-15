#include "stdafx.h"
#include "Pattern1.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern1::Pattern1()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
}

void Pattern1::ShootBullets()
{
	std::string str ="BossNormalShooting1";
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	int shootCount = 5;
	for (int count = 0;count < shootCount;++count)
	{
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		sf::Vector2f playerPosition = player->GetPosition();
		sf::Vector2f shootDirection = playerPosition - boss->GetPosition();
		float angle = Utils::Angle(shootDirection.y, playerPosition.x);
		if (count >= 1)
		{
			if (count % 2 == 1)
				angle += Utils::DegreesToRadians(10.0f * (count / 2 + 1)); // 1 2 
			else if (count % 2 == 0)
				angle += Utils::DegreesToRadians(-10.0f * (count / 2)); // 1 2
		}
		//shoot->BossNormalFire(boss->GetPosition(), angle, "BossNormalShooting1");
		shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, boss->GetPosition(), angle, str);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
		std::cout <<"Pattern1 : "<< bossShootPool.GetPool().size() << std::endl;
	}
}