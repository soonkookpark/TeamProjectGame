#include "stdafx.h"
#include "FieldItemTable.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"
#include "Items/FieldItem.h"

bool FieldItemTable::Load()
{
    rapidcsv::Document doc("tables/itemTables/FieldItemTable.csv");

    for (int i = 0; doc.GetRowCount() > i; i++)
    {
        tables.insert({ doc.GetCell<std::string>(0,i),
            {
                doc.GetCell<int>(1,i),
                doc.GetCell<int>(2,i)                
            }
            });
        RESOURCE_MGR.LoadTextureRect(
            doc.GetCell<std::string>(0, i),
            doc.GetCell<std::string>(3, i),
            doc.GetCell<int>(4, i),
            doc.GetCell<int>(5, i),
            doc.GetCell<int>(6, i),
            doc.GetCell<int>(7, i));
    }


    return ;
}

void FieldItemTable::Release()
{
}
