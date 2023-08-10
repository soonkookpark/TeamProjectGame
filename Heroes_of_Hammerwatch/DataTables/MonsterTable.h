#pragma once
#include "DataTable.h"
#include "Monster.h"

class MonsterTable :
    public DataTable
{
public:
protected:    
    std::unordered_map<std::string, Monster::MonsterParameters> tables;
public:
    MonsterTable();
    virtual bool Load() override;
    virtual void Release() override;

    Monster::MonsterParameters& Get(std::string key) { return tables[key]; };
};

