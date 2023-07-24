#pragma once
#include "GameObject.h"
class AudioGo : public GameObject
{
protected:
	std::string audioFile;
	sf::Sound sound;

public:
	AudioGo(const AudioGo& obj) = delete;
	AudioGo& operator=(const AudioGo& obj) = delete;
	AudioGo(const std::string& id = "",const std::string& n = "") :GameObject(n), audioFile(id) {}
	virtual ~AudioGo() override;
	virtual void Init() { GameObject::Init(); }
	virtual void Release() override;
	virtual void Reset()override;
	virtual void Update(float dt) { GameObject::Update(dt); }
	virtual void Draw(sf::RenderWindow& window) { GameObject::Draw(window); }

};

