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
	AnimationController animation;
	sf::Vector2f direction;
	bool moveBoss = false;
	float bossAttackTime = 0.8f;
	float speed = 300.f;
	ObjectPool<Shoot> bossShootPool;
	Player* player;
	sf::Vector2f WallBounds;
	float bgWidth;
	float bgHeight;

	int bossHp = 1000; //
	sf::Clock onePageCk;
	bool onePage = false;
	int rand1;
	int rand2 ;

	std::vector < NormalAttackInfo> attackInfo; // test º¯¼ö 
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
	void SetWallBounds(sf::Vector2f boundf, float widthX, float widthY);


	bool testShootBullet;
	void GetShootBulletTestCode(bool ty) { testShootBullet = ty; }

	bool testShootBullet2 = false;
	bool GetShootBullet2TestCode(){ return testShootBullet2; }
	void SetShootBullet2TestCode(bool type) { testShootBullet2 = type; }
	void SetPoolPos(sf::Vector2f pos) { poolShootPos = pos; }
	sf::Vector2f CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, float t);
private:
	ShootMGR shootPatternMgr;
};

