#pragma once
#include "GameObject.h"
#include "FieldItem.h"
#include "EquipItem.h"
#include "SpriteGo.h"

class Player;
class Inventory : public GameObject
{
public:
	struct MyItemInfo {
		sf::Sprite iconImage;
		std::string itemName;
		std::string itemDescription;
	};
	struct MyStatusInfo {
		int playerMaxHp;
		int playerMaxMp;
		float playerHealHp;
		float playerHealMp;
		int playerSpeed;
		int playerExp;
		int playerAtkPower;
		int playerMagicPower;
		int skillPower;
		int criticalChance;
		int armor;
		int resistance;
	};
protected:
	SpriteGo inventoryMenu;
	std::vector<Inventory::MyItemInfo*> equipItemImageInMyInventory;
	std::list<GameObject*> inventoryImageUI;
	Player* player;
	MyStatusInfo myInventoryStatusInfo;
	sf::RectangleShape inventoryBox;

public:
	Inventory(const std::string& n = "Inventory");
	virtual ~Inventory();
	void InventoryDisplay();
	void AddItem();
	bool ExistInventory(GameObject* go);
	GameObject* AddInventory(GameObject* go);
	void SetPlayer(Player* player1);
	
	virtual void Init();
	virtual void Reset();	// √ ±‚»≠
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window)override;


	void AddItemToInventory(MyItemInfo* itemInfo);
	const std::vector<Inventory::MyItemInfo*> GetInventoryItems() const;
	void Collocate(Player* player);

};

