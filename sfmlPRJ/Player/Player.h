#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Shoot.h"

class Boss;
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
	
	ObjectPool<Shoot> playerShootPool;
	float attackTime = 0.8f;
	bool autoShot = false;

	Boss* boss;
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
};

