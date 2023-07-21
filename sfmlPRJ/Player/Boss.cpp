#include "stdafx.h"
#include "Boss.h"
#include "SceneGame.h"
#include "Scene.h"
#include "Player.h"

void Boss::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Move.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(this);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();


	moveTime = 0.f;
	moveTimerDuration = 0.f;
	startPos = sf::Vector2f{ -270.f, -250.f };
	endPos = sf::Vector2f({ 0.f, -50.f });
	secondPos = sf::Vector2f(-200.f, 0.f);
	attackRand1 = Utils::RandomRange(0, 6);

}

void Boss::Release()
{
	SpriteGo::Release();
	bossShootPool.Release();
}

void Boss::Reset()
{
	bossShootPool.Clear();
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(-300.f,0.f);
//	SetPosition(-270.f, -250.f);
	bossHp = 810;
	startPos = sf::Vector2f{ -270.f, -250.f };
	endPos = sf::Vector2f({ 0.f, -50.f });
	secondPos = sf::Vector2f(-200.f, 0.f);
	moveTime = 0.f;
	moveTimerDuration = 0.f;
	bossAttackNoramalPatternChangeTime = 0.f;
	bossAttackTimeOneLimit = 1.0f;
	stopAttackTime = 0.f;
	bossDie = false;
	startGame = 0.f;
	score = 0;
	count = 0;
}

void Boss::Update(float dt)
{
	if (bossHp == 0.f)
		bossDie = true;
	if (!bossDie && !player->GetPlayerDie())
	{
		direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
		BossMove(dt);
		BossFireUcnique(dt);
		BossFireNormal(dt);
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		if (INPUT_MGR.GetKey(sf::Keyboard::Tab) && sceneGame->GetBoombCountSpriteCurrent()>=0 && player->GetEffectDraw() && !useBoomb)
		{
			sceneGame->UseBoomb();
			bossShootPool.Clear();
			useBoomb = true;
		}

		animation.Update(dt);
		SpriteGo::Update(dt);
	}
}

void Boss::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Boss::BossMove(float dt)
{
	bossAtk -= dt;


	moveTime += dt;
	moveTimerDuration += dt;
	float t = moveTime / moveDuration;
	/*if (t >= 1.f)
	{
		t = 1.f;
	}
	if (position == endPos)
	{
		animation.Play("Idle");
		moveBoss = false;
		stopBoss = true;
		if (moveTimerDuration > stopLimit)
		{
			stopBoss = false;
			moveTime = 0.f;
			moveTimerDuration = 0.f;
			startPos = position;
			secondPos = sf::Vector2f(Utils::RandomRange(0, 500), -Utils::RandomRange(0, 150));
			if (secondPos.x > 200.f)
				secondPos.x = -secondPos.x;
			endPos = sf::Vector2f(Utils::RandomRange(0, 500), -Utils::RandomRange(0, 150));
			if (endPos.x > 200.f)
				endPos.x = -endPos.x;
		}
	}
	sf::Vector2f p = CalculateBezierPoint(startPos, secondPos, endPos, t);
	if (p.x - sprite.getGlobalBounds().width * 0.5f < WallBounds.x)
	{
		p.x = WallBounds.x + sprite.getGlobalBounds().width * 0.5f;
	}
	else if (p.x + sprite.getGlobalBounds().width * 0.5f > WallBounds.x + bgWidth)
	{
		p.x = WallBounds.x + bgWidth - sprite.getGlobalBounds().width * 0.5f;
	}

	if (p.y + sprite.getGlobalBounds().height * 0.5f > WallBounds.y + bgHeight)
	{
		p.y = WallBounds.y + bgHeight - sprite.getGlobalBounds().height * 0.5f;
	}
	else if (p.y - sprite.getGlobalBounds().height * 0.5f < WallBounds.y)
	{
		p.y = WallBounds.y + sprite.getGlobalBounds().height * 0.5f;
	}
	position = p;
	if (position.x != 0.f)
	{
		if (!moveBoss)
		{
			SetScale(1.f, 1.f);
			animation.Play("Move");
			moveBoss = true;
		}
	}*/
	position += direction * speed * dt;
	SetPosition(position);


}

void Boss::BossFireUcnique(float dt)
{
	stopAttackTime -= dt;

	/*if (stopBoss && stopAttackTime < stopAttackTimeLimit)
	{
		stopAttackTime = 4.0f;
		uniqueshootPatternMgr.ChangePattern(0);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();
	}*/
}

void Boss::BossFireNormal(float dt)
{
	bossAttackNoramalPatternChangeTime += dt;
	bossAttackTimeOne -= dt;

	//if (attackRand1 == 2)
	//{
	//	bossAttackTimeOneLimit = 0.2f;
	//}
	//else
	//{
	//	bossAttackTimeOneLimit = 1.0f;
	//}
	//if (bossAttackNoramalPatternChangeTime > bossAttackNoramalPatternChangeTimeLimit)
	//{
	//	int prevType = attackRand1;
	//	attackRand1 = Utils::RandomRange(0, 6);
	//	if (prevType == attackRand1)
	//		attackRand1 = Utils::RandomRange(0, 6);
	//	bossAttackNoramalPatternChangeTime = 0.f;
	//}
	//if (bossHp > 750 && bossAttackTimeOne < bossAttackTimeOneLimit)
	//{
	//	bossAttackTimeOne = bossAttackTimeOneLimit + 0.3f;
	//	shootPatternMgr.ChangePattern(attackRand1);
	//	shootPatternMgr.SetCharacterAll(player, this);
	//	shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
	//	shootPatternMgr.ShootBullets();
	//}


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		float angleInterval = 360.f / maxCount;
		for (int i = 0;i < 30;++i)
		{
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			float angle = angleInterval * i;
			shoot->SetPattenInfo(Shoot::NoramalPatten::DelayTimeAttackOneType, GetPosition(), "BossNormalShooting1", angle, 1.f +(i*.5f),250.f );
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		testShootBullet = true;
		
	}

	if (testShootBullet && bossAtk < 0.f && count != maxCount)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		float angleInterval = 360.f / maxCount;

		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		float angle = angleInterval * count;
		shoot->SetPattenInfo(Shoot::NoramalPatten::testcode3, GetPosition(), angle, "BossNormalShooting1", 250.f);
		shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
		++count;
		bossAtk = delay;
	}
	if ((count == maxCount) && testShootBullet)
	{
		testShootBullet = false;
		count = 0;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	
		for (int i = 0;i < 30;++i)
		{
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			sf::Vector2f pos = Utils::RandomOnCircle(10.f+i*10.f);
			shoot->SetPattenInfo(Shoot::NoramalPatten::ColumnType, pos, "BossNormalShooting1");
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		for(int i=1;i<=5;++i)
		{
			
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			shoot->SetPattenInfo(Shoot::NoramalPatten::testcode,GetPosition() + sf::Vector2f(20.f*i, -20.f*i), 45.f, "BossNormalShooting1", 250.f);
			std::cout << GetPosition().x << "\t" << GetPosition().y << std::endl;
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
}
/*
for (int count = 0;count < shootCount;++count)
	{
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		float angle = Utils::DegreesToRadians(90.f);
		if (count >= 1)
		{
			if (count % 2 == 1)
				angle += Utils::DegreesToRadians(10.0f * (count / 2 + 1)); // 1 2
			else if (count % 2 == 0)
				angle += Utils::DegreesToRadians(-10.0f * (count / 2)); // 1 2
		}
		shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, boss->GetPosition(), angle, str,250.f);
		shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot); //
		}

	}
*/



bool Boss::CheckCollisionWithBullet(const Shoot& bullet)
{

	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		bossHp -= player->GetGetPlayerDamage();
		score++;
		return true;
	}

	return false;
}

void Boss::SetWallBounds(sf::Vector2f boundf, float widthX, float widthY)
{
	bgWidth = widthX;
	bgHeight = widthY;
	WallBounds = boundf;
}


sf::Vector2f Boss::CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, float t)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	sf::Vector2f p = uuu * p0;
	p += 3 * uu * t * p1;
	p += 3 * u * tt * p2;
	p += ttt * p2;

	return p;
}

sf::Vector2f Boss::RotateVector(const sf::Vector2f& vector, float angleDegrees) {
	float angleRadians = angleDegrees * (3.14159265359f / 180.0f); // Convert degrees to radians
	float cosAngle = std::cos(angleRadians);
	float sinAngle = std::sin(angleRadians);

	float rotatedX = vector.x * cosAngle - vector.y * sinAngle;
	float rotatedY = vector.x * sinAngle + vector.y * cosAngle;

	return sf::Vector2f(rotatedX, rotatedY);
}



//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5)) // 원형으로 내려감
	//{
	//}
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	//{
	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	//	int bulletCount = 30;
	//	float triangleHeight = 100.f;
	//	float startingYPos = 0.f;
	//	float angleInterval = 360.f / bulletCount;
	//	for (int i = 0; i < bulletCount; i++)
	//	{
	//		float angle = angleInterval * i;
	//		Shoot* shoot = bossShootPool.Get();
	//		shoot->SetPlayer(player);
	//		shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
	//		sf::Vector2f vertex1 = position;
	//		sf::Vector2f vertex2 = position + sf::Vector2f(triangleHeight * 0.5f, triangleHeight);
	//		sf::Vector2f vertex3 = position + sf::Vector2f(-triangleHeight * 0.5f, triangleHeight);
	//		sf::Vector2f bulletPos = vertex1 + ((vertex2 - vertex1) * (static_cast<float>(i) / (bulletCount - 1)));
	//		float angle2 = Utils::RandomRange(0, 360);
	//		shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, bulletPos, angle2, "BossNormalShooting1");
	//		if (sceneGame != nullptr)
	//		{
	//			sceneGame->AddGo(shoot);
	//		}
	//		/*Shoot* shoot2 = bossShootPool.Get();
	//		shoot2->SetPlayer(player);
	//		shoot2->SetWallBounds(WallBounds, bgWidth, bgHeight);
	//		sf::Vector2f vertex1Left = position;
	//		sf::Vector2f vertex2Left = position + sf::Vector2f(-triangleHeight * 0.5f, triangleHeight);
	//		sf::Vector2f vertex3Left = position + sf::Vector2f(triangleHeight * 0.5f, triangleHeight);
	//		sf::Vector2f bulletPosLeft = vertex1Left + ((vertex2Left - vertex1Left) * (static_cast<float>(i) / (bulletCount - 1)));
	//		shoot2->SetPattenInfo(Shoot::NoramalPatten::ColumnType, bulletPosLeft, "BossNormalShooting1");
	//		if (sceneGame != nullptr)
	//		{
	//			sceneGame->AddGo(shoot);
	//			sceneGame->AddGo(shoot2);
	//		}
	//		int totalLineBullets = bulletCount * 2 - 1;
	//		startingYPos = bulletPosLeft.y;
	//		if (i == bulletCount - 1)
	//		{
	//			for (int j = 1; j < totalLineBullets;++j)
	//			{
	//				Shoot* line = bossShootPool.Get();
	//				line->SetPlayer(player);
	//				line->SetWallBounds(WallBounds, bgWidth, bgHeight);
	//				sf::Vector2f vertex1Left1 = bulletPosLeft;
	//				sf::Vector2f vertex2Left2 = bulletPosLeft + sf::Vector2f(-triangleHeight, triangleHeight);
	//				sf::Vector2f vertex3Left3 = bulletPosLeft + sf::Vector2f(triangleHeight, triangleHeight);
	//				sf::Vector2f bulletPosLine = vertex1Left1 + ((vertex3Left3 - vertex1Left1) * (static_cast<float>(j) / (totalLineBullets - 1)));
	//				bulletPosLine.y = startingYPos;
	//				line->SetPattenInfo(Shoot::NoramalPatten::ColumnType, bulletPosLine, "BossNormalShooting1");
	//				if (sceneGame != nullptr)
	//				{
	//					sceneGame->AddGo(line);
	//				}
	//			}
	//		}
	//	}*/
	//	}
	//}

//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	//{
	//	bossAttackTimeOne = 0.3f;
	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	//	Shoot* shoot = bossShootPool.Get();
	//	shoot->SetPlayer(player);
	//	shoot->SetPositionTest(position, { 0.f,1.f });
	//	shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
	//	if (sceneGame != nullptr)
	//	{
	//		sceneGame->AddGo(shoot); //
	//	}
	//}
	//if (testShootBullet)
	//{
	//	if (bossAtk < 0.f && count != maxCount)
	//	{
	//		Scene* scene = SCENE_MGR.GetCurrScene();
	//		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	//		float angleInterval = 360.f / maxCount;

	//		Shoot* shoot = bossShootPool.Get();
	//		shoot->SetPlayer(player);
	//		float angle = angleInterval * count;
	//		shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, poolShootPos, angle, "BossNormalShooting1");
	//		shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
	//		shoot->sortLayer = -1;
	//		if (sceneGame != nullptr)
	//		{
	//			sceneGame->AddGo(shoot);
	//		}
	//		++count;
	//		bossAtk = delay;
	//	}
	//}
	//if ((count == maxCount) && testShootBullet)
	//{
	//	testShootBullet = false;
	//	count = 0;
	//}


