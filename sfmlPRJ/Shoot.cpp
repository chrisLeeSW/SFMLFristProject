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
	SpriteGo::Reset();
}

void Shoot::Update(float dt)
{
	if (type == CharceterType::Player)
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
	}
	if (type == CharceterType::Boss)
	{
		
	
		if (position.y >= 600.f)
		{
			pool->Return(this);
		}
		if (player->CheckCollisionWithBullet(*this))
		{
			pool->Return(this);
		}
	}
	position += direction * speed * dt;
	position += velocity *dt;
	sprite.setPosition(position);
	animation.Update(dt);

	SpriteGo::Update(dt);
}

void Shoot::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Shoot::PlayerFire(sf::Vector2f pos)
{

	type = CharceterType::Player;
	SetPosition(pos);
	direction = sf::Vector2f{ 0.f,-1.f };
	animation.Play(animationId);

}

void Shoot::BossNormalFire(sf::Vector2f pos, float angle,std::string clipName)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	direction = sf::Vector2f(std::cos(angle),std::sin(angle));
	animation.Play(clipName);
}

void Shoot::SetAnimationId(const std::string& n)
{
	animationId = n;
}

void Shoot::BossNormalFirePatten1(sf::Vector2f pos, float angle, std::string clipName)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	float radian = Utils::DegreesToRadians(angle);
	direction = sf::Vector2f(std::cos(radian), std::sin(radian));
	animation.Play(clipName);
}

void Shoot::testFire(sf::Vector2f pos, sf::Vector2f dir,float angle)
{
	type = CharceterType::Boss;
	SetPosition(pos);
	float radian = Utils::DegreesToRadians(angle);
	direction = sf::Vector2f(std::cos(radian), std::sin(radian));
	velocity = dir;
	//animation.Play(clipName);
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
