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

void EquipItem::SetData(int key)
{
	equipment = DATATABLE_MGR.Get<EquipItemTable>(DataTable::Ids::EquipItem)->Get(key);
	sprite.setTexture(*RESOURCE_MGR.GetTexture(equipment.itemName));
}

void EquipItem::Reset()
{
}

void EquipItem::Update(float dt)
{
}

<<<<<<< HEAD
=======
std::string EquipItem::getString()
{
	return equipment.itemName;
}

>>>>>>> f04772722ce356dddd2946b04c76968c9aadd923