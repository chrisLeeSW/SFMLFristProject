#include "stdafx.h"
#include "Pattern7.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"

#include <thread>
Pattern7::Pattern7()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};

}

void Pattern7::ShootBullets()
{
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 20;
    float maxAngle = Utils::DegreesToRadians(720.f);
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);
        float angle = Utils::Lerp(0.f, maxAngle, static_cast<float>(count) / (shootCount - 1));
        shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, boss->GetPosition(), angle, "BossNormalShooting1");
        shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
        shoot->sortLayer = -1;
        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }
}

void Pattern7::Update(float dt)
{
}

void Pattern7::SetWallBounds(sf::Vector2f pos, float width, float height)
{
    wallBounds = pos;
    imgWidth = width;
    imgHeight = height;
}


// 특수패턴 만들기 ..

/*
	그냥 원형 터짐
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 30;
    float angleInterval = 360.f / shootCount;
    float delayTime = 0.05f; // 딜레이 타임 (초 단위)
    for (int count = 0; count < shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);

        float angle = angleInterval * count;
        shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, sf::Vector2f{0.f,0.f}, angle, "BossNormalShooting1");

        shoot->sortLayer = -1;
        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }


*/