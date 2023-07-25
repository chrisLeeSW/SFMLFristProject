#include "stdafx.h"
#include "UniquPattern3.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
UniquPattern3::UniquPattern3()
{

}

void UniquPattern3::ShootBullets()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	for (int i = 1; i <= 50; ++i)
	{
		float randXpos = Utils::RandomRange(-400.f, 100.f);
		float randYpos = Utils::RandomRange(-300.f, 0.f);
		Shoot* shoot = boss->GetObjectPool().Get();
		shoot->SetPlayer(player);
		shoot->SetPattenInfo(Shoot::NoramalPatten::DelayTimeAttackTwoType, { randXpos,randYpos }, "BossNormalShooting1", 300.f, (0.5f + i * 0.5f)); //  새로운 딜레이타임 만들기
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}

void UniquPattern3::Update(float dt)
{
}

void UniquPattern3::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
