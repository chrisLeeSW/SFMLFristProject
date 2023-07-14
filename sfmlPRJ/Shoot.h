#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

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
	enum class PlayerShootingInfo
	{

	};
	enum class BossAttackType
	{
		Straight,
	};

	Shoot(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId,n){}
	virtual ~Shoot() override { Release();}

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	void PlayerFire(sf::Vector2f pos); //CharceterType type,float angle

	void BossNormalFire(sf::Vector2f pos,float angle,std::string clipName);
	void BossNormalFirePatten1(sf::Vector2f pos, float angle, std::string clipName);

	void SetAnimationId(const std::string& n);
	ObjectPool<Shoot>* pool = nullptr;

	void SetPlayer(Player* player);
	void SetBoss(Boss* boss);
protected:
	AnimationController animation;
	std::string animationClipName;
	std::string animationId ="";
	sf::Vector2f direction ;

	float speed = 500.f;

	CharceterType type = CharceterType::None;
	Player* player;
	Boss* boss;
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