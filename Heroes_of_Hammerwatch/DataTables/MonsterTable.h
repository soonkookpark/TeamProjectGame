#pragma once
#include "DataTable.h"
#include "Monster.h"

class MonsterTable :
    public DataTable
{
public:
    struct MonsterParameters
    {
        int exp = 0;
        float maxHealth = 0;
        float armor = 0;
        float resistance = 0;
        AttackType attackType;
        float damage = 0;
        bool isMelee = true;
        bool isFlying = false;
        float searchRange = 0;
        float moveFrequency = 0;
        float moveRange = 0;
        float physicalEvade = 0;
        float MagicalEvade = 0;
        float speed = 0;
        int attackArc = 0;
        float attackRange = 0;
        Monster::MonsterType monsterType;
    };
protected:
    std::unordered_map<std::string, MonsterParameters> tables;
public:
    MonsterTable();
    virtual bool Load() override;
    virtual void Release() override;

    MonsterParameters& Get(std::string key) { return tables[key]; };
};

