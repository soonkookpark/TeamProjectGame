#pragma once
#include "Singleton.h"
#include "Player.h"
#include "Inventory.h"



struct SaveData {
	//�κ��丮�� �÷��̾��� ������ ��ƿͼ� ���� ����ü�� ���� ����
	Player::PlayerInfo* playerData;
	Player::CreatureInfo* creatureData;
	Inventory::MyItemInfo* itemData;
};

class SaveLoadLogic : public Singleton<SaveLoadLogic>
{
	friend Singleton<SaveLoadLogic>;

protected:
	SaveData gameData;
	Player* player;
	Inventory* inven;
public:
	SaveLoadLogic() = default;
	~SaveLoadLogic() = default;
	void SaveGameData();
	void LoadGameData();
	SaveData GetData(Player* player, Inventory* inventory);
};

#define SAVELOAD_MGR (SaveLoadLogic::GetInstance())
