#include "stdafx.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "MonsterTable.h"
#include "EliteMonsterTable.h"
#include "PlayerTable.h"
#include "FieldItemTable.h"
#include "SkillDataTable.h"
#include "EquipItemTable.h"

void DataTableMgr::LoadAll()
{
	tables.insert({ DataTable::Ids::String, new StringTable() });
	tables.insert({ DataTable::Ids::Monster, new MonsterTable() });
	tables.insert({ DataTable::Ids::EliteMonster, new EliteMonsterTable() });
	tables.insert({ DataTable::Ids::PlayerClass, new PlayerTable() });
	tables.insert({ DataTable::Ids::FieldItem, new FieldItemTable() });
	tables.insert({ DataTable::Ids::SkillData, new SkillDataTable() });
	tables.insert({ DataTable::Ids::EquipItem, new EquipItemTable() });
	for (auto pair : tables)
	{
		if (!pair.second->Load())
		{
			std::cout << "ERR: DATA TABLE LOAD FAIL" << std::endl;
			exit(-1);
		}
	}
}

void DataTableMgr::ReleaseAll()
{
	for (auto pair : tables)
	{
		//pair.second->Release();
		delete pair.second;
	}
	tables.clear();
}
