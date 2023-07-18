#include "stdafx.h"
#include "Pattern4.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"

Pattern4::Pattern4()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		//bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
    bossShootPool.Init();
}

void Pattern4::ShootBullets()
{
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 20;
    // 게임 벽 만든후 하나 추가할 예정  ↓
    float minXWall = wallBounds.x;
    float maxXWall = imgWidth;
    if (minXWall < 0.f)     minXWall = -minXWall;
    float distanceWall = minXWall + maxXWall;
    float space = distanceWall / shootCount;
    float start = wallBounds.x + space;
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);
        shoot->SetPattenInfo(Shoot::NoramalPatten::ColumnType, sf::Vector2f{ wallBounds.x+space+(space/2 *count),boss->GetPosition().y}, 0.f, "BossNormalShooting1");
        shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
        shoot->sortLayer = -1;

        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }
}

void Pattern4::Update(float dt)
{
}

void Pattern4::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    wallBounds = pos;
    imgWidth = width;
    imgHeight = height;
}
