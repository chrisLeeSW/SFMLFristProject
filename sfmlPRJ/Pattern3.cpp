#include "stdafx.h"
#include "Pattern3.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern3::Pattern3()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
}

void Pattern3::ShootBullets()
{
    Scene* scene = SCENE_MGR.GetCurrScene();
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int shootCount = 2;
    float minFrequency = 2.f;  // 최소 주파수
    float maxFrequency = 50.f;  // 최대 주파수
    float amplitude = 10.0f;   // 진폭

    for (int count = 0; count <= shootCount; ++count)
    {
        Shoot* shoot = bossShootPool.Get();
        shoot->SetPlayer(player);

        sf::Vector2f playerPosition = player->GetPosition();
        sf::Vector2f shootDirection = playerPosition - boss->GetPosition();
        float angle = Utils::Angle(shootDirection.y, playerPosition.x);
        float frequency = minFrequency + static_cast<float>(count) / shootCount * (maxFrequency - minFrequency);
        // 주파수를 적용하여 각도에 변화를 줌
        angle += Utils::DegreesToRadians(10.0f * (count ));
        angle += std::sin(frequency * count) * amplitude;

        shoot->SetPattenInfo(Shoot::NoramalPatten::FrequencyType, boss->GetPosition(), angle, "BossNormalShooting1", minFrequency, maxFrequency);
        shoot->sortLayer = -1;

        if (sceneGame != nullptr)
        {
            sceneGame->AddGo(shoot);
        }
    }

}

void Pattern3::Update(float dt)
{
}
