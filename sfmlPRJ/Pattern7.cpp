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
    sf::Clock clock;
    float dt = clock.getElapsedTime().asSeconds();

    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 30;
    float angleInterval = 360.f / shootCount;
    float delayTime = 0.05f; // 딜레이 타임 (초 단위)
    for (int count = 0; count < shootCount;)
    {
        delayTime -= dt;
        if (delayTime< 0.f)
        {
            Shoot* shoot = bossShootPool.Get();
            shoot->SetPlayer(player);
            float angle = angleInterval * count;
            shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, sf::Vector2f{ 0.f,0.f }, angle, "BossNormalShooting1");

            shoot->sortLayer = -1;
            if (sceneGame != nullptr)
            {
                sceneGame->AddGo(shoot);
            }
            delayTime = 0.05f;
            ++count;
        }

    }
}

void Pattern7::Update(float dt)
{

    //Scene* scene = SCENE_MGR.GetCurrScene();
    //SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    //int shootCount = 30;
    //float angleInterval = 360.f / shootCount;
    //float delayTime = 0.5f; // 딜레이 타임 (초 단위)
    //for (int count = 0; count < shootCount;)
    //{
    //    delayTime -= dt;
    //    if (delayTime < 0.f)
    //    {
    //        Shoot* shoot = bossShootPool.Get();
    //        shoot->SetPlayer(player);
    //        float angle = angleInterval * count;
    //        shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, sf::Vector2f{ 0.f,0.f }, angle, "BossNormalShooting1");

    //        shoot->sortLayer = -1;
    //        if (sceneGame != nullptr)
    //        {
    //            sceneGame->AddGo(shoot);
    //        }
    //        delayTime = 0.5f;
    //        ++count;
    //    }

    //}
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