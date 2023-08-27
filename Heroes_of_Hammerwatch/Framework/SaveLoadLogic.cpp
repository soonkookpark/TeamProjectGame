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

    // CSV ���� �̸� ����
    std::string filename = "saved_data.csv";

    // ������ ���� ���� ����
    std::ofstream outFile(filename);

    if (outFile.is_open())
    {
        // �����͸� CSV �������� ���Ͽ� ����
        outFile << "PlayerName,PlayerLevel,CreatureType,CreatureLevel,ItemName,ItemQuantity\n";
        outFile << data.playerData->ClassName <<"\n";

        // ���� �ݱ�
        outFile.close();
        std::cout << "�����Ͱ� ���������� ����Ǿ����ϴ�." << std::endl;
    }
    else
    {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
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
