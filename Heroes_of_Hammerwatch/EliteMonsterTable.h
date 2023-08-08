#pragma once
#include "DataTable.h"
class EliteMonsterTable :
    public DataTable
{
protected:
    std::unordered_map<std::string,std::unordered_map<std::string, float>>tables;
public:
    // DataTable��(��) ���� ��ӵ�
    virtual bool Load() override;
    virtual void Release() override;

    std::unordered_map<std::string, float>& Get(std::string key) { return tables[key]; };
};

