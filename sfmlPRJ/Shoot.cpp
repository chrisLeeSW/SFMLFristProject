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
}

void Shoot::Release()
{
	SpriteGo::Release();
}

void Shoot::Reset()
{
	animation.Play("Shooting");
	checkFireType = false;
	delayOnAttackType = false;
	SpriteGo::Reset();
}

void Shoot::Update(float dt)
{
	accuTime += dt;
	if (type == CharceterType::Player)
	{
		PlayerFire(dt);
	}
	else if (type == CharceterType::Boss)
	{
		BossFire(dt);
	}
	if (patternInfo.pattenType == NoramalPatten::TornadoTypeLoof && accuTime > 1.0f)
	{
		float angleOffset = 30.0f; 

		float radian = Utils::DegreesToRadians(angleOffset);
		float newX = direction.x * std::cos(radian) - direction.y * std::sin(radian);
		float newY = direction.x * std::sin(radian) + direction.y * std::cos(radian);
		direction = sf::Vector2f(newX, newY);
		accuTime = 0.f;
	}
	if (patternInfo.pattenType == NoramalPatten::DelayTimeAttackOneType && accuTime > 0.5f && !delayOnAttackType && !delayOnAttackingOne)
	{
		direction = { 0.f, 0.f };
		accuTime = 0.f;
		delayOnAttackType = true;
	}
	else if (patternInfo.pattenType == NoramalPatten::DelayTimeAttackTwoType && accuTime > 0.5f && !delayOnAttackType && !delayOnAttackingOne)
	{
		direction = { 0.f, 0.f };
		accuTime = 0.f;
		delayOnAttackType = true;
	}
	else if (patternInfo.delayTime <= accuTime && delayOnAttackType)
	{
		direction = Utils::Normalize(player->GetPosition() - GetPosition());
		accuTime = 0.f;
		delayOnAttackType = false;
		delayOnAttackingOne = true;
	}
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
	if (player->GetPlayerDie()) pool->Clear();
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
			SetAngleDirection();
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
		case NoramalPatten::DelayTimeAttackOneType:
		{
			SetPosition(patternInfo.pos);
			SetAngleDirection();
			animation.Play(patternInfo.animationClipId);
		}
		break; case NoramalPatten::DelayTimeAttackTwoType:
		{
			SetPosition(patternInfo.pos);
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::DelayType:
		{
			SetPosition(patternInfo.pos);
			SetAngleDirection();
			animation.Play(patternInfo.animationClipId);
		}
		break;
		case NoramalPatten::TornadoTypeLoof:
		{
			SetPosition(patternInfo.pos);
			SetAngleDirection();
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

void Shoot::PlayerFire(sf::Vector2f pos, sf::Vector2f dir,std::string clipId)
{

	type = CharceterType::Player;
	SetPosition(pos);
	direction = dir;
	animation.Play(clipId);
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


void Shoot::SetPlayer(Player* player)
{
	this->player = player;
}

void Shoot::SetBoss(Boss* boss)
{
	this->boss = boss;
}

void Shoot::SetWallBounds(sf::Vector2f boundf, float widthX, float heightY)
{
	bgWidth = widthX;
	bgHeight = heightY;
	WallBounds = boundf;
}

void Shoot::SetAngleDirection()
{
	float radian = Utils::DegreesToRadians(patternInfo.angle);
	direction = sf::Vector2f(std::cos(radian), std::sin(radian));
}
