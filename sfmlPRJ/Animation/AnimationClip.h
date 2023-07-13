#pragma once

enum class AnimationLoopTypes
{
	Single,  // �ѹ� ����
	Loop,   // ��� ���� ��Ű��
};
struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;  
	// int���� Rect���� top left width height �� ��������
	std::function<void()> action;
};

struct AnimationClip 
//�� �������� ������ �ִ� Clip
{
	std::string id;
	AnimationLoopTypes loopType;
	int fps;

	std::vector<AnimationFrame> frames;
	bool LoadFromFile(const std::string path);
};