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

	{
		NormalAttackInfo info;
		info.animationClipId = "BossNormalShooting1";
		info.bulletCount = 5;
		info.maxSpeed = 500.f;

		attackInfo.push_back(info);
	}
}

void Boss::Release()
{
	SpriteGo::Release();
	bossShootPool.Release();
}

void Boss::Reset()
{
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(-270.f, -250.f);
}

void Boss::Update(float dt)
{
	BossMove(dt);

	animation.Update(dt);
	SpriteGo::Update(dt);
}

void Boss::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Boss::BossMove(float dt)
{
	bossAtk -= dt;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad4))
	{
		direction.x = -1.f;
		SetScale(1.f, 1.f);
		if (!moveBoss)
		{
			animation.Play("Move");
			moveBoss = true;
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad6))
	{
		direction.x = 1.f;
		SetScale(-1.f, 1.f);
		if (!moveBoss)
		{
			animation.Play("Move");
			moveBoss = true;
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad8))
	{
		direction.y = -1.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad5))
	{
		direction.y = 1.f;
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad4) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad5) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad6) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad8))
	{
		direction = { 0.f,0.f };
		animation.Play("Idle");
		moveBoss=false;
	}

	bossAttackTime -= dt;
	position += direction * speed * dt;
	SetPosition(position);


	if (GetPosition().x - sprite.getGlobalBounds().width * 0.5f < WallBounds.x)
	{
		SetPosition(WallBounds.x + bgWidth - sprite.getGlobalBounds().width * 0.5f, GetPosition().y);
	}
	else if (GetPosition().x + sprite.getGlobalBounds().width * 0.5f > WallBounds.x + bgWidth)
	{
		SetPosition(WallBounds.x + sprite.getGlobalBounds().width * 0.5f, GetPosition().y);
	}
	else if (GetPosition().y + sprite.getGlobalBounds().height * 0.5f > WallBounds.y + bgHeight)
	{
		SetPosition(GetPosition().x, WallBounds.y + bgHeight - sprite.getGlobalBounds().height * 0.5f);
	}
	else if (GetPosition().y - sprite.getGlobalBounds().height * 0.5f < WallBounds.y)
	{
		SetPosition(GetPosition().x, WallBounds.y + sprite.getGlobalBounds().height * 0.5f);
	}


	/*if (bossHp > 750 && !onePage)
	{
		onePage = true;
		rand1 = Utils::RandomRange(0, 6);
		rand2 = Utils::RandomRange(0, 6);
	}
	if (onePage && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;

		shootPatternMgr.ChangePattern(rand1);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();

		shootPatternMgr.ChangePattern(rand2);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();
	}
	if (onePageCk.getElapsedTime().asSeconds() > 20.f)
	{
		onePage = false;
		onePageCk.restart();
	}*/

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad0) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(0);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();
		
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad1) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(1);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
		
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(2);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad3) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(3);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Num1) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(4);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
		
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Num2) && bossAttackTime < 0.2f)
	{
		bossAttackTime = 0.3f;
		bossAttackTime = 0.3f;
		shootPatternMgr.ChangePattern(5);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
	
	}
	//
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		bossAttackTime = 0.3f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		shoot->SetPositionTest(position, { 0.f,1.f });
		shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot); //
		}
	}
	if (testShootBullet)
	{
		//shootPatternMgr.ChangePattern(6);
		//shootPatternMgr.SetCharacterAll(player, this);

		if (bossAtk < 0.f && count != maxCount)
		{
			//shootPatternMgr.Update(dt);

			Scene* scene = SCENE_MGR.GetCurrScene();
			SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
			float angleInterval = 360.f / maxCount;

			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			float angle = angleInterval * count;
			shoot->SetPattenInfo(Shoot::NoramalPatten::AngleDirectionType, poolShootPos, angle, "BossNormalShooting1");
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
			++count;
			bossAtk = delay;
		}

	}
	if (count == maxCount && testShootBullet)
	{
		testShootBullet = false;
		count = 0;
	}

}

bool Boss::CheckCollisionWithBullet(const Shoot& bullet)
{
	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		std::cout << "isCollied Boss" << std::endl;
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

sf::Vector2f Boss::CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, float t)
{
		float u = 1.0f - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		sf::Vector2f p = uuu * p0; // (1-t)^3 * P0
		p += 3 * uu * t * p1;      // 3 * (1-t)^2 * t * P1
		p += 3 * u * tt * p2;      // 3 * (1-t) * t^2 * P2
		p += ttt * p3;             // t^3 * P3

		return p;
}




// 폐기 탄막 -> 목적은 토네이도식이지만 1번과 별차이를 모르겠음 
//if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
//{
//	testTime = 1.0f;
//	Scene* scene = SCENE_MGR.GetCurrScene();
//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
//	const int bulletCount = 3;  // 총알 개수
//	const float tornadoRadius = 100.f;  // 토네이도의 반지름
//	const float rotationSpeed = 120.f;  // 회전 속도 (각도/초)
//
//	float startAngle = -90.f;  // 시작 각도 (12시 방향)
//	float angleStep = 360.f / bulletCount;  // 각도 단계
//	for (int i = 0; i < bulletCount; ++i)
//	{
//		float angle = startAngle + i * angleStep;
//		float radian = Utils::DegreesToRadians(angle);
//		float offsetX = std::cos(radian) * tornadoRadius;
//		float offsetY = std::sin(radian) * tornadoRadius;
//
//		Shoot* shoot = bossShootPool.Get();
//		shoot->SetPlayer(player);
//		shoot->BossNormalFirePatten1(position + sf::Vector2f(offsetX, offsetY), angle, "BossNormalShooting2");
//		shoot->sortLayer = -1;
//		if (sceneGame != nullptr)
//		{
//			sceneGame->AddGo(shoot);
//		}
//	}
//}


//패턴: 방사형 원형 탄막
	//if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
	//{
	//	testTime = 1.0f;
	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	//	const int bulletCount = 12;  // 총알 개수
	//	const float radius = 100.f;  // 원의 반지름
	//	const float angleStep = 360.f / bulletCount;  // 각도 단계

	//	for (int i = 0; i < bulletCount; ++i)
	//	{
	//		float angle = angleStep * i;
	//		float radian = Utils::DegreesToRadians(angle);
	//		sf::Vector2f offset = sf::Vector2f(std::cos(radian), std::sin(radian)) * radius;

	//		// 총알 생성 및 설정
	//		Shoot* shoot = bossShootPool.Get();
	//		shoot->SetPlayer(player);
	//		shoot->BossNormalFirePatten1(GetPosition() + offset, angle, "BossNormalShooting2");
	//		shoot->sortLayer = -1;
	//		if (sceneGame != nullptr)
	//		{
	//			sceneGame->AddGo(shoot);
	//		}
	//	}
	//}


//if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
	//{
	//	testTime = 1.0f;
	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	//	const int bulletCount = 10;  // 총알 개수

	//	// 이전 총알의 위치를 초기화
	//	sf::Vector2f previousPosition = GetPosition();

	//	// 총알 생성 및 초기화
	//	for (int i = 0; i < bulletCount; ++i)
	//	{
	//		Shoot* bullet = bossShootPool.Get();
	//		bullet->SetPlayer(player);

	//		// 총알의 시작 위치 계산
	//		float startDistance = 20.f;  // 시작 위치와의 거리
	//		float distanceInterval = 10.f;  // 총알 간의 거리 간격
	//		sf::Vector2f startPosition = previousPosition - sf::Vector2f(startDistance * i, distanceInterval * i);
	//		bullet->SetPosition(startPosition);

	//		// 총알의 이동 방향 계산
	//		float bulletAngle = Utils::DegreesToRadians(90.f);  // 총알의 기본 이동 각도 (직진)
	//		float angleRange = 30.f;  // 총알의 각도 범위
	//		float angleOffset = angleRange * i / (bulletCount - 1) - angleRange * 0.5f;  // 총알의 각도 오프셋
	//		bulletAngle += Utils::DegreesToRadians(angleOffset);
	//		sf::Vector2f bulletDirection = sf::Vector2f(std::cos(bulletAngle), std::sin(bulletAngle));
	//		bullet->testFire(startPosition, bulletDirection, 90);

	//		// 총알을 게임에 추가
	//		if (sceneGame != nullptr)
	//		{
	//			sceneGame->AddGo(bullet);
	//		}

	//		previousPosition = startPosition; // 현재 총알의 시작 위치를 이전 총알의 위치로 설정
	//	}
	//}
