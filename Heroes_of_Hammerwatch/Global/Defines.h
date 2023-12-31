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
	FIELD_ITEMS,
	PLAYER,
	G_MONSTER,
	WALL,
	A_MONSTER,
	EFFECT_TEXT,
	UI = 101,
	UI_TEXT,
};

enum SightDegree
{
	R = 0, //-22.5~22.5
	DR,
	D,
	DL,
	L,
	UL,
	U,
	UR,
};

struct TileInfo
{
	std::string texture_ID;
	sf::FloatRect bound;
	std::string name;
	int index;
};

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};


#include "AnimationClip.h"