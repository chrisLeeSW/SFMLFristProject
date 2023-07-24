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
	playerBoomb = new SoundGo("Sounds/Boomb.wav");

	texid.loadFromFile("graphics/EffectSprite.png");
	effectBoomb.setTexture(texid);
	effectBoomb.setTextureRect({ 258,746,256,256 });
	effectBoomb.setScale(0.5f, 0.5f);
	Utils::SetOrigin(effectBoomb, Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
	playerShootPool.Release();
	if (playerShoot != nullptr) delete playerShoot;
	if (playerBoomb != nullptr) delete playerBoomb;
}

void Player::Reset()
{
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(-340.f, 260.f);
	hitboxCircle.setPosition(position);
	Utils::SetOrigin(hitboxCircle, Origins::MC);
	damage = 0.5f;
	invincibilityTime = 0.f;
	playerLife = 2;
	playerLifeDown = false;
	playerDie = false;
	effectDraw = false;
	effecTime = 0.f;
	timerBlink = 0.f;
	timerBlinkDuration = 0.3f;
}

void Player::Update(float dt)
{
	if (playerLifeDown)
	{
		invincibilityTime += dt;
		timerBlink += dt;
		if (timerBlink >= 0.f && timerBlink < timerBlinkDuration)
			sprite.setColor(sf::Color::Color(255, 255, 255, 150));
		else if (timerBlink > timerBlinkDuration && timerBlink < timerBlinkDuration * 2.f)
		{
			sprite.setColor(sf::Color::Color(255, 255, 255, 255));
			timerBlink = 0.f;
		}
	}
	if (invincibilityTime >= 10.f)
	{
		playerLifeDown = false;
		invincibilityTime = 0.f;
		timerBlink = 0.f;
		sprite.setColor(sf::Color::Color(255, 255, 255, 255));
	}
	
	if (playerLife == 0)
	{
		playerDie = true;
		return;
	}
	effectRoate += speed*dt;
	if(!playerDie)
	{
		PlayerMove(dt);
		PlayerShoot(dt);
		effectBoomb.setPosition(GetPosition());
		effectBoomb.setRotation(effectRoate);
		animation.Update(dt);
		SpriteGo::Update(dt);
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	
	SpriteGo::Draw(window);
	window.draw(hitboxCircle);
	if(effectDraw)window.draw(effectBoomb,sf::BlendAdd);
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
	if (effectDraw) effecTime += dt;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		autoShot = !autoShot;
	}
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if ((INPUT_MGR.GetKey(sf::Keyboard::X) || autoShot) && attackTime < 0.8f)
	{
		playerShoot->SoundPlay();
		playerShoot->sound.setVolume(5.f);
		attackTime = 1.0f;
		int count = 0;
		while (count < 3)
		{
			Shoot* shoot = playerShootPool.Get();
			std::string str = "Shooting"; 
			shoot->SetBoss(boss);
			sf::Vector2f dir = Utils::Normalize(boss->GetPosition()- GetPosition());
			if (count == 0)
				shoot->PlayerFire(GetPosition(), dir, str);
			else if (count == 1)
			{
				shoot->PlayerFire(GetPosition() + sf::Vector2f{ 20.f * count ,0.f * count }, dir, str);
			}
			else if (count == 2)
			{
				shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f * 0.5f *  count ,0.f * count }, dir, str);
			}
			else if (count>=3)
			{
				if (count % 2 == 1)
				{
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{20.f * (count/2+1) ,0.f * count }, dir, str);
				}
				else if (count % 2 == 0)
					shoot->PlayerFire(GetPosition()  + sf::Vector2f{ -20.f  * (count/2) ,0.f * count }, dir, str);
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
	if (INPUT_MGR.GetKey(sf::Keyboard::Tab) &&!effectDraw && sceneGame->GetBoombCountSpriteCurrent() >= 0)
	{
		playerBoomb->SoundPlay();
		effectDraw = true;
	}
	if (effecTime >= 8.f)
	{
		effecTime = 0.f;
		effectDraw = false;
		boss->SetUseBoomb(effectDraw);
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
		playerLifeDown = true;
		playerLife--;
		if (sceneGame != nullptr)
		{
			sceneGame->DecreasePlayerLife();
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

void Player::IncreaseDamage()
{
	damage += 0.5f;
}

void Player::IncreasePlayerLife()
{
	playerLife++;
}
