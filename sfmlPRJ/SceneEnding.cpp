#include "stdafx.h"
#include "SceneEnding.h"
#include "SpriteGo.h"
void SceneEnding::LoadFromFile(const std::string& path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
	
	std::vector<std::string> paths = doc.GetColumn<std::string>(0);
	for (int i = 1;i < paths.size();++i)
	{
		textureId.push_back(paths[i]);
	}
	
}

SceneEnding::SceneEnding() : Scene(SceneId::Ending)
{
}

void SceneEnding::Init()
{
	
	

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneEnding::Release()
{
	textureId.clear();
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneEnding::Enter()
{
	LoadFromFile("script/EndingTextureId.csv");

	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	currentTextureId = 0;
	ending = (SpriteGo*)AddGo(new SpriteGo());
	ending->textureId = textureId[currentTextureId];
	ending->Reset();
	ending->SetPosition(-FRAMEWORK.GetWindowSize().x * 0.5f, -FRAMEWORK.GetWindowSize().y *0.5f);

	
	Scene::Enter();
}

void SceneEnding::Exit()
{
	Scene::Exit();
}

void SceneEnding::Update(float dt)
{
	timer += dt;

	if (timer > 5.f)
	{
		timer = 0.f;
		currentTextureId++;
		if (currentTextureId == textureId.size())
		{
			SCENE_MGR.ChangeScene(SceneId::Title);
		}
		ending->textureId = textureId[currentTextureId];
		ending->Reset();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	Scene::Update(dt);
}

void SceneEnding::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
