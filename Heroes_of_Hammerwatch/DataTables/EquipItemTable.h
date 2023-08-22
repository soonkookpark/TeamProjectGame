#pragma once
#include"DataTable.h"
#include"EquipItem.h"
class EquipItemTable : public DataTable
{
private:
	std::map<int,EquipItem::ItemInfo> equipItemTables;
public:
	EquipItemTable();
	virtual bool Load() override;
	virtual void Release() override;
	EquipItem::ItemInfo& Get(int id) { return equipItemTables[id]; }
};