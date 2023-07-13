#include "stdafx.h"
#include "Shoot.h"

void Shoot::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip(fileNames));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);

	SpriteGo::Init();
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
		position += direction*speed * dt;

		if (position.y <= -600.f)
		{
			pool->Return(this);
		}
	}
	else if (type == CharceterType::Boss)
	{
		position += direction * speed * dt;
		if (position.y >= 600.f)
		{
			pool->Return(this);
		}
	}
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
	position = pos;
	direction = sf::Vector2f{ 0.f,-1.f };
	std::cout << position.x << std::endl;
	sprite.setScale(0.5f, 0.5f);
	animation.Play("Shooting");
}

void Shoot::BossFire(sf::Vector2f pos)
{
	type = CharceterType::Boss;
	position = pos;
	direction = sf::Vector2f{ 0.f,1.f };
}

void Shoot::SetFileName(std::string n)
{
	fileNames = n;
}
