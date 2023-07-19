#include "stdafx.h"
#include "Pattern6.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern6::Pattern6()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
    bossShootPool.Init();
}

void Pattern6::ShootBullets()
{
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount =5;
    float minYWall =wallBounds.y;
    float maxYWall = imgHeight*0.5f;
    if (minYWall < 0.f)     minYWall = -minYWall;
    float distanceWall = minYWall + maxYWall;
    float space = distanceWall / shootCount;
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);
        shoot->SetPattenInfo(Shoot::NoramalPatten::RowLeftType, sf::Vector2f{ wallBounds.x+imgWidth,wallBounds.y +20.f + (space * count )}, 0.f, "BossNormalShooting1");
        shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
        shoot->sortLayer = -1;
        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }

}

void Pattern6::Update(float dt)
{
}

void Pattern6::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    wallBounds = pos;
    imgWidth = width;
    imgHeight = height;
}
