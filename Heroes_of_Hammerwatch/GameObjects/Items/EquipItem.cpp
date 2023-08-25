#include "stdafx.h"
#include "EquipItem.h"
#include "EquipItemTable.h"
#include "DataTableMgr.h"
#include "ResourceMgr.h"
EquipItem::EquipItem(int key)
	:SpriteGo("", "EquipItem")
{
	SetData(key);

	//수정 필요
	sortLayer = 200;
}

void EquipItem::SetData(int key)
{
	
	EquipItemTable* table = DATATABLE_MGR.Get<EquipItemTable>(DataTable::Ids::EquipItem);
	equipment = table->Get(key);
	//sprite.setTexture(*RESOURCE_MGR.GetTexture(equipment.itemName));
	std::cout << "equipment.attackPower: " << equipment.attackPower << std::endl;
	std::cout << "equipment.defense: " << equipment.defense << std::endl;
	std::cout << "equipment.itemName: " << equipment.itemName << std::endl;
	std::cout << "equipment.speed: " << equipment.speed << std::endl;


	//return equipment;
}

void EquipItem::Reset()
{
}

void EquipItem::Update(float dt)
{
}

EquipItem::ItemInfo EquipItem::PullEquipInfo()
{
	return equipment;
}
