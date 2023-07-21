#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include "Shoot.h"
#include "ShootMGR.h"
#include "UniqueShootMGR.h"
class Player;
class Scene;
class SceneGame;
class Boss :public SpriteGo
{
protected:

	AnimationController animation;
	sf::Vector2f direction;
	bool moveBoss = false;
	float speed = 300.f;
	ObjectPool<Shoot> bossShootPool ;
	Player* player=nullptr;
	sf::Vector2f WallBounds;
	float bgWidth=0.f;
	float bgHeight=0.f;
	float bossHp = 810.f; //
	float startGame = 0.f;
	


	
	//
	float bossAtk = 0.05f;
	float delay = 0.05f;
	int count=0;
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
	int GetScore() { return score; }
	sf::Vector2f  RotateVector(const sf::Vector2f& vector, float angleDegrees);

	void SetUseBoomb(bool t) { useBoomb = t; }
private:
	ShootMGR shootPatternMgr;
	UniqueShootMGR uniqueshootPatternMgr;


	sf::Vector2f endPos;
	sf::Vector2f startPos;
	sf::Vector2f secondPos;
	float stopAttackTime=0.f;
	float stopAttackTimeLimit = 2.0f;
	bool stopBoss=false;
	float moveTimerDuration=0.f;
	float moveTime=0.f;
	float moveDuration = 3.f; 
	float stopLimit = 5.f;

	int attackRand1 =-1;
	float bossAttackTimeOne =0.f;
	float bossAttackTimeOneLimit = 1.0f;
	float bossAttackNoramalPatternChangeTimeLimit = 20.f;
	float bossAttackNoramalPatternChangeTime =0.f;

	bool bossDie = false;
	int score = 0 ;
	bool useBoomb = false;

	sf::Vector2f testpos;

};

