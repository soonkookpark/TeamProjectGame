#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"


class Player : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};

protected:
	AnimationController animation; //애니메이터 컨ㄹ트롤러를 만들어 스프라이트를 하나집어 현재 재생하고싶은 애니메이션의 프레임에 맞춰 좌표를 변경하는 기능을 넣었다. 사용을 어떻게하나 애니메이션 개체마다 초기화해야함. 애니메이션 클립들. 클립들을 추가해줘야겟지? 애드클립이 그걸하는거야
	// 가보면 인서트 하잕ㅎ아 init랑 쌍으로  animation클립에 잇는것들 확인
	sf::Vector2f direction;
	float speed = 500.f;

	bool filpX = false;
	bool isGround = true;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

	int money;
	int ore;

	//RectangleGo* testRect;
public:
	Player(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	bool GetFlipX() const;
	void SetFlipX(bool filp);
	void PlayerMove();

	void Sword();
	void Shield();
	void Skill3();

	void HealHP(int value);
	void HealMP(int value);

	void AcquireOre(int value) { ore += value; };
	void AcquireMoney(int value) { money == value; };
	void AcquireKey(int value) {};
	void AcquireItem(int key) {};//아이템을 얻는다면 실행 할 함수 리턴 값이랑 그런거는 바꿔줘야되 순국이형!!
};

