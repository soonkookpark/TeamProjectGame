#pragma once
#include "GameObject.h"
#include "FieldItem.h"
#include "EquipItem.h"
#include "SpriteGo.h"

class Player;
class TextGo;
class Inventory : public GameObject
{
public:
	struct MyItemInfo {
		sf::Sprite iconImage;
		std::string itemName;
		std::string itemDescription;
	};
	struct MyStatusInfo {
		std::string jobName;
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
		int luck;
	};
protected:
	SpriteGo inventoryMenu;
	std::vector<Inventory::MyItemInfo*> equipItemImageInMyInventory;
	std::list<GameObject*> inventoryImageUI;
	Player* player;
	MyStatusInfo myInventoryStatusInfo;
	sf::RectangleShape inventoryBox;

	TextGo* inventoryText1 = nullptr;
	TextGo* inventoryText2 = nullptr;
	TextGo* inventoryText3 = nullptr;
	TextGo* inventoryText4 = nullptr;
	TextGo* inventoryText5 = nullptr;
	TextGo* inventoryText6 = nullptr;
	TextGo* inventoryText7 = nullptr;
	TextGo* inventoryText8 = nullptr;
	TextGo* inventoryText9 = nullptr;
	TextGo* inventoryText10 = nullptr;
	TextGo* inventoryText11 = nullptr;
	TextGo* inventoryText12 = nullptr;
	TextGo* inventoryText13 = nullptr;
	TextGo* inventoryText14 = nullptr;
	TextGo* inventoryText15 = nullptr;
	TextGo* inventoryText16 = nullptr;
	TextGo* inventoryText17 = nullptr;
	TextGo* inventoryText18 = nullptr;
	TextGo* inventoryText19 = nullptr;

	
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
	void FindGameText();
};

