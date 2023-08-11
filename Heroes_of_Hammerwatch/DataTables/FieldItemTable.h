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
    // DataTable��(��) ���� ��ӵ�
    virtual bool Load() override;
    virtual void Release() override;

    std::vector<int> Get(const std::string key) { return tables[key]; }
};

