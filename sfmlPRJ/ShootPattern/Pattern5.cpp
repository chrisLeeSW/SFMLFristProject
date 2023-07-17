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
    int shootCount = 10;
    // 게임 벽 만든후 하나 추가할 예정  ↓
    float minYWall = wallBounds.y;
    float maxYWall = imgHeight;
    if (minYWall < 0.f)     minYWall = -minYWall;
    float distanceWall = minYWall + maxYWall;
    float space = distanceWall / shootCount;
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);
        shoot->SetPattenInfo(Shoot::NoramalPatten::RowRightType, sf::Vector2f{ wallBounds.x ,wallBounds.y + space + (space / 2 * count) }, 0.f, "BossNormalShooting1");
        shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
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

void Pattern5::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    wallBounds = pos;
    imgWidth = width;
    imgHeight = height;
}
