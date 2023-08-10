#include "stdafx.h"
#include "FieldItem.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "FieldItemTable.h"
#include "DataTableMgr.h"

FieldItem::FieldItem(const std::string& key)
	:SpriteGo("","FieldItem")
{
	SetDatas(key);
}

void FieldItem::SetDatas(const std::string& key)
{
	FieldItemTable* table = DATATABLE_MGR.Get<FieldItemTable>(DataTable::Ids::FieldItem);
	itemType = static_cast<ItemType>(table->Get(key)[0]);
	value = table->Get(key)[1];
	sprite.setTexture(*RESOURCE_MGR.GetTexture(key));	
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
		player->AcquireItem(value);
		break;
	}
	SCENE_MGR.GetCurrScene()->RemoveGo(this);
}
