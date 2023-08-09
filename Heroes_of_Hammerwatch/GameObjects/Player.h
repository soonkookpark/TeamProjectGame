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
	AnimationController animation; //�ִϸ����� ����Ʈ�ѷ��� ����� ��������Ʈ�� �ϳ����� ���� ����ϰ���� �ִϸ��̼��� �����ӿ� ���� ��ǥ�� �����ϴ� ����� �־���. ����� ����ϳ� �ִϸ��̼� ��ü���� �ʱ�ȭ�ؾ���. �ִϸ��̼� Ŭ����. Ŭ������ �߰�����߰���? �ֵ�Ŭ���� �װ��ϴ°ž�
	// ������ �μ�Ʈ �ϟꤾ�� init�� ������  animationŬ���� �մ°͵� Ȯ��
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
	void AcquireItem(int key) {};//�������� ��´ٸ� ���� �� �Լ� ���� ���̶� �׷��Ŵ� �ٲ���ߵ� ��������!!
};

