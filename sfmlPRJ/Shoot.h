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
		testcode,
		DelayTimeAttackOneType,
		DelayTimeAttackTwoType,
		testcode3,
		DelayType,
		TornadoTypeLoof,
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
		float delayTime = 3.0f;
	};

	Shoot(const std::string& textureId = "", const std::string& n = "") :SpriteGo(textureId,n){		}
	virtual ~Shoot() override { Release();}

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	void BossFire(float dt);
	void PlayerFire(float dt);

	void PlayerFire(sf::Vector2f pos, sf::Vector2f dir,std::string id); 
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float speed =500.f);
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, float angle, std::string clipId, float freq, float amp,float speed=500.f);
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, std::string clipId, float speed = 500.f);
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, sf::Vector2f dir,std::string clipId);
	void SetPattenInfo(NoramalPatten pattenType, sf::Vector2f pos, std::string clipId,float angle,float delay, float speed = 500.f);


	ObjectPool<Shoot>* pool = nullptr;

	void SetPlayer(Player* player);
	void SetBoss(Boss* boss);


	void SetWallBounds(sf::Vector2f boundf, float widthX, float widthY);
protected:
	NormalPattenInfo patternInfo;
	
	bool checkFireType = false;

	float frequency;
	float amplitude;
	float accuTime;

	AnimationController animation;

	sf::Vector2f direction ;
	sf::Vector2f velocity = { 0.f,0.f };


	CharceterType type = CharceterType::None;
	Player* player;
	Boss* boss;
	sf::Vector2f WallBounds;
	float bgWidth;
	float bgHeight;
	float delayTime;
	bool delayOnAttackType = false;
	bool delayOnAttackingOne = false;

	bool testing2 = false;
	bool testing3 = false;


	float testing1DirSet = 0.f;
	int tornadoCount = 0;
	
};
