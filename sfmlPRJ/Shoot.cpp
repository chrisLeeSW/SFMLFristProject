#include "stdafx.h"
#include "Shoot.h"
#include "Player.h"
#include "Boss.h"

#include "Scene.h"
#include "SceneGame.h"

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
	checkFireType = false;
	delayOnAttackOneType = false;
	isUniqueAttack = false;
	SpriteGo::Reset();
}

void Shoot::Update(float dt)
{
	accuTime += dt;
	if (type == CharceterType::Player)
	{
		PlayerFire(dt);
	}
	if (type == CharceterType::Boss)
	{
		BossFire(dt);
	}
	if (uniqueType == UniqueType::TornadoType && position.y >= 0.f)
	{
		isUniqueAttack = true;
		boss->GetShootBulletTestCode(isUniqueAttack);
		boss->SetPoolPos(position);
	}
	if (isUniqueAttack)	
	{
		isUniqueAttack = !isUniqueAttack;
		uniqueType = UniqueType::None;
		pool->Return(this);
	}

	if (patternInfo.pattenType == NoramalPatten::testcode  &&!testing2)
	{
		direction = { 0.f,0.f };
		testing2 = true;
	}
	if (patternInfo.pattenType == NoramalPatten::testcode && accuTime > 0.5f && !testing3)
	{
		
		direction = sf::Vector2f(std::cos(patternInfo.angle), std::sin(patternInfo.angle));
		testing3 = true;

	}



	if (patternInfo.pattenType == NoramalPatten::DelayTimeAttackOneType && accuTime > 0.5f && !delayOnAttackOneType && !delayOnAttackingOne)
	{
		direction = { 0.f, 0.f };
		accuTime = 0.f;
		delayOnAttackOneType = true;

	}
	else if (patternInfo.delayTime <= accuTime && delayOnAttackOneType)
	{
		direction = Utils::Normalize(player->GetPosition() - GetPosition());
		accuTime = 0.f;
		delayOnAttackOneType = false;
		delayOnAttackingOne = true;
	}
	/*if (patternInfo.pattenType == NoramalPatten::testcode3 && accuTime > 0.5f && !delayOnAttackOneType)
	{
		direction = { 0.f,0.f };

		accuTime = 0.f;
		delayOnAttackOneType = true;
	}
	if (patternInfo.pattenType == NoramalPatten::testcode3 && delayOnAttackOneType && accuTime > 3.0f &&!testing2)
	{
		direction = Utils::Normalize(player->GetPosition() - GetPosition());
		testing2 = true;
	}*/

	if (patternInfo.pattenType == NoramalPatten::FrequencyType )
	{
		position.x = patternInfo.pos.x + std::sin(accuTime * patternInfo.frequency) * patternInfo.amplitude;
		position.y += direction.y * patternInfo.speed * dt;
	}

	else
	{
		position += direction * patternInfo.speed * dt;
	}




	sprite.setPosition(position);
	animation.Update(dt);

	if (position.y - sprite.getGlobalBounds().height * 0.5f < WallBounds.y - sprite.getGlobalBounds().height * 0.5)
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}
	else if (position.y + sprite.getGlobalBounds().height * 0.5f > WallBounds.y + bgHeight)
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}
	else if (position.x - sprite.getGlobalBounds().width * 0.5f < WallBounds.x - 20.f)
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}
	else if (position.x + sprite.getGlobalBounds().width * 0.5f > WallBounds.x + bgWidth + 20.f)
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}

	/*if (INPUT_MGR.GetKey(sf::Keyboard::Tab))
	{
		pool->Clear();
	}*/
	SpriteGo::Update(dt);
}

void Shoot::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Shoot::BossFire(float dt)
{
	if (!checkFireType)
	{
		switch (patternInfo.pattenType)
		{
		case NoramalPatten::SectorType:
		{
			SetPosition(patternInfo.pos);
			direction = sf::Vector2f(std::cos(patternInfo.angle), std::sin(patternInfo.angle));
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::AngleDirectionType:
		{
			SetPosition(patternInfo.pos);
			float radian = Utils::DegreesToRadians(patternInfo.angle);
			direction = sf::Vector2f(std::cos(radian), std::sin(radian));
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::FrequencyType:
		{
			SetPosition(patternInfo.pos);
			direction = { 1.f,0.1f };
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::ColumnType:
		{
			SetPosition(patternInfo.pos);
			direction = { 0.f,1.f };
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::RowRightType:
		{
			SetPosition(patternInfo.pos);
			direction = { 1.f,0.f };
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::RowLeftType:
		{
			SetPosition(patternInfo.pos);
			direction = { -1.f,0.f };
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::testcode:
		{
			SetPosition(patternInfo.pos);
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::DelayTimeAttackOneType:
		{
			SetPosition(patternInfo.pos);
			float radian = Utils::DegreesToRadians(patternInfo.angle);
			direction = sf::Vector2f(std::cos(radian), std::sin(radian));
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::testcode3:
		{
			SetPosition(patternInfo.pos);
			float radian = Utils::DegreesToRadians(patternInfo.angle);
			direction = sf::Vector2f(std::cos(radian), std::sin(radian));
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::DelayType:
		{
			SetPosition(patternInfo.pos);
			float radian = Utils::DegreesToRadians(patternInfo.angle);
			direction = sf::Vector2f(std::cos(radian), std::sin(radian));
			animation.Play(patternInfo.animationClipId);
		}
		break;
		}
		checkFireType = true;
	}
	if (player->CheckCollisionWithBullet(*this))
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}
}

void Shoot::PlayerFire(float dt)
{
	if (boss->CheckCollisionWithBullet(*this))
	{
		pool->Return(this);
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}

}

void Shoot::PlayerFire(sf::Vector2f pos, sf::Vector2f dir)
{

	type = CharceterType::Player;
	SetPosition(pos);
	//direction = sf::Vector2f{ 0.f,-1.f };
	direction = dir;
	animation.Play(animationId);

}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float speed)
{
	type = CharceterType::Boss;
	patternInfo.pattenType = pattenType;
	patternInfo.pos = pos;
	patternInfo.angle = angle;
	patternInfo.animationClipId = clipId;
	patternInfo.speed = speed;
}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float freq, float ampl, float speed)
{
	type = CharceterType::Boss;
	patternInfo.pattenType = pattenType;
	patternInfo.pos = pos;
	patternInfo.angle = angle;
	patternInfo.animationClipId = clipId;
	patternInfo.frequency = freq;
	patternInfo.amplitude = ampl;
	patternInfo.speed = speed;
}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, std::string clipId, float speed)
{
	type = CharceterType::Boss;
	patternInfo.pattenType = pattenType;
	patternInfo.pos = pos;
	patternInfo.animationClipId = clipId;
	patternInfo.speed = speed;
}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, sf::Vector2f dir, std::string clipId)
{
	type = CharceterType::Boss;
	patternInfo.pattenType = pattenType;
	patternInfo.pos = pos;
	direction = dir;
	patternInfo.animationClipId = clipId;
}

void Shoot::SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos,  std::string clipId, float angle, float delay, float speed)
{
	type = CharceterType::Boss;
	patternInfo.pattenType = pattenType;
	patternInfo.pos = pos;
	patternInfo.angle = angle;
	patternInfo.animationClipId = clipId;
	patternInfo.speed = speed;
	patternInfo.delayTime = delay;
}



/*

	if (patternInfo.pattenType == NoramalPatten::FrequencyType)
	{
		position.y = position.y + std::sin(accuTime * patternInfo.frequency) * patternInfo.amplitude;
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

void Shoot::SetWallBounds(sf::Vector2f boundf, float widthX, float heightY)
{
	bgWidth = widthX;
	bgHeight = heightY;
	WallBounds = boundf;
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
			shoot->delayOnAttackOneType = true;

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

/*
* case NoramalPatten::FrequencyType:
		{
			SetPosition(patternInfo.pos);
			direction = sf::Vector2f(std::cos(patternInfo.angle), std::sin(patternInfo.angle));
			animation.Play(patternInfo.animationClipId);
		}
		break;

if (patternInfo.pattenType == NoramalPatten::FrequencyType)
	{
		position.x += direction.x * speed * dt;
		position.y = patternInfo.pos.y + std::sin(accuTime * patternInfo.frequency) * patternInfo.amplitude; // ���ļ� ����
	}
	���ڸ� �������ϴ� �ڵ� �߻� -> ;;�ð��� �༭ ���ָ鼭 ��ġ ���� ���� �ָ� ��� �����غ���

	shoopattern ��
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	int shootCount = 1;
	float minFrequency = 2.f;  // �ּ� ���ļ�
	float maxFrequency = 50.f;  // �ִ� ���ļ�
	float amplitude = 1000.0f;   // ����

	for (int count = 0; count < shootCount; ++count)
	{
		Shoot* shoot = bossShootPool.Get();
		shoot->SetPlayer(player);

		sf::Vector2f playerPosition = player->GetPosition();
		sf::Vector2f shootDirection = playerPosition - boss->GetPosition();
		float angle = Utils::Angle(shootDirection.y, playerPosition.x);
		float frequency = minFrequency + static_cast<float>(count) / shootCount * (maxFrequency - minFrequency);
		// ���ļ��� �����Ͽ� ������ ��ȭ�� ��
		angle += std::sin(frequency * count) * amplitude;

		shoot->SetPattenInfo(Shoot::NoramalPatten::FrequencyType, boss->GetPosition(), angle, "BossNormalShooting1", minFrequency, maxFrequency);
		shoot->sortLayer = -1;

		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}


*/