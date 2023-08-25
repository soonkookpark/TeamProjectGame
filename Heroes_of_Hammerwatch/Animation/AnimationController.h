#pragma once
class AnimationController
{

protected:
	std::unordered_map<std::string/*ID*/, AnimationClip> clips;
	std::queue<std::string> queue; //애니메이션 큐.





	float speed = 1.f; // 애니메이션 재생 배율 2면 2배빠르게 등등등등드읃읃읃ㅇ
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame = -1;
	int totalFrame = 0;
	float clipDuration = 0.f; //한 프레임당 얼마나 재생할지
	float accumTime = 0.f; //타이머 얼마나 시간이 지났는지~ 클립지날때마다 갱신하고 등등등등등등


	sf::Sprite* target = nullptr;

public:
	void AddClip(const AnimationClip& newClip);
	void SetTarget(sf::Sprite* sprite) { target = sprite; }
	sf::Sprite* GetTarget() const { return target; }
	bool IsPlaying() { return isPlaying; }
	void SetSpeed(float s) { speed = s; }
	float Speed() const { return speed; }

	void Update(float dt);

	void Play(const std::string& clipId, bool ClearQueue = true);
	void PlayQueue(const std::string& clipId);

	void Stop();

	float GetTotalPlayTime(const std::string& clipId);

	void SetFrame(const AnimationFrame& frame);
	void SetFrame(int frame) { currentFrame = frame; }
	std::string GetCurrentClipId();
	int GetCurrFrame() { return currentFrame; }
};

