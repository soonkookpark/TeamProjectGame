#pragma once
#include "Singleton.h"
#include "Player.h"
#include "Inventory.h"



struct SaveData {
	//인벤토리와 플레이어의 정보를 담아와서 여기 구조체에 각각 저장
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
