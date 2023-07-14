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

	hitboxShape.setSize({ 32.f, 32.f });
	hitboxShape.setFillColor(sf::Color::Color(255, 255, 255, 0));
	Utils::SetOrigin(hitboxShape, Origins::MC);

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
	SetPosition(0.f, -260.f);
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
	window.draw(hitboxShape);
}

void Boss::BossMove(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::O))
	{
		direction.y =1.f;
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::O))
	{
		direction.y = 0.f;
	}
	testTime -= dt;
	position += direction * speed * dt;
	hitboxShape.setPosition(position);
	SetPosition(position);

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad0) && testTime < 0.8f)
	{
		testTime = 1.0f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int shootCount = 5;
		for (int count = 0;count < shootCount;++count)
		{
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
			shoot->BossNormalFire(position, angle,"BossNormalShooting1");
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad1) && testTime < 0.8f)
	{
		testTime = 1.0f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int shootCount = 6;
		float pattenAngle = 360.f / shootCount;
		for (int count = 0; count < shootCount; ++count)
		{
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);

			float additionalAngle = pattenAngle * count;
			shoot->BossNormalFirePatten1(position, additionalAngle,"BossNormalShooting2");
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
	{
		testTime = 1.0f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		const int bulletCount = 10;  // �Ѿ� ����

		// ���� �Ѿ��� ��ġ�� �ʱ�ȭ
		sf::Vector2f previousPosition = GetPosition();

		// �Ѿ� ���� �� �ʱ�ȭ
		for (int i = 0; i < bulletCount; ++i)
		{
			Shoot* bullet = bossShootPool.Get();
			bullet->SetPlayer(player);

			// �Ѿ��� ���� ��ġ ���
			float startDistance = 20.f;  // ���� ��ġ���� �Ÿ�
			float distanceInterval = 10.f;  // �Ѿ� ���� �Ÿ� ����
			sf::Vector2f startPosition = previousPosition - sf::Vector2f(startDistance * i, distanceInterval * i);
			bullet->SetPosition(startPosition);

			// �Ѿ��� �̵� ���� ���
			float bulletAngle = Utils::DegreesToRadians(90.f);  // �Ѿ��� �⺻ �̵� ���� (����)
			float angleRange = 30.f;  // �Ѿ��� ���� ����
			float angleOffset = angleRange * i / (bulletCount - 1) - angleRange * 0.5f;  // �Ѿ��� ���� ������
			bulletAngle += Utils::DegreesToRadians(angleOffset);
			sf::Vector2f bulletDirection = sf::Vector2f(std::cos(bulletAngle), std::sin(bulletAngle));
			bullet->testFire(startPosition, bulletDirection, 90);

			// �Ѿ��� ���ӿ� �߰�
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(bullet);
			}

			previousPosition = startPosition; // ���� �Ѿ��� ���� ��ġ�� ���� �Ѿ��� ��ġ�� ����
		}
	}



	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0) && !hitboxDraw)
	{
		hitboxShape.setFillColor(sf::Color::Color(255, 255, 255, 0));
		hitboxDraw = false;
	}
	else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0) && hitboxDraw)
	{
		hitboxShape.setFillColor(sf::Color::Yellow);
		hitboxDraw = true;
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

// ��� ź�� -> ������ ����̵��������� 1���� �����̸� �𸣰��� 
//if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
//{
//	testTime = 1.0f;
//	Scene* scene = SCENE_MGR.GetCurrScene();
//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
//	const int bulletCount = 3;  // �Ѿ� ����
//	const float tornadoRadius = 100.f;  // ����̵��� ������
//	const float rotationSpeed = 120.f;  // ȸ�� �ӵ� (����/��)
//
//	float startAngle = -90.f;  // ���� ���� (12�� ����)
//	float angleStep = 360.f / bulletCount;  // ���� �ܰ�
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


//����: ����� ���� ź��
	//if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
	//{
	//	testTime = 1.0f;
	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	//	const int bulletCount = 12;  // �Ѿ� ����
	//	const float radius = 100.f;  // ���� ������
	//	const float angleStep = 360.f / bulletCount;  // ���� �ܰ�

	//	for (int i = 0; i < bulletCount; ++i)
	//	{
	//		float angle = angleStep * i;
	//		float radian = Utils::DegreesToRadians(angle);
	//		sf::Vector2f offset = sf::Vector2f(std::cos(radian), std::sin(radian)) * radius;

	//		// �Ѿ� ���� �� ����
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