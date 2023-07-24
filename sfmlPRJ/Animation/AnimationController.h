#pragma once


class AnimationController
{
private:

protected:
	static int clipSizeSum ;

	std::unordered_map<std::string, AnimationClip*> clips;
	std::queue<std::string> queue;
	float speed = 1.f; // aniation ���۽�ų �ӵ�
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame =-1; // ���° clip���� Ȯ��
	int totalFrame = 0;
	float clipDuration = 0.f;
	float accumTime = 0.f;

	sf::Sprite* target = nullptr; // img ��������
	

public:


	void AddClip(AnimationClip& newClip);
	void SetTarget(sf::Sprite* sprite) { target = sprite; };
	sf::Sprite* GetTarget()const { return target; };
	bool IsPlaying() { return isPlaying; };
	void SetSpeed(float s) { speed = s; };
	float Speed()const { return speed; };

	void Update(float dt);

	void Play(const std::string& clipid, bool clearQueue = true);
	void PlayQueue(const std::string& clipid); // play�Ѱ��� ��Ƶѷ����ϴ°�

	void Stop(); //

	void SetFrame(const AnimationFrame& frame);

	std::queue<std::string> GetQueue()const;
	std::string GetCurrentClipId()const;
};

