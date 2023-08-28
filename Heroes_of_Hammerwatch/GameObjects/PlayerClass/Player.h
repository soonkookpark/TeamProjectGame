#pragma once
#include "Creature.h"
#include "AnimationController.h"

class TileMap;
class OnTileMap;
class RectangleGo;
class EquipItem;
class SpriteGo;
class Inventory;
class Player : public Creature
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};
	struct PlayerInfo
	{
		std::string ClassName;
		int manaPoint = 0;
		int healthPowerPerLevel = 0;
		int manaPointPerLevel = 0;
		float HealthHeal = 0.f;
		float ManaHeal = 0.f;
		float HealthHealPerLevel = 0.f;
		float ManaHealPerLevel = 0.f;
		float DefencePerLevel = 0.f;
		float ResistancePerLevel = 0.f;
		float AttackPower = 0.f;
		float SkillPower = 0.f;
		float CriticalRate = 0.f;
		float CriticalDamage = 0.f;
		float SkillCriticalRate = 0.f;
		float SkillCriticalDamage = 0.f;
		float ExpPerLevel = 0.f;
	};

	struct InventoryItem
	{
		//EquipItem::ItemInfo itemInfo;
		sf::Sprite ItemImage;
		std::string itemName;
		std::string itemDescription;
	};

protected:
	//AnimationController animation; //�ִϸ����� ����Ʈ�ѷ��� ����� ��������Ʈ�� �ϳ����� ���� ����ϰ���� �ִϸ��̼��� �����ӿ� ���� ��ǥ�� �����ϴ� ����� �־���. ����� ����ϳ� �ִϸ��̼� ��ü���� �ʱ�ȭ�ؾ���. �ִϸ��̼� Ŭ����. Ŭ������ �߰�����߰���? �ֵ�Ŭ���� �װ��ϴ°ž�
	// ������ �μ�Ʈ �ϟꤾ�� init�� ������  animationŬ���� �մ°͵� Ȯ��
	sf::Vector2f direction;
	//float speed = 100.f;
	float curMana = 0.f;

	bool filpX = false;
	bool isGround = true;
	bool isAnimationPlay = false;
	bool attackNow = false;
	bool inventoryUI = false;

	PlayerInfo pTable;
	//sf::Vector2i playerTileIndex;
	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	//TileMap* tilemap;
	int tileSize = 16;
	int tilePixelSize = 16;
	sf::RectangleShape box;
	sf::Vector2i tileIntSize;
	
	//RectangleGo* testRect;	
	
	float angle = 0.f;
	float pastAngle = 0.f;
	float currentExp = 0.f;

	int money = 0;
	int ore = 0;

	//test clock
	sf::Clock clock1;
	
	sf::RectangleShape testTiles[8];
	sf::RectangleShape testIntersect;
	//sf::Sprite spriteImage;
	//�̹��� �޴� ���
	//RectangleGo* testRect;
	
	std::vector<InventoryItem> inventoryInfo;
	//EquipItem equipItem;
	sf::Sprite charInventory;
	SpriteGo* charInventory1;

	Inventory* inventory = nullptr;

public:
	Player(const std::string& textureId = "", const std::string& n = "player");
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetData(const std::string& name);
	bool GetFlipX() const;
	void SetFlipX(bool filp);
	void PlayerMove(float dt);

	int CharacterSight(float angle);
	//void IdleAnimationPrint(SightDegree lookat);
	//void MoveAnimationPrint(SightDegree lookat);
	//void AttackAnimationPrint(SightDegree lookat);
	void SetTile(TileMap* tile);

	virtual void SetDead() override;
	 
	void HealMP(int value);

	void AcquireOre(int value) { ore += value; };
	void AcquireMoney(int value) { money += value; };
	void AcquireKey(int value) {};
	void AcquireItem(int key);//�������� ��´ٸ� ���� �� �Լ� ���� ���̶� �׷��Ŵ� �ٲ���ߵ� ��������!!
	//���� ���ƾ�

	void Collider(int x, int y);
	sf::RectangleShape GetPlayerBox() { return box; }
	void TestCode();
	//std::vector<Player::InventoryItem> GetInventoryInfo();
	void InventoryOnOff();
	PlayerInfo* ControlPlayerInfos() { return &pTable; }
	float PlayerNowExp() { return currentExp; }

	void ChangeLayer();
};

