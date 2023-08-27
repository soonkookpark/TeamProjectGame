#include "stdafx.h"
#include "SaveLoadLogic.h"
#include <iostream>
#include <fstream>

void SaveLoadLogic::SaveGameData()
{
}

void SaveLoadLogic::LoadGameData()
{
    SaveData data = GetData(player, inven);  // Assuming player and inven are class members

    // CSV 파일 이름 설정
    std::string filename = "saved_data.csv";

    // 파일을 쓰기 모드로 열기
    std::ofstream outFile(filename);

    if (outFile.is_open())
    {
        // 데이터를 CSV 형식으로 파일에 쓰기
        outFile << "PlayerName,PlayerLevel,CreatureType,CreatureLevel,ItemName,ItemQuantity\n";
        outFile << data.playerData->ClassName <<"\n";

        // 파일 닫기
        outFile.close();
        std::cout << "데이터가 성공적으로 저장되었습니다." << std::endl;
    }
    else
    {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
    }
}

SaveData SaveLoadLogic::GetData(Player* player, Inventory* inventory)
{
	SaveData data;
	data.playerData = player->ControlPlayerInfos();
	data.creatureData = player->ControlCreatureInfos();
	data.itemData = inventory->getInventoryInfo();

	return SaveData();
}
