#include "stdafx.h"
#include "Inventory.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "SceneMgr.h"

Inventory::Inventory(const std::string& n)
	:GameObject(n), inventoryMenu("graphics/Inventory/Inventory.png","InventoryMenuImage")
{
	AddInventory(&inventoryMenu);
	inventoryMenu.SetActive(false);
	//inventoryMenu.sprite.setScale(0.5f, 0.5f);
	//sortOrder = UI;
	sortLayer = UI;
}

Inventory::~Inventory()
{
	Release();
}

bool Inventory::ExistInventory(GameObject* go)
{
	return std::find(inventoryImageUI.begin(), inventoryImageUI.end(), go) != inventoryImageUI.end();
}

GameObject* Inventory::AddInventory(GameObject* go)
{
	if (!ExistInventory(go))
	{
		inventoryImageUI.push_back(go);
	}
	return go;
}

void Inventory::SetPlayer(Player* player1)
{
	this->player = player1;
}

void Inventory::InventoryDisplay()
{
	//inventoryMenu.SetPosition(player->GetPosition().x, player->GetPosition().y);
	inventoryMenu.SetActive(!inventoryMenu.GetActive());
	if (inventoryMenu.GetActive())
	{

	}
}

void Inventory::AddItem()
{

}

void Inventory::Init()
{
	for (auto i : inventoryImageUI)
	{
		i->Init();
	}
}

void Inventory::Reset()
{
	inventoryMenu.Reset();
	inventoryMenu.SetOrigin(Origins::MC);
	//Player* player = (Player*)SCENE_MGR.GetCurrScene()->FindGo("")
	
}

void Inventory::Release()
{
	inventoryImageUI.clear();
}

void Inventory::Update(float dt)
{
}

void Inventory::Draw(sf::RenderWindow& window)
{
	
	for (auto m : inventoryImageUI)
	{
		if (m->GetActive())
		{
			m->Draw(window);
		}
	}

}
void Inventory::AddItemToInventory(MyItemInfo* itemInfo)
{
	equipItemImageInMyInventory.push_back(itemInfo);
}

const std::vector<Inventory::MyItemInfo*> Inventory::GetInventoryItems() const 
{
	return equipItemImageInMyInventory;
}