#pragma once
#include "DataTable.h"
#include "Skill.h"
class SkillDataTable :
    public DataTable
{
protected:
    std::unordered_map<std::string, Skill::SkillInfo> sTables;
public:
    SkillDataTable();
    virtual bool Load() override;
    virtual void Release() override;

    Skill::SkillInfo& Get(std::string key) { return sTables[key]; };
};

