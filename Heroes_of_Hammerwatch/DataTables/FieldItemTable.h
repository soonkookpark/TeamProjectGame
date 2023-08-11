#pragma once
#include "DataTable.h"
class FieldItemTable :
    public DataTable
{
protected:
    std::map<std::string,std::vector<int>> tables;
public:
    FieldItemTable() : DataTable(DataTable::Ids::FieldItem) {};
    virtual ~FieldItemTable() = default;
    // DataTable을(를) 통해 상속됨
    virtual bool Load() override;
    virtual void Release() override;

    std::vector<int> Get(const std::string key) { return tables[key]; }
};

