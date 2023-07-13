#include "stdafx.h"
#include "AnimationController.h"
#include "ResourceMgr.h" // sprite �� ����
void AnimationController::AddClip(const AnimationClip& newClip)
{
	if (clips.find(newClip.id) == clips.end())
	{
		clips.insert({ newClip.id,newClip });
	}
} // ?? clips

void AnimationController::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0.f;
	++currentFrame;
	
	
	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id=queue.front();
			queue.pop();
			Play(id,false);
			return;
		}
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				return;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			}

		}

	}
	if(currentClip->frames[currentFrame].action != nullptr)
	{
		currentClip->frames[currentFrame].action();
	}


	if (target != nullptr)
	{
		SetFrame(currentClip->frames[currentFrame]);
	}

}

void AnimationController::Play(const std::string& clipid, bool clearQueue)
{
	if (clearQueue)
	{
		while (!queue.empty())
			queue.pop();
	} // queue �� clear �Լ��� pop���� clear �� ���

	auto id = clips.find(clipid);

	if (clips.find(clipid) == clips.end())
	{
		Stop();
		std::cout << "ERR : Not EXIST CLIP" << std::endl;
		return;
	}

	isPlaying = true;

	currentClip = &id->second;
	currentFrame = 0;
	totalFrame = currentClip->frames.size();
	clipDuration = 1.f / currentClip->fps;
	accumTime = 0.f;

	SetFrame(currentClip->frames[currentFrame]);

}

void AnimationController::PlayQueue(const std::string& clipid)
{
	queue.push(clipid);

}

void AnimationController::Stop()
{
	isPlaying = false;

}

void AnimationController::SetFrame(const AnimationFrame& frame) // ?
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(frame.textureId);
	target->setTexture(*tex);
	target->setTextureRect(frame.texCoord);
}

std::queue<std::string> AnimationController::GetQueue() const
{
	return queue;
}

std::string AnimationController::GetCurrentClipId() const
{
	if (currentClip == nullptr)
		return "";
		
	return currentClip->id;
}
