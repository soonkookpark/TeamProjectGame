#pragma once
#include "DataTable.h"
#include "Monster.h"

class MonsterTable :
    public DataTable
{
public:
    struct MonsterTableInfo
    {
        Creature::CreatureInfo CI;
        Monster::MonsterParameters MI;
    };
protected:    
    std::unordered_map<std::string, MonsterTableInfo> tables;
public:
    MonsterTable();
    virtual bool Load() override;
    virtual void Release() override;

    MonsterTableInfo& Get(std::string key) { return tables[key]; };
};

