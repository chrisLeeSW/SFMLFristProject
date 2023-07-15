#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include "Shoot.h"

#include "ShootMGR.h"
class Player;
class Boss :public SpriteGo
{
public:
	struct NormalAttackInfo
	{
		std::string animationClipId;
		int bulletCount;
		float maxSpeed;
	};
protected:
	sf::RectangleShape hitboxShape;
	bool hitboxDraw = false;
	AnimationController animation;
	sf::Vector2f direction;
	float speed = 100.f;
	bool moveBoss = false;
	bool filpX = false;

	ObjectPool<Shoot> bossShootPool;

	sf::Clock clock;
	float timer;

	Player* player;

	float testTime = 0.8f;

	std::vector < NormalAttackInfo> attackInfo;

public:
	Boss(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId, n) {}
	virtual ~Boss() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void BossMove(float dt);

	void SetPlayer(Player* player){ this->player = player; }
	bool CheckCollisionWithBullet(const Shoot& bullet);
private:
	ShootMGR shootPatternMgr;
};

