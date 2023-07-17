#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

#include "UniqueShootMGR.h"

class Player;
class Boss;
class Shoot : public SpriteGo
{

public:
	enum class CharceterType
	{
		None,
		Player,
		Boss,
	};
	enum class NoramalPatten
	{
		None = -1,
		SectorType,
		AngleDirectionType,
		FrequencyType,
		ColumnType,
		RowRightType,
		RowLeftType,
	};
	enum class UniqueType
	{
		None=-1,
		TornadoType,
	};
	struct NormalPattenInfo
	{
		NoramalPatten pattenType= NoramalPatten::None;
		sf::Vector2f pos = {0.f,0.f};
		float angle =0.f;
		std::string animationClipId = "";
		float frequency=1.f;
		float amplitude=1.f;
		float speed = 500.f;
	};
	Shoot(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId,n){}
	virtual ~Shoot() override { Release();}

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	void BossFire(float dt);
	void PlayerFire(float dt);

	void PlayerFire(sf::Vector2f pos); //CharceterType type,float angle
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId);
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float freq, float amp);

	void BossNormalFire(sf::Vector2f pos,float angle,std::string clipName);
	void BossNormalFirePatten1(sf::Vector2f pos, float angle, std::string clipName);
	void testFire(sf::Vector2f pos, float frequency, float amplitude, std::string clipName);

	void SetAnimationId(const std::string& n);
	ObjectPool<Shoot>* pool = nullptr;

	void SetPlayer(Player* player);
	void SetBoss(Boss* boss);

	void SetDirection(sf::Vector2f);

	bool test = false;
	float accumulatedTime = 0.f;
	void frequencyMovement(float dt);


	void SetPositionTest(sf::Vector2f test1pos, sf::Vector2f test2dir)
	{
		uniqueType = UniqueType::TornadoType;
		position = test1pos;
		direction = test2dir;
	}
	bool testUnique = false;
	bool GetTestUnique()const
	{
		return testUnique;
	}
	void ShootBulletWithAngle(float angle, const std::string& clipId)
	{
		type = CharceterType::Boss;
		direction = sf::Vector2f(std::cos(angle), std::sin(angle));
		animation.Play(clipId);
	}


	void SetWallBounds(sf::Vector2f boundf, float widthX, float widthY);
protected:
	UniqueType uniqueType = UniqueType::None;
	NormalPattenInfo pattenInfo;
	
	bool testCode = false;

	float frequency;
	float amplitude;
	float accuTime;

	AnimationController animation;
	std::string animationClipName;
	std::string animationId ="";

	sf::Vector2f direction ;
	sf::Vector2f velocity = { 0.f,0.f };


	CharceterType type = CharceterType::None;
	Player* player;
	Boss* boss;
	sf::Vector2f WallBounds;
	float bgWidth;
	float bgHeight;
};

/*
void Shoot::Fire(sf::Vector2f pos, float angle, CharceterType types)
{
	type = types;
	if (type == CharceterType::Player)
	{
		sprite.setScale(0.5f, 0.5f);
	}
	position = pos;
	// 각도를 라디안으로 변환
	float radians = angle * static_cast<float>(M_PI) / 180.f;
	// 방향 벡터 계산
	direction = sf::Vector2f(std::cos(radians), std::sin(radians));
}
*/