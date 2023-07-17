#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

#include "Boss.h"
void Player::Init()
{

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Idel.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Move.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);

	playerShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetPlayer(this);
		bullet->pool = &playerShootPool;
	};
	playerShootPool.Init();
	hitboxCircle.setRadius(2.5f);
	hitboxCircle.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(hitboxCircle, Origins::MC);
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
	SetPosition(-340.f, 260.f);
	hitboxCircle.setPosition(position);
	Utils::SetOrigin(hitboxCircle, Origins::MC);
}

void Player::Update(float dt)
{
	PlayerMove(dt);
	PlayerShoot(dt);
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(hitboxCircle);
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
		speed = 50.f;
	}
	else
	{
		speed = 150.f;
	}
	position += direction * speed * dt;
	hitboxCircle.setPosition(position);
	SetPosition(position);



	if (direction.x != 0.f && !movePlayer)
	{
		if (!movePlayer)
		{
			animation.Play("Move");
			movePlayer = true;
		}
	}
	ChangeFlip(direction.x);
	if (direction.x == 0.f && movePlayer)
	{
		animation.Play("Idle");
		movePlayer = false;
	}

	if (GetPosition().x - sprite.getGlobalBounds().width *0.5f < WallBounds.x)
	{
		SetPosition(WallBounds.x + bgWidth  - sprite.getGlobalBounds().width* 0.5f,GetPosition().y);
	}
	if (GetPosition().x + sprite.getGlobalBounds().width * 0.5f > WallBounds.x + bgWidth)
	{
		SetPosition(WallBounds.x + sprite.getGlobalBounds().width * 0.5f, GetPosition().y);
	}
	if (GetPosition().y + sprite.getGlobalBounds().height * 0.5f > WallBounds.y + bgHeight)
	{
		SetPosition(GetPosition().x, WallBounds.y + sprite.getGlobalBounds().height * 0.5f);
	}
	if (GetPosition().y - sprite.getGlobalBounds().height * 0.5f < WallBounds.y)
	{
		SetPosition(GetPosition().x, WallBounds.y + bgHeight - sprite.getGlobalBounds().height * 0.5f);
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
			std::string str = "Shooting"; //
			shoot->SetAnimationId(str); //
			shoot->SetBoss(boss);
			if (count == 0)
				shoot->PlayerFire(GetPosition() );
			else if (count == 1)
			{
				shoot->PlayerFire(GetPosition() + sf::Vector2f{ 20.f * count ,0.f * count });
			}
			else if (count == 2)
			{
				shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f * 0.5f *  count ,0.f * count });
			}
			else if (count>=3)
			{
				if (count % 2 == 1)
				{
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{20.f * (count/2+1) ,0.f * count });
				}
				else if (count % 2 == 0)
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f  * (count/2) ,0.f * count });
			}
			shoot->sortLayer = -1;
			shoot->SetWallBounds(WallBounds, bgWidth, bgHeight);
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
			count++;
		}
	}


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1) && hitboxDraw)
	{
		hitboxCircle.setFillColor(sf::Color::Color(255, 255, 255, 0));
		hitboxDraw = false;
	}
	else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1) && !hitboxDraw)
	{
		hitboxCircle.setFillColor(sf::Color::Yellow);
		hitboxDraw = true;
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

bool Player::CheckCollisionWithBullet(const Shoot& bullet)
{
	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		
		if (hitboxCircle.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
		{
			std::cout << "isCollied Player" << std::endl;
			return true;
		}
	}
	return false;
}

void Player::SetWallBounds(sf::Vector2f boundf,float widthX , float widthY)
{	
	bgWidth = widthX;
	bgHeight = widthY;
	WallBounds = boundf;
}
