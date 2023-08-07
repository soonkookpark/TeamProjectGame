#include "stdafx.h"
#include "MonsterTable.h"
#include "rapidcsv.h"

bool MonsterTable::Load()
{
    rapidcsv::Document doc("tables/MonsterTables/MonsterDataTable.csv");
        
    for (int i = 0; doc.GetColumnCount() > i; i++)
    {
        tables.insert({ doc.GetCell<std::string>(i,1),
            {
                doc.GetCell<int>(i,2),
                doc.GetCell<float>(i,3),
                doc.GetCell<float>(i,4),
                doc.GetCell<float>(i,5),
                static_cast<AttackType>(doc.GetCell<int>(i,6)),
                doc.GetCell<float>(i,7),
                static_cast<bool>(doc.GetCell<int>(i,8)),
                static_cast<bool>(doc.GetCell<int>(i,9)),
                doc.GetCell<float>(i,10),
                doc.GetCell<float>(i,11),
                doc.GetCell<float>(i,12),
                doc.GetCell<float>(i,13),
                doc.GetCell<float>(i,14),
                doc.GetCell<float>(i,15),
                doc.GetCell<int>(i,16),
                doc.GetCell<float>(i,17),
                static_cast<Monster::MonsterType>(doc.GetCell<int>(i,18))
            }
            });        
    }
    return true;
}

MonsterTable::MonsterTable()
    :DataTable(Ids::Monster)
{
}

void MonsterTable::Release()
{
    tables.clear();
}

