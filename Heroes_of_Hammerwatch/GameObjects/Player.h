#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class TileMap;
class RectangleGo;

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
	float speed = 100.f;

	bool filpX = false;
	bool isGround = true;
	
	sf::Vector2i playerTileIndex;
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	TileMap* tilemap;
	int tileSize;
	int tilePixelSize = 16;
	sf::RectangleShape box;
	sf::Vector2f agoTile;
	sf::Vector2f newTile;
	RectangleGo* testRect;
	sf::Vector2f look;
	float angle;
	SightDegree lookat = SightDegree::R;
public:
	Player(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	bool GetFlipX() const;
	void SetFlipX(bool filp);
	void PlayerMove();
	void FindTileInfo();
	bool CheckTileInfo(sf::Vector2f info);
	int CharacterSight(float angle);

	void SetTile(TileMap* tile);
	void BoxMaker();
};

