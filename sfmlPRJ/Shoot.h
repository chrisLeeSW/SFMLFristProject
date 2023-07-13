#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"
class Shoot : public SpriteGo
{

public:
	enum class CharceterType
	{
		None,
		Player,
		Boss,
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

	void BossFire(sf::Vector2f pos);

	void SetFileName(std::string n);
	ObjectPool<Shoot>* pool = nullptr;
protected:
	AnimationController animation;
	std::string fileNames;
	sf::Vector2f direction ;

	float speed = 300.f;

	CharceterType type = CharceterType::None;
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