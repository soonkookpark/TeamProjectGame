#include "stdafx.h"
#include "SkillDataTable.h"
#include "rapidcsv.h"

SkillDataTable::SkillDataTable()
	:DataTable(Ids::SkillData)
{
}

bool SkillDataTable::Load()
{
	rapidcsv::Document doc("tables/PlayerTables/PlayerSkill.csv");

    for (int i = 0; (doc.GetRowCount()-1) > i; i++)
    {
        sTables.insert({ doc.GetCell<std::string>(1,i),
            {
                //string
                doc.GetCell<std::string>(1,i),
                doc.GetCell<std::string>(2,i),
                doc.GetCell<std::string>(3,i),
                doc.GetCell<std::string>(10,i),
                doc.GetCell<std::string>(11,i),
                //int
                doc.GetCell<int>(4,i),
                doc.GetCell<int>(5,i),
                doc.GetCell<int>(6,i),
                doc.GetCell<int>(8,i),
                doc.GetCell<int>(9,i),
                doc.GetCell<int>(14,i),
                doc.GetCell<int>(15,i),
                doc.GetCell<int>(18,i),
                doc.GetCell<int>(19,i),
                doc.GetCell<int>(20,i),
                doc.GetCell<int>(21,i),
                doc.GetCell<int>(22,i),
                doc.GetCell<int>(23,i),
                doc.GetCell<int>(24,i),
                doc.GetCell<int>(25,i),
                doc.GetCell<int>(26,i),
                doc.GetCell<int>(27,i),
                //float
                doc.GetCell<float>(7,i),
                doc.GetCell<float>(12,i),
                doc.GetCell<float>(13,i),
                doc.GetCell<float>(16,i),
                doc.GetCell<float>(17,i),
               
            }
            });
        std::cout << i << "¹ø ³¡!" << std::endl;
    }
    return true;

}

void SkillDataTable::Release()
{
    sTables.clear();
}
