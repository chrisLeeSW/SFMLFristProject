#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AimationClip,
	SpriteFont,
};

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Ending,
	RankTitle,
	Count,
};

#include "AnimationClip.h"