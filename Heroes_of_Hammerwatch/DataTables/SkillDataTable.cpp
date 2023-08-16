#include "stdafx.h"
#include "SkillDataTable.h"
#include "rapidcsv.h"

SkillDataTable::SkillDataTable()
	:DataTable(Ids::SkillData)
{
}

bool SkillDataTable::Load()
{
    
	std::string filename("tables/PlayerTables/PlayerSkill.csv");
    rapidcsv::Document doc(filename);
    for (int i = 0; doc.GetRowCount() > i; i++)
    {
        sTables.insert(
            {
                {
                    //조건을 찾dmfusmsrj
                    doc.GetCell<std::string>(1,i),
                    doc.GetCell<std::string>(2,i),
                    doc.GetCell <int>(4,i),
                },
                {
                    doc.GetCell<std::string>(1,i),
                    doc.GetCell<std::string>(2,i),
                    static_cast<Skill::SKillType>(doc.GetCell<int>(3,i)),
                    doc.GetCell<int>(4,i),
                    doc.GetCell<int>(5,i),
                    doc.GetCell<float>(6,i),
                    doc.GetCell<std::string>(7,i),
                    doc.GetCell<std::string>(8,i),
                    doc.GetCell<float>(9,i),
                    doc.GetCell<int>(10,i),
                    doc.GetCell<float>(11,i),
                    doc.GetCell<int>(12,i),
                    doc.GetCell<int>(13,i),
                    doc.GetCell<int>(14,i),
                    doc.GetCell<int>(15,i),
                    doc.GetCell<int>(16,i),
                }
            });
       // std::cout << i << "번 끝!" << std::endl;
    }   
    return true;
}

void SkillDataTable::Release()
{
    //sTables.clear();
}
