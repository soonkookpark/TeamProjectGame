#include "stdafx.h"
#include "EquipItemTable.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"

EquipItemTable::EquipItemTable() :DataTable(DataTable::Ids::EquipItem)
{
}

bool EquipItemTable::Load()
{
	rapidcsv::Document doc("tables/itemTables/EquipItemTable.csv");
	for (int i = 0; doc.GetRowCount() > i; i++)
	{
		equipItemTables.insert
		(
			{ doc.GetCell<int>(1,i),
				
				{
					doc.GetCell<std::string>(0,i),
					//doc.GetCell<int>(1,i),
					doc.GetCell<int>(2,i),
					doc.GetCell<std::string>(3,i),
					doc.GetCell<int>(4,i),
					doc.GetCell<int>(5,i),
					doc.GetCell<int>(6,i),
					doc.GetCell<int>(7,i),
					doc.GetCell<int>(8,i)
				}
			}
		);
		RESOURCE_MGR.LoadTextureRect(
			doc.GetCell<std::string>(0, i),
			doc.GetCell<std::string>(9,i),
			doc.GetCell<int>(10, i),
			doc.GetCell<int>(11, i),
			doc.GetCell<int>(12, i),
			doc.GetCell<int>(13, i),
			true);
	}



	return true;
}

void EquipItemTable::Release()
{
}
