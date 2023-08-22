#include "stdafx.h"
#include "EquipItem.h"
#include "EquipItemTable.h"
#include "DataTableMgr.h"
#include "ResourceMgr.h"
EquipItem::EquipItem(int key)
	:SpriteGo("", "EquipItem")
{
	SetData(key);
	
}

EquipItem::ItemInfo EquipItem::SetData(int key)
{
	equipment = DATATABLE_MGR.Get<EquipItemTable>(DataTable::Ids::EquipItem)->Get(key);
	sprite.setTexture(*RESOURCE_MGR.GetTexture(equipment.itemName));

	return equipment;
}

void EquipItem::Reset()
{
}

void EquipItem::Update(float dt)
{
}
