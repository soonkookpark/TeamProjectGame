#include "stdafx.h"
#include "MonsterTable.h"
#include "rapidcsv.h"

bool MonsterTable::Load()
{
    rapidcsv::Document doc("tables/MonsterTables/MonsterDataTable.csv");
        
    for (int i = 0; doc.GetRowCount() > i; i++)
    {
        tables.insert({ doc.GetCell<std::string>(0,i),
            {
                doc.GetCell<int>(1,i),
                doc.GetCell<float>(2,i),
                doc.GetCell<float>(3,i),
                doc.GetCell<float>(4,i),
                static_cast<AttackType>(doc.GetCell<int>(5,i)),
                doc.GetCell<float>(6,i),
                static_cast<bool>(doc.GetCell<int>(7,i)),
                static_cast<bool>(doc.GetCell<int>(8,i)),
                doc.GetCell<float>(9,i),
                doc.GetCell<float>(10,i),
                doc.GetCell<float>(11,i),
                doc.GetCell<float>(12,i),
                doc.GetCell<float>(13,i),
                doc.GetCell<float>(14,i),
                doc.GetCell<int>(15,i),
                doc.GetCell<float>(16,i),
                static_cast<Monster::MonsterType>(doc.GetCell<int>(17,i))
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

