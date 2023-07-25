#pragma once
#include "Scene.h"
class TextGo;
class SpriteGo;
class SceneRankingDisplay : public Scene
{

public:
	struct PlayerRankInfo
	{
		std::string playerName;
		int score;
		PlayerRankInfo(const std::string& name="---", int score=0) : playerName(name), score(score) {}
	};
	SceneRankingDisplay();
	virtual ~SceneRankingDisplay() override = default;

	virtual void Init();
	virtual void Release();
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);
	void LoadFileRank(const std::string& id);
	void SaveFileRank(const std::string& id);
	void LoadText();
	int HighScore();
protected:
	std::vector<PlayerRankInfo> playerRankInfo;
	std::vector<TextGo*> rankingBoard;

	SpriteGo* gameBackGround;

	TextGo* newText;
	bool inputText=true;
	char str[3];
	int strCurretn = 0;
};

