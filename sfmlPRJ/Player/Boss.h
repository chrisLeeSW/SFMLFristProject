#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include "Shoot.h"
#include "ShootMGR.h"
#include "UniqueShootMGR.h";
class Player;
class Boss :public SpriteGo
{
public:
	struct NormalAttackInfo
	{
		std::string animationClipId;
		int bulletCount;
		float maxSpeed;
	}; //  지울수도 있음
protected:

	AnimationController animation;
	sf::Vector2f direction;
	bool moveBoss = false;
	float speed = 300.f;
	ObjectPool<Shoot> bossShootPool ;
	Player* player;
	sf::Vector2f WallBounds;
	float bgWidth=0.f;
	float bgHeight=0.f;
	float bossHp = 810.f; //
	float startGame = 0.f;
	


	


	std::vector < NormalAttackInfo> attackInfo; // test 변수 
	//
	float bossAtk = 0.05f;
	float delay = 0.05f;
	int count;
	int maxCount = 30;
	int maxCount2 = 3;
	sf::Vector2f poolShootPos;
	//
public:
	Boss(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId, n){}
	virtual ~Boss() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void BossMove(float dt);
	void BossFireUcnique(float dt);
	void BossFireNormal(float dt);
	void SetPlayer(Player* player) { this->player = player; }
	bool CheckCollisionWithBullet(const Shoot& bullet);
	void SetWallBounds(sf::Vector2f boundf, float widthX, float widthY);


	bool testShootBullet;
	void GetShootBulletTestCode(bool ty) { testShootBullet = ty; }

	void SetPoolPos(sf::Vector2f pos) { poolShootPos = pos; }
	sf::Vector2f CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p3, float t);
	float GetBossHp() { return bossHp; }
	bool GetBossDie(){ return bossDie; }
private:
	ShootMGR shootPatternMgr;
	UniqueShootMGR uniqueshootPatternMgr;


	sf::Vector2f endPos;
	sf::Vector2f startPos;
	sf::Vector2f secondPos;
	float stopAttackTime;
	float stopAttackTimeLimit = 2.0f;
	bool stopBoss;
	float moveTimerDuration;
	float moveTime;
	float moveDuration = 3.f; 
	float stopLimit = 5.f;

	int attackRand1 =-1;
	float bossAttackTimeOne =0.f;
	float bossAttackTimeOneLimit = 1.0f;
	float bossAttackNoramalPatternChangeTimeLimit = 20.f;
	float bossAttackNoramalPatternChangeTime =0.f;

	bool bossDie = false;
};

