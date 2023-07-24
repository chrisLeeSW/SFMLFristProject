#include "stdafx.h"
#include "AudiGo.h"

AudioGo::~AudioGo()
{
	GameObject::Release();
}

void AudioGo::Release()
{
}

void AudioGo::Reset()
{
	sf::SoundBuffer* soundbuffer = RESOURCE_MGR.GetSoundBuffer(audioFile);
	if (soundbuffer != nullptr)
	{
		sound.setBuffer(*soundbuffer);
	}
}
