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
	AnimationClip,//파일하나당 애니메이션 클립 하나.
};

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Edit,
	Count,
};

enum class AttackType
{
	None = -1,
	Physic,
	Magic,
	Count,
};

enum SortLayer
{
	//SortLayer 값 정의
	TILE = 0,
	PLAYER,
	G_MONSTER,
	WALL,
	A_MONSTER,
	UI = 101,
};


#include "AnimationClip.h"