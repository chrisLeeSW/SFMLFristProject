#include "stdafx.h"
#include "Shoot.h"
#include "Player.h"
#include "Boss.h"
void Shoot::Init()
{

	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Shooting.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/BossNormalShooting1.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/BossNormalShooting2.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	//SetOrigin(Origins::MC);
}

void Shoot::Release()
{
	SpriteGo::Release();
}

void Shoot::Reset()
{
	animation.Play("Shooting");
	testCode = false;
	SpriteGo::Reset();
}

void Shoot::Update(float dt)
{
	accuTime += dt;
	if (type == CharceterType::Player)
	{
		PlayerFire(dt);
		/*if (position.y <= -600.f)
		{
			pool->Return(this);
			std::cout << "Realse" << std::endl;
		}
		if (boss->CheckCollisionWithBullet(*this))
		{
			pool->Return(this);
		}*/
	}
	if (type == CharceterType::Boss)
	{
		/*if (position.y >= 600.f)
		{
			pool->Return(this);
		}
		if (player->CheckCollisionWithBullet(*this))
		{
			pool->Return(this);
		}*/
		BossFire(dt);
	}
	//velocity += acceleration * dt;



	if (pattenInfo.pattenType == NoramalPatten::FrequencyType)
	{
		position.x += direction.x * speed * dt; // x������ ����
		position.y = pattenInfo.pos.y + std::sin(accuTime * pattenInfo.frequency) * pattenInfo.amplitude; // ���ļ� ����
	}
	else
	{
		position += direction * speed * dt;
		position += velocity * dt;
	}
	sprite.setPosition(position);
	animation.Update(dt);

	SpriteGo::Update(dt);
}

void Shoot::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Shoot::BossFire(float dt)
{
	if (!testCode)
	{
		switch (pattenInfo.pattenType)
		{
		case NoramalPatten::SectorType:
		{
			SetPosition(pattenInfo.pos);
			direction = sf::Vector2f(std::cos(pattenInfo.angle), std::sin(pattenInfo.angle));
			animation.Play(pattenInfo.animationClipId);
		}
		break;
		case NoramalPatten::AngleDirectionType:
		{
			SetPosition(pattenInfo.pos);
			float radian = Utils::DegreesToRadians(pattenInfo.angle);
			direction = sf::Vector2f(std::cos(radian), std::sin(radian));
			animation.Play(pattenInfo.animationClipId);
		}
		break;
		case NoramalPatten::FrequencyType:
		{
			SetPosition(pattenInfo.pos);
			direction = sf::Vector2f(std::cos(pattenInfo.angle), std::sin(pattenInfo.angle));
			animation.Play(pattenInfo.animationClipId);
		}
		break;
		}
		testCode = true;
	}

	if (position.y >= 600.f)
	{
		pool->Return(this);
	}
	if (player->CheckCollisionWithBullet(*this))
	{
		pool->Return(this);
	}
}

void Shoot::PlayerFire(float dt)
{
	if (position.y <= -600.f)
	{
		pool->Return(this);
		std::cout << "Realse" << std::endl;
	}
	if (boss->CheckCollisionWithBullet(*this))
	{
		pool->Return(this);
	}
	//position += direction * speed * dt;
}

void Shoot::PlayerFire(sf::Vector2f pos)
{

	type = CharceterType::Player;
	SetPosition(pos);
	direction = sf::Vector2f{ 0.f,-1.f };
	animation.Play(animationId);

}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId)
{
	type = CharceterType::Boss;
	pattenInfo.pattenType = pattenType;
	pattenInfo.pos = pos;
	pattenInfo.angle = angle;
	pattenInfo.animationClipId = clipId;
}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float freq, float ampl)
{
	type = CharceterType::Boss;
	pattenInfo.pattenType = pattenType;
	pattenInfo.pos = pos;
	pattenInfo.angle = angle;
	pattenInfo.animationClipId = clipId;
	pattenInfo.frequency = freq;
	pattenInfo.amplitude = ampl;
}

/*

	if (pattenInfo.pattenType == NoramalPatten::FrequencyType)
	{
		position.y = position.y + std::sin(accuTime * pattenInfo.frequency) * pattenInfo.amplitude;
	}

*/




void Shoot::BossNormalFire(sf::Vector2f pos, float angle, std::string clipName)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	direction = sf::Vector2f(std::cos(angle), std::sin(angle));
	animation.Play(clipName);
}



void Shoot::BossNormalFirePatten1(sf::Vector2f pos, float angle, std::string clipName)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	float radian = Utils::DegreesToRadians(angle);
	direction = sf::Vector2f(std::cos(radian), std::sin(radian));
	animation.Play(clipName);
}



void Shoot::testFire(sf::Vector2f pos, float frequency, float amplitude, std::string clipName)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	direction = { 0.f,1.0f };
	this->frequency = frequency;
	this->amplitude = amplitude;
	animation.Play(clipName);
}


void Shoot::SetAnimationId(const std::string& n)
{
	animationId = n;
}

void Shoot::SetPlayer(Player* player)
{
	this->player = player;
}

void Shoot::SetBoss(Boss* boss)
{
	this->boss = boss;
}

void Shoot::SetDirection(sf::Vector2f dir)
{
	direction = dir;
}


void Shoot::frequencyMovement(float dt)
{
	// ���ļ� �����ӿ� �ʿ��� ������ �����մϴ�.
	float frequency = 2.0f;  // ���ļ� (�ֱ�� ���� Ƚ��)
	float amplitude = 50.0f; // ���� (������ ũ��)
	float timeFactor = 2.0f; // �ð��� ���� ��� (������ ������)

	// ���ļ� �������� ����մϴ�.
	float angle = timeFactor * 2 * M_PI * frequency * accumulatedTime;
	float yOffset = amplitude * sin(angle);

	// �Ѿ��� ��ġ�� ���ļ� �������� �����մϴ�.
	position.y += yOffset;

	// �Ѿ��� ���� �ð��� ������Ʈ�մϴ�.
	accumulatedTime += dt;
}
/*

if (INPUT_MGR.GetKey(sf::Keyboard::Numpad2) && testTime < 0.8f)
	{
		int shootCount = 6;
		float patternAngle = 360.f / shootCount;
		for (int count = 0; count < shootCount; ++count)
		{
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);

			float additionalAngle = patternAngle * count;
			shoot->BossNormalFirePatten1(position, additionalAngle, "BossNormalShooting2");
			shoot->sortLayer = -1;

			// ���ļ� �������� �����մϴ�.
			shoot->test = true;

			Scene* scene = SCENE_MGR.GetCurrScene();
			SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}

*/

/*
sf::Vector2f acceleration(0.f, -100.f); // ���Ϸ� ������ ���ӵ�

// �Ѿ��� ���� ���̿� �����ϸ� ���ӵ��� 0 �Ǵ� ������ �����Ͽ� ����
if (position.y < targetHeight)
{
	acceleration.y = 0.f; // �Ǵ� ���� ���� ����Ͽ� ����
}
sf::Vector2f acceleration(0.f, -100.f); // ���Ϸ� ������ ���ӵ�

// �Ѿ��� ���� ���̿� �����ϸ� ���ӵ��� 0 �Ǵ� ������ �����Ͽ� ����
if (position.y < targetHeight)
{
	acceleration.y = 0.f; // �Ǵ� ���� ���� ����Ͽ� ����
}
sf::Vector2f acceleration(0.f, 0.f); // �ʱ� ���ӵ� 0

// ���ǿ� ���� ���ӵ� ����
if (someCondition)
{
	acceleration.x = 100.f; // ����
}
else
{
	acceleration.x = -50.f; // ���� �Ǵ� ������ ����
}


*/