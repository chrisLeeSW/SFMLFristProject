#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Shoot.h"

class Boss;
class SoundGo;
class Player :public SpriteGo
{

protected:
	sf::CircleShape hitboxCircle;
	bool hitboxDraw = true;
	std::vector<std::string> animationId;
	AnimationController animation;
	sf::Vector2f direction;
	float speed = 500.f;
	bool movePlayer = false;
	bool filpX = false;
	float damage = 0.5f;

	ObjectPool<Shoot> playerShootPool;
	float attackTime = 0.8f;
	bool autoShot = false;
	Boss* boss;

	sf::Vector2f WallBounds;
	float bgWidth;
	float bgHeight;

	SoundGo* playerShoot;
	SoundGo* playerBoomb;

	int playerLife = 2;
	bool playerLifeDown = false;
	float invincibilityTime=0;
	bool playerDie = false;

	sf::Sprite effectBoomb;
	sf::Texture texid;
	float effectRoate = 0.f;
	float effecTime = 0.f;
	bool effectDraw = false;
	float timerBlink=0.f;
	float timerBlinkDuration = 0.3f;

	
public:
	Player(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerMove(float dt);
	void PlayerShoot(float dt);
	void ChangeFlip(float x);

	void SetBoss(Boss* boss) { this->boss = boss; }
	bool CheckCollisionWithBullet(const Shoot& bullet);
	
	void SetWallBounds(sf::Vector2f boundf, float widthX, float widthY);
	float GetPlayerDamage() { return damage; }
	bool GetPlayerDie() { return playerDie; }
	void SetPlayerDie(bool tp) { playerDie = tp; }
	bool GetEffectDraw() { return effectDraw; }
	float GetDamage() { return damage; }
	void IncreaseDamage();
	void IncreasePlayerLife();
	int GetPlayerLife() { return playerLife; }

};

