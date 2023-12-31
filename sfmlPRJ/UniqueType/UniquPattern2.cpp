#include "stdafx.h"
#include "UniquPattern2.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
UniquPattern2::UniquPattern2()
{
}

void UniquPattern2::ShootBullets()
{
	int maxCount = 30;
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	float angleInterval = 360.f / maxCount;
	for (int i = 0; i < maxCount; ++i)
	{
		Shoot* shoot = boss->GetObjectPool().Get();
		shoot->SetPlayer(player);
		float angle = angleInterval * i;

		float radius = 10.f;
		float centerX = boss->GetPosition().x;
		float centerY = boss->GetPosition().y;

		float radian = Utils::DegreesToRadians(angle - 90.f);

		float x = centerX + radius * std::cos(radian);
		float y = centerY + radius * std::sin(radian);

		shoot->SetPattenInfo(Shoot::NoramalPatten::TornadoTypeLoof, sf::Vector2f(x, y), angle, "BossNormalShooting1", 100.f);
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}

void UniquPattern2::Update(float dt)
{
}

void UniquPattern2::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
