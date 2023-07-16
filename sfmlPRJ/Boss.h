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
	float speed = 300.f;
	bool moveBoss = false;
	bool filpX = false;
	ObjectPool<Shoot> bossShootPool;
	Player* player;


	sf::Clock clock;
	float timer;


	float bossAttackTime = 0.8f;

	std::vector < NormalAttackInfo> attackInfo;
	//
	float bossAtk=0.05f;
	float delay=0.05f;
	int count;
	int maxCount = 30;
	sf::Vector2f poolShootPos;
	//
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

	bool testShootBullet;
	void GetShootBulletTestCode(bool ty) { testShootBullet = ty; }

	bool testShootBullet2 = false;
	bool GetShootBullet2TestCode(){ return testShootBullet2; }
	void SetShootBullet2TestCode(bool type) { testShootBullet2 = type; }
	void SetPoolPos(sf::Vector2f pos) { poolShootPos = pos; }
private:
	ShootMGR shootPatternMgr;
};

