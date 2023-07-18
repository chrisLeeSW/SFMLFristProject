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

	moveRand = -1;
	moveTime = 0.f;


	p2 = sf::Vector2f({ 0.f, -50.f }); // 끝점
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
	moveRand = -1;
	moveTime = 0.f;
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
	moveTime += dt;
	bossAttackTimeOne -= dt;
	
	//sf::Vector2f p0(-300.f, -50.f); // 시작점
	//
	//sf::Vector2f p1(-200.f, 0.f); // 거치는 지점 1

	//float moveDuration = 1.f; // 이동 시간
	//float t = moveTime / moveDuration;

	//if (t >= 1.f)
	//{
	//	t = 1.f;
	//}

	//	sf::Vector2f p = CalculateBezierPoint(p0, p1, p2, t);
	//	position = p;
	//if (position == p2)
	//{
	//	moveTime = 0.f;
	//	p2 = sf::Vector2f({ -100.f, -150.f });
	//}
	//
	/*if (p.x - sprite.getGlobalBounds().width * 0.5f < WallBounds.x)
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
	}*/
	//std::cout << "POS X :" << position.x << "\t POS Y:" << position.y << std::endl;
	//if (moveTime >= 10.0f || moveRand == -1)
	//{
	//	moveRand = Utils::RandomRange(0, 5);
	//	moveTime = 0.f;
	//	std::cout << "Boss Rand : " << moveBoss << std::endl;
	//}
	//switch (moveRand)
	//{
	//case 0:
	//	direction.x = -0.3f;
	//	break;
	//case 1:
	//	direction.x = 0.13f;
	//	break;
	//default :
	//	direction.x = 0.f;
	//	break;
	//}
	//if (direction.x < 0.f)
	//{
	//	SetScale(1.f, 1.f);
	//	if (!moveBoss)
	//	{
	//		animation.Play("Move");
	//		moveBoss = true;
	//	}
	//}
	//else if (direction.x > 0.f)
	//{
	//	SetScale(-1.f, 1.f);
	//	if (!moveBoss)
	//	{
	//		animation.Play("Move");
	//		moveBoss = true;
	//	}
	//}
	//else if (direction.x == 0.f)
	//{
	//	animation.Play("Idle");
	//	moveBoss = false;
	//}
	//if (direction.x == 0.f && bossAttackTimeOne < 0.2f)
	//{
	//	bossAttackTimeOne = 0.4f;
	//	shootPatternMgr.ChangePattern(0);
	//	shootPatternMgr.SetCharacterAll(player, this);
	//	shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
	//	shootPatternMgr.ShootBullets();
	//}
	//if (direction.x != 0.f && bossAttackTimeOne < 0.2f)
	//{
	//	bossAttackTimeOne = 0.3f;
	//	shootPatternMgr.ChangePattern(2);
	//	shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
	//	shootPatternMgr.SetCharacterAll(player, this);
	//	shootPatternMgr.ShootBullets();
	//}



	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad4))
	{
		direction.x = -0.1f;
		SetScale(1.f, 1.f);
		if (!moveBoss)
		{
			animation.Play("Move");
			moveBoss = true;
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad6))
	{
		direction.x = 0.1f;
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
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad4) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad5) || 
		INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad6) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad8))
	{
		direction = { 0.f,0.f };
		animation.Play("Idle");
		moveBoss = false;
	}

	
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


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		std::cout<<" -x :"<< WallBounds.x<<std::endl;
		std::cout << " x :" << WallBounds.x + bgWidth << std::endl;
		std::cout << " -y :" << WallBounds.y << std::endl;
		std::cout << " -x :" << WallBounds.y + bgHeight << std::endl;
	}

	/*
	
	if (bossHp > 750 && !onePage)
	{
		onePage = true;
		rand1 = Utils::RandomRange(0, 6);
		rand2 = Utils::RandomRange(0, 6);
		std::cout << "rand 1 : " << rand1 << '\t' << "rand2 : " << rand2 << std::endl;
		if (rand1 == rand2)
		{
			rand2 = Utils::RandomRange(0, 6);
		}
	}
	if (onePage && bossAttackTimeOne < 0.3f)
	{
		bossAttackTimeOne = 0.5f;

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
		rand1 = -1;
		rand2 = -1;
	}
	
	*/

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad0) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(0);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();

	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad1) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(1);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();

	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(2);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad3) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(3);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Num1) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(4);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();

	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Num2) && bossAttackTimeOne < 0.2f)
	{
		bossAttackTimeOne = 0.3f;
		bossAttackTimeOne = 0.3f;
		shootPatternMgr.ChangePattern(5);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.ShootBullets();

	}
	//
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		bossAttackTimeOne = 0.3f;
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
		if (bossAtk < 0.f && count != maxCount)
		{
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
	if ((count == maxCount) && testShootBullet)
	{
		testShootBullet = false;
		count = 0;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		int i, j;

		for (i = 1;i <= 3;i++) {			//행 지정
			for (j = 2;j >= i;j--) {		//공백 출력
				printf(" ");
			}
			for (j = 1;j <= i * 2 - 1;j++) {		//별 출력
				printf("*");
			}
			printf("\n");
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5)) // 원형으로 내려감
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int bulletCount = 50;
		float triangleWidth = 50.f;
		float triangleHeight = 50.f;
		float angleInterval = 360.f / bulletCount;
		for (int i = 0; i < bulletCount; i++)
		{
			float angle = angleInterval * i;
			float xOffset = std::cos(Utils::DegreesToRadians(angle)) * triangleWidth;
			float yOffset = std::sin(Utils::DegreesToRadians(angle)) * triangleHeight;
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, position + sf::Vector2f(xOffset, yOffset),angle,  "BossNormalShooting1"); // angle 값 가능
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int bulletCount = 3; 
		float triangleHeight = 100.f; 
		float startingYPos = 0.f; 
		float angleInterval = 360.f / bulletCount;
		for (int i = 0; i < bulletCount; i++)
		{
			float angle = angleInterval * i;
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			sf::Vector2f vertex1 = position;
			sf::Vector2f vertex2 = position + sf::Vector2f(triangleHeight * 0.5f, triangleHeight);
			sf::Vector2f vertex3 = position + sf::Vector2f(-triangleHeight * 0.5f, triangleHeight);
			sf::Vector2f bulletPos = vertex1 + ((vertex2 - vertex1) * (static_cast<float>(i) / (bulletCount - 1)));
			shoot->SetPattenInfo(Shoot::NoramalPatten::ColumnType, bulletPos,  "BossNormalShooting1");


			Shoot* shoot2 = bossShootPool.Get();
			shoot2->SetPlayer(player);
			shoot2->SetWallBounds(WallBounds, bgWidth, bgHeight);
			sf::Vector2f vertex1Left = position;
			sf::Vector2f vertex2Left = position + sf::Vector2f(-triangleHeight * 0.5f, triangleHeight);
			sf::Vector2f vertex3Left = position + sf::Vector2f(triangleHeight * 0.5f, triangleHeight);
			sf::Vector2f bulletPosLeft = vertex1Left + ((vertex2Left - vertex1Left) * (static_cast<float>(i) / (bulletCount - 1)));
			shoot2->SetPattenInfo(Shoot::NoramalPatten::ColumnType, bulletPosLeft,  "BossNormalShooting1");
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
				sceneGame->AddGo(shoot2);
			}
			int totalLineBullets = bulletCount * 2 - 1;
			startingYPos = bulletPosLeft.y;
			if (i == bulletCount - 1)
			{

				for (int j = 1; j < totalLineBullets;++j)
				{
					Shoot* line = bossShootPool.Get();
					line->SetPlayer(player);
					line->SetWallBounds(WallBounds, bgWidth, bgHeight);
					sf::Vector2f vertex1Left1 = bulletPosLeft;
					sf::Vector2f vertex2Left2 = bulletPosLeft + sf::Vector2f(-triangleHeight, triangleHeight);
					sf::Vector2f vertex3Left3 = bulletPosLeft + sf::Vector2f(triangleHeight, triangleHeight);
					sf::Vector2f bulletPosLine = vertex1Left1 + ((vertex3Left3 - vertex1Left1) * (static_cast<float>(j) / (totalLineBullets - 1)));
					bulletPosLine.y = startingYPos;
					line->SetPattenInfo(Shoot::NoramalPatten::ColumnType, bulletPosLine,  "BossNormalShooting1");
					if (sceneGame != nullptr)
					{
						sceneGame->AddGo(line);
					}
				}
			}
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num7))
	{
		std::string str = "BossNormalShooting1";
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);
		sf::Vector2f playerPosition = player->GetPosition();
		sf::Vector2f shootDirection = playerPosition - GetPosition();
		float angle = Utils::Angle(shootDirection.y, playerPosition.x);
		if (count >= 1)
		{
			if (count % 2 == 1)
				angle += Utils::DegreesToRadians(10.0f * (count / 2 + 1)); // 1 2 
			else if (count % 2 == 0)
				angle += Utils::DegreesToRadians(-10.0f * (count / 2)); // 1 2
		}
		shoot->SetPattenInfo(Shoot::NoramalPatten::SectorType, GetPosition(), angle, str);
		shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
		shoot->sortLayer = -1;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		std::cout << bossHp << std::endl;
	}
}

bool Boss::CheckCollisionWithBullet(const Shoot& bullet)
{
	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		bossHp--;
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
	// p0 현재 시작점
	// p1 거치는 지점 ?1
	// p2  거치는 지점 2
	// p3 도착지점
	// t 시간 ?
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
