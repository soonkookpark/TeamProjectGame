#pragma once
#include "DataTable.h"
#include "Player.h"
class PlayerTable :public DataTable
{
public:
    struct PlayerTableInfos
    {
        Creature::CreatureInfo CI;
        Player::PlayerInfo PI;
    };
protected:
    std::unordered_map<std::string, PlayerTableInfos> pTables;
public:
    PlayerTable();
    virtual bool Load() override;
    virtual void Release() override;

    PlayerTableInfos& Get(std::string key) { return pTables[key]; };
};

