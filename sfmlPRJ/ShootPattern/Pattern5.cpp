#include "stdafx.h"
#include "Pattern5.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern5::Pattern5()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
}

void Pattern5::ShootBullets()
{
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 5;
    // 게임 벽 만든후 하나 추가할 예정  ↓
    float minXWall = -200.f;
    float maxXWall = 200.f;
    float minYWall = -200.f;
    float maxYWall = 200.f;
    if (minYWall < 0.f)     minYWall = -minYWall;
    float distanceWall = minYWall + maxYWall;
    float space = distanceWall / shootCount;
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);
        shoot->SetPattenInfo(Shoot::NoramalPatten::RowRightType, sf::Vector2f{ minXWall,-space + (space * count) }, 0.f, "BossNormalShooting1");
        shoot->sortLayer = -1;

        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }
}

void Pattern5::Update(float dt)
{
}
