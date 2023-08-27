#include "stdafx.h"
#include "EliteTick.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "DataTableMgr.h"
#include "EliteMonsterTable.h"
#include "BuffToOther.h"

EliteTick::EliteTick()
	:Monster("EliteTick")
{	
	SetData("EliteTick");
}

void EliteTick::Update(float dt)
{
	Monster::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F))
	{
		SummonTicks();
	}
}

void EliteTick::SetData(const std::string& name)
{
	Monster::SetData(name);
	EliteMonsterTable* dataTable = DATATABLE_MGR.Get<EliteMonsterTable>(DataTable::Ids::EliteMonster);
	std::unordered_map<std::string, float> EliteTickTable = dataTable->Get(name);
	spawnRange = EliteTickTable["spawnRange"];
	skillFrequency = EliteTickTable["skillFrequency"];
	buffRange = EliteTickTable["buffRange"];
	textureId = "graphics/Test/testElite.png";
	skills.insert({ "Buff",new BuffToOther("test",this) });
	creatureInfo.speed = 0;
}

void EliteTick::Chase(float dt)
{
	Monster::Chase(dt);
	
	//Buff();
	timer += dt;
	if (timer > skillFrequency)
	{
		timer = 0;
		SummonTicks();
	}
}

void EliteTick::SummonTicks()
{	
	Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x + spawnRange, position.y + spawnRange);
	mob->Reset();
	mob->SetTileMap(tileMap);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x - spawnRange, position.y + spawnRange);
	mob->Reset();
	mob->SetTileMap(tileMap);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x + spawnRange, position.y - spawnRange);
	mob->Reset();
	mob->SetTileMap(tileMap);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x - spawnRange, position.y - spawnRange);
	mob->Reset();
	mob->SetTileMap(tileMap);
}
/*
void EliteTick::Buff()
{
	std::list<GameObject*> mobs;
	SCENE_MGR.GetCurrScene()->FindGos(mobs, "mob");
	for (auto mob : mobs)
	{

		if (Utils::Distance(mob->GetPosition(), position) < buffRange)
		{
			if (!dynamic_cast<Monster*>(mob)->GetIsBuffed())
			{
				dynamic_cast<Monster*>(mob)->GetBuff();
			}
		}
		else
		{
			if (dynamic_cast<Monster*>(mob)->GetIsBuffed())
			{
				dynamic_cast<Monster*>(mob)->LoseBuff();
			}
		}
	}
}
*/