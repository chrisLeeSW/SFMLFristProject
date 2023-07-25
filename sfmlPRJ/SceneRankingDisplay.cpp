#include "stdafx.h"
#include "SceneRankingDisplay.h"
#include "TextGo.h"
#include "SpriteGo.h"
SceneRankingDisplay::SceneRankingDisplay()  : Scene(SceneId::Game)
{
}

void SceneRankingDisplay::Init()
{
	Release();
	LoadFileRank("ranking.txt");
	LoadText();
	gameBackGround = (SpriteGo*)AddGo(new SpriteGo("graphics/GameSceneBackGround.png"));
	gameBackGround->SetPosition(-FRAMEWORK.GetWindowSize().x * 0.5f, -FRAMEWORK.GetWindowSize().y * 0.5f);
	gameBackGround->sortLayer = -1;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneRankingDisplay::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneRankingDisplay::Enter() // 들어올대 읽어서 출력 시키게끔 하는게 맞을 것 같음.
{
	
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	if (inputText)
	{
		newText = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
		newText->SetOrigin(Origins::MC);
		newText->text.setCharacterSize(50);
		newText->SetPosition(150.f, 0.f);
	}
	HighScore();
	Scene::Enter();
}

void SceneRankingDisplay::Exit()
{
	Scene::Exit();
}

void SceneRankingDisplay::Update(float dt)
{
	/*
	if (inputText)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
		{
			str[strCurretn] = 'A';
			strCurretn++;
		}
		else if (INPUT_MGR.GetKeyDown(sf::Keyboard::B))
		{
			str[strCurretn] = 'B';
			strCurretn++;
		}

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
		{
			inputText = false;
			PlayerRankInfo newPlayer;
			newPlayer.playerName = str;
			newPlayer.score = 1000;
			playerRankInfo.emplace_back(newPlayer);
			SaveFileRank("ranking.txt");
		}
		if (strCurretn >= 3) strCurretn = 2;

		newText->text.setString(str);
	}
	// 테스트 코드인데...이걸 어떻게 접근 시킬까 고민해야함..
	*/
	Scene::Update(dt);
}

void SceneRankingDisplay::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneRankingDisplay::SaveFileRank(const std::string& path)
{
	std::ofstream file(path);
	if (!file)
	{
		std::cout << "Error: Cannot open file for writing." << std::endl;
		return;
	}

	for (const auto& player : playerRankInfo)
	{
		file << player.playerName << " " << player.score << std::endl;
	}

	file.close();
}

void SceneRankingDisplay::LoadText()
{
	std::sort(playerRankInfo.begin(), playerRankInfo.end(), [](const PlayerRankInfo& a, const PlayerRankInfo& b) {
		return a.score > b.score;
		});

	// rankingBoard에 이전에 생성된 TextGo 객체들이 있다면 삭제합니다.
	for (auto text : rankingBoard)
	{
		delete text;
	}
	rankingBoard.clear();

	// 최대 10개까지만 출력합니다.
	int maxRankingCount = std::min(10, static_cast<int>(playerRankInfo.size()));
	for (int i = 0;i < maxRankingCount;++i)
	{
		TextGo* text = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
		text->SetOrigin(Origins::MC);
		text->text.setCharacterSize(50);
		text->SetPosition(-250.f, -300.f + (i * 50.f));
		std::stringstream str;
		str << "No" << i+1 << ": " << playerRankInfo[i].playerName << "\t" << "Score" << playerRankInfo[i].score;
		text->text.setString(str.str());
		rankingBoard.push_back(text);
		
	}
}

int SceneRankingDisplay::HighScore()
{

	return playerRankInfo[0].score;
}

void SceneRankingDisplay::LoadFileRank(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Error: Cannot open file for reading." << std::endl;
		return;
	}
	playerRankInfo.clear();
	std::string name;
	int score;
	while (file >> name >> score)
	{
		playerRankInfo.emplace_back(name, score);
	}

	file.close();
}