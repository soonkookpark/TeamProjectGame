#pragma once
#include "DataTable.h"
#include "Player.h"
class PlayerTable :public DataTable
{
protected:
    std::unordered_map<std::string, Player::PlayerInfo> pTables;
public:
    PlayerTable();
    virtual bool Load() override;
    virtual void Release() override;

    Player::PlayerInfo& Get(std::string key) { return pTables[key]; };
};

