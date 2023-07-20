#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

#include "Boss.h"
#include "SoundGo.h"
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
	hitboxCircle.setRadius(1.5f);
	hitboxCircle.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(hitboxCircle, Origins::MC);

	playerShoot = new SoundGo("Sounds/playerTan.wav");
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
	soundVolum = 10.f;
	damage = 0.5f;
	invincibilityTime = 0.f;
	playerLife = 2;
	playerLifeDown = false;
	playerDie = false;
}

void Player::Update(float dt)
{
	if (playerLifeDown)
	{
		invincibilityTime += dt;
	}
	if (invincibilityTime >= 10.f)
	{
		playerLifeDown = false;
		invincibilityTime = 0.f;
	}
	//
	//if (playerLife == 0) playerLife = 500;
	//
	/*
	if (playerLife == 0)
	{
		playerDie = true;
	}
	*/
	if(!playerDie)
	{
		PlayerMove(dt);
		PlayerShoot(dt);
		SpriteGo::Update(dt);
		animation.Update(dt);
	}

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
		speed = 100.f;
	}
	else
	{
		speed = 500.f;
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
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		soundVolum += 5.f;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		soundVolum -= 5.f;
	}
	if ((INPUT_MGR.GetKey(sf::Keyboard::X) || autoShot) && attackTime < 0.8f)
	{
		playerShoot->SoundPlayer();
		playerShoot->sound.setVolume(soundVolum);
		attackTime = 1.0f;
		int count = 0;
		while (count < 3)
		{

			Shoot* shoot = playerShootPool.Get();
			std::string str = "Shooting"; 
			shoot->SetAnimationId(str); 
			shoot->SetBoss(boss);
			sf::Vector2f dir = Utils::Normalize(boss->GetPosition()- GetPosition());
			if (count == 0)
				shoot->PlayerFire(GetPosition(), dir);
			else if (count == 1)
			{
				shoot->PlayerFire(GetPosition() + sf::Vector2f{ 20.f * count ,0.f * count }, dir);
			}
			else if (count == 2)
			{
				shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f * 0.5f *  count ,0.f * count }, dir);
			}
			else if (count>=3)
			{
				if (count % 2 == 1)
				{
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{20.f * (count/2+1) ,0.f * count }, dir);
				}
				else if (count % 2 == 0)
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f  * (count/2) ,0.f * count }, dir);
			}
			shoot->sortLayer = 2;
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
	float playerRadius = hitboxCircle.getGlobalBounds().width;
	float bulletRadius = bullet.sprite.getGlobalBounds().width * 0.25f; 
	float distance = Utils::Distance(GetPosition(), bullet.sprite.getPosition());
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (distance < playerRadius + bulletRadius && !playerLifeDown )
	{
		std::cout << "isCollied Player" << std::endl;
		playerLifeDown = true;
		playerLife--;
		if (sceneGame != nullptr)
		{
			sceneGame->isCollied();
		}	
		return true;
	}
	return false;
}

void Player::SetWallBounds(sf::Vector2f boundf,float widthX , float widthY)
{	
	bgWidth = widthX;
	bgHeight = widthY;
	WallBounds = boundf;
}
