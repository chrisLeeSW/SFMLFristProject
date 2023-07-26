#pragma once
#include "Scene.h"
class Player;
class Boss;
class SpriteGo;
class TextGo;
class SoundGo;

class SceneGame : public Scene
{
protected:
	Player* player;
	Boss* bossCirno;
	TextGo* bossName;
	SpriteGo* background;
	SpriteGo* gameBackground;
	SpriteGo* miniUi;
	SpriteGo* titleNameHong;
	SpriteGo* bossEffect;
	sf::Vector2f gameWallSize;

	bool isTalking;
	bool bossAngry;
	int talkCount = 0;
	SpriteGo* cirnoTalking;
	SpriteGo* playerTalking;

	sf::RectangleShape shape;
	TextGo* talk;

	sf::RectangleShape hpBar;
	float hpBarbyX = 0.f;

	sf::Clock clock;
	sf::Time frameTime;
	int frames = 0;

	SoundGo* music1;
	SoundGo* bossDie;
	SoundGo* timeOutSound;
	float musicVolum = 5.f;

	float soundTime;
	bool soundPlay;

	SpriteGo* scoreBys;
	SpriteGo* scoreByc;
	SpriteGo* scoreByo;
	SpriteGo* scoreByr;
	SpriteGo* scoreBye;
	SpriteGo* scoreByClone;
	TextGo* scoreNumber;

	TextGo* playerLife;
	SpriteGo* playerLifeSprite[2];
	int playerLifeSpriteCurrent = 2;

	TextGo* boombCount;
	SpriteGo* boombCountSprite[5];
	int boombCountSpriteCurrent = -1;
	int maxBoombCountSpritecurretn =5;

	TextGo* gameTimeText;
	float gameTimer = 90.f;

	TextGo* playerDamageText;

	std::queue<std::wstring> talking;

	SpriteGo* gameOver;
	bool timeOut = false;
	int randStatus;
	bool getBoomb = false;
	bool getPlayerLife = false;


public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void DecreasePlayerLife();
	void IncreasePlayerLife();
	void UseBoomb();
	int GetBoombCountSpriteCurrent() { return boombCountSpriteCurrent; }
	void SettingText();
	void LoadGameSceneResource();
	void GamePlaySettingReset();
	void GameOver();
	void BossEffectSetting();
	void PlayerStatusSetting();
	void BossHpBarSet();
	void SetTextGoByTexture();
};

