#pragma once

enum class AnimationLoopTypes
{
	Single,	//한번만 재생
	Loop,	// 루프
};

struct AnimationFrame 
{
	std::string textureId;
	sf::IntRect	texCoord;//floatRect도 있고 이놈도 있다.
	std::function<void()> action/*= nullptr*/;//특정한 프레임이 시작할때 호출할 함수를 넣는거야 이건 그리고 초기화해야해.
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;//애니메이션이벤트
	AnimationLoopTypes loopType;
	int fps;

	bool LoadFromFile(const std::string path);
};

