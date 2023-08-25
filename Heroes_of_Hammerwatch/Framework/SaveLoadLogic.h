#pragma once
#include "Singleton.h"
#include "Player.h"
#include "Inventory.h"


struct SaveData {
	//�κ��丮�� �÷��̾��� ������ ��ƿͼ� ���� ����ü�� ���� ����
	Player::PlayerInfo playerData
};

class SaveLoadLogic : public Singleton<SaveLoadLogic>
{
	friend Singleton<SaveLoadLogic>;

protected:
	SaveData gameData;
public:
	SaveLoadLogic() = default;
	~SaveLoadLogic() = default;
	void SaveGameData();
	void LoadGameData();
};

#define SAVELOAD_MGR (SaveLoadLogic::GetInstance())
