#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
void Player::Init()
{

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Idel.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Move.csv"));
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Shooting.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

	playerShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetFileName("Animations/Player_Ani_Shooting.csv");
		bullet->pool = &playerShootPool;
	};
	playerShootPool.Init();

	//playerShootPool.OnCreate = [this](Shoot* bullet) {
	//	bullet->textureId = "graphics/TouhuoPlayerShoot.png";
	//	sf::IntRect rect = { 137,80,57,57 };
	//	bullet->sprite.setTextureRect(rect);
	//	bullet->pool = &playerShootPool;
	//};
	//playerShootPool.Init();

}

void Player::Release()
{
	SpriteGo::Release();
	playerShootPool.Release();
}

void Player::Reset()
{
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(0.f, 260.f);
}

void Player::Update(float dt)
{
	PlayerMove(dt);
	PlayerShoot(dt);
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Player::PlayerMove(float dt)
{
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::LShift) || INPUT_MGR.GetKey(sf::Keyboard::RShift))
	{
		speed = 250.f;
	}
	else
	{
		speed = 500.f;
	}
	position += direction * speed * dt;
	SetPosition(position);



	if (INPUT_MGR.GetAxisRaw(Axis::Horizontal))
	{
		movePlayer = true;
		animation.Play("Move");
	}
	ChangeFlip(direction.x);
	if (direction.x == 0.f && movePlayer)
	{
		animation.Play("Idle");
		movePlayer = false;
	}
}

void Player::PlayerShoot(float dt)
{
	attackTime -= dt;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		autoShot = !autoShot;
	}

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if ((INPUT_MGR.GetKey(sf::Keyboard::X) || autoShot) && attackTime < 0.8f)
	{
		attackTime = 1.0f;
		int count = 0;
		while (count < 5)
		{
			Shoot* shoot = playerShootPool.Get();
			if (count == 0)
				shoot->PlayerFire(GetPosition());
			else if (count == 1)
			{
				shoot->PlayerFire(GetPosition() + sf::Vector2f{ 20.f * count ,0.f * count });
			}
			else if (count == 2)
			{
				shoot->PlayerFire(GetPosition() + sf::Vector2f{ -20.f * 0.5f *  count ,0.f * count });
			}
			else if (count>=3)
			{
				if (count % 2 == 1)
				{
					shoot->PlayerFire(GetPosition() + sf::Vector2f{20.f * (count/2+1) ,0.f * count });
				}
				else if (count % 2 == 0)
					shoot->PlayerFire(GetPosition() + sf::Vector2f{ -20.f  * (count/2) ,0.f * count });
			}
			shoot->sortLayer = -1;
			std::cout << GetPosition().x << std::endl;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
			count++;
		}
	}
}

void Player::ChangeFlip(float x)
{
	sf::Vector2f scale = sprite.getScale();
	if (x > 0.f)
		scale.x = -abs(scale.x);
	else
		scale.x = abs(scale.x);
	sprite.setScale(scale);
}

