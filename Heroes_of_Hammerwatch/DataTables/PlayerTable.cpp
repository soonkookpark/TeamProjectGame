#include "stdafx.h"
#include "PlayerTable.h"
#include "rapidcsv.h"

bool PlayerTable::Load()
{
	rapidcsv::Document doc("tables/PlayerTables/PlayerStatus.csv");
    for (int i = 0; doc.GetRowCount() > i; i++)
    {
        pTables.insert({ doc.GetCell<std::string>(0,i),
            {
                {
                    doc.GetCell<float>(1,i),
                    doc.GetCell<float>(9,i),
                    doc.GetCell<float>(11,i),
                    doc.GetCell<float>(13,i),
                    doc.GetCell<float>(20,i),
                    doc.GetCell<float>(20,i),
                    doc.GetCell<float>(21,i),
                },
                doc.GetCell<std::string>(0,i),
                doc.GetCell<int>(2,i),
                doc.GetCell<int>(3,i),
                doc.GetCell<int>(4,i),
                doc.GetCell<float>(5,i),
                doc.GetCell<float>(6,i),
                doc.GetCell<float>(7,i),
                doc.GetCell<float>(8,i),
                doc.GetCell<float>(10,i),
                doc.GetCell<float>(12,i),
                doc.GetCell<float>(14,i),
                doc.GetCell<float>(15,i),
                doc.GetCell<float>(16,i),
                doc.GetCell<float>(17,i),
                doc.GetCell<float>(18,i),
                doc.GetCell<float>(19,i),
                doc.GetCell<float>(22,i),                
            }
            });
        std::cout << i << "¹ø ³¡!" << std::endl;
    }





	return true;
}
PlayerTable::PlayerTable()
	:DataTable(Ids::PlayerClass)
{

}


void PlayerTable::Release()
{
	pTables.clear();
}
