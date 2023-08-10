#include "stdafx.h"
#include "EliteMonsterTable.h"
#include "rapidcsv.h"

EliteMonsterTable::EliteMonsterTable()
	:DataTable(Ids::EliteMonster)
{
}

bool EliteMonsterTable::Load()
{
	rapidcsv::Document doc("tables/MonsterTables/EliteMonsterTable.csv");

	int i = 0;
	while (i < doc.GetRowCount())
	{
		std::unordered_map<std::string, float> temp;
		for (int j = 1; j < doc.GetColumnCount(); j += 2)
		{
			if (doc.GetCell<std::string>(j, i) == " ")
				break;
			temp.insert({ doc.GetCell<std::string>(j, i) ,doc.GetCell<float>(j + 1, i) });
		}
		tables.insert({doc.GetCell<std::string>(0,i),temp});
		i++;
	}
    return true;
}

void EliteMonsterTable::Release()
{
}
