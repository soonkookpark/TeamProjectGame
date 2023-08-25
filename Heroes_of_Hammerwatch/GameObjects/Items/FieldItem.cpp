#include "stdafx.h"
#include "FieldItem.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "FieldItemTable.h"
#include "DataTableMgr.h"
#include "InputMgr.h"
#include "EquipItem.h"
FieldItem::FieldItem(const std::string& key)
	:SpriteGo("","FieldItem")
{
	SetData(key);
}

void FieldItem::SetData(const std::string& key)
{
	FieldItemTable* table = DATATABLE_MGR.Get<FieldItemTable>(DataTable::Ids::FieldItem);
	itemType = static_cast<ItemType>(table->Get(key)[0]);
	value = table->Get(key)[1];
	// 이 스프라이트를 넘겨야함.
	sprite.setTexture(*RESOURCE_MGR.GetTexture(key));
	
	sortLayer = SortLayer::FIELD_ITEMS;
}

void FieldItem::Reset()
{
	SpriteGo::Reset();
	player = (Player*)SCENE_MGR.GetCurrScene()->FindGo("player");
}

void FieldItem::Update(float dt)
{
	if (Utils::SpriteToSprite(sprite, player->sprite))
	{
		IntersectsWithItem();
	}
	
}

void FieldItem::IntersectsWithItem()
{
	std::string itemTypes[(int)ItemType::COUNT] =
	{
		"HP_POTION",
		"MP_POTION",
		"MONEY",
		"ORE",
		"KEY",
		"ITEM",
	};
	std::cout << "플레이어가 " << itemTypes[(int)itemType] << " 타입의 아이템을 얻었습니다." << std::endl;
	switch (itemType)
	{
	case FieldItem::ItemType::HP_POTION:
		player->HealHP(value);
		break;
	case FieldItem::ItemType::MP_POTION:
		player->HealMP(value);
		break;
	case FieldItem::ItemType::MONEY:
		player->AcquireMoney(value);
		break;
	case FieldItem::ItemType::ORE:
		player->AcquireOre(value);
		break;
	case FieldItem::ItemType::KEY:
		player->AcquireKey(value);
		break;
	case FieldItem::ItemType::ITEM:
		//std::cout<<
		player->AcquireItem(value);
		//equipment = new EquipItem(value);
		//equipment = new EquipItem::ItemInfo;
		break;
	}
	SCENE_MGR.GetCurrScene()->RemoveGo(this);
}
