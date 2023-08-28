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
	//AnimationController animation; //애니메이터 컨ㄹ트롤러를 만들어 스프라이트를 하나집어 현재 재생하고싶은 애니메이션의 프레임에 맞춰 좌표를 변경하는 기능을 넣었다. 사용을 어떻게하나 애니메이션 개체마다 초기화해야함. 애니메이션 클립들. 클립들을 추가해줘야겟지? 애드클립이 그걸하는거야
	// 가보면 인서트 하잕ㅎ아 init랑 쌍으로  animation클립에 잇는것들 확인
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
	//이미지 받는 방식
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
	void AcquireItem(int key);//아이템을 얻는다면 실행 할 함수 리턴 값이랑 그런거는 바꿔줘야되 순국이형!!
	//고마워 다훈아

	void Collider(int x, int y);
	sf::RectangleShape GetPlayerBox() { return box; }
	void TestCode();
	//std::vector<Player::InventoryItem> GetInventoryInfo();
	void InventoryOnOff();
	PlayerInfo* ControlPlayerInfos() { return &pTable; }
	float PlayerNowExp() { return currentExp; }

	void ChangeLayer();
};

