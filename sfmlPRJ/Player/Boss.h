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
class SoundGo;
class Boss :public SpriteGo // æ‡ 900MB∏‘¿Ω
{
protected:
	AnimationController animation;
	sf::Vector2f direction;
	bool moveBoss = false;
	float speed = 300.f;
	Player* player=nullptr;
	sf::Vector2f WallBounds;
	float bgWidth=0.f;
	float bgHeight=0.f;
	float bossHp = 810.f; 
	ObjectPool<Shoot> bossShootPool;
	ShootMGR shootPatternMgr;
	UniqueShootMGR uniqueshootPatternMgr;
	SoundGo* bossTan;

	sf::Vector2f endPos;
	sf::Vector2f startPos;
	sf::Vector2f secondPos;
	float stopAttackTime = 0.f;
	float stopAttackTimeLimit = 2.0f;
	bool stopBoss = false;
	float moveTimerDuration = 0.f;
	float moveTime = 0.f;
	float moveDuration = 3.f;
	float stopLimit = 5.f;

	int attackRand1 = -1;
	float bossAttackTimeOne = 0.f;
	float bossAttackTimeOneLimit = 1.0f;
	float bossAttackNoramalPatternChangeTimeLimit = 0.f;
	float bossAttackNoramalPatternChangeTime = 0.f;
	float bossAttackTimeTwoLimit = 1.0f;

	bool bossDie = false;
	int score = 0;
	bool useBoomb = false;

	bool onePage = true;
	bool twoPage = false;
	bool threePage = false;
	bool fourPage = false;
	bool effectUniqueAttack = false;
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


	sf::Vector2f CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p3, float t);
	float GetBossHp() { return bossHp; }
	bool GetBossDie(){ return bossDie; }
	int GetScore() { return score; }
	void SetUseBoomb(bool t) { useBoomb = t; }
	bool GetBossStop() {return effectUniqueAttack;}
};

