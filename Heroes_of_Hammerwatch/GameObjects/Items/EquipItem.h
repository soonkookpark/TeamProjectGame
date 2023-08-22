#pragma once
#include "SpriteGo.h"

class EquipItem : public SpriteGo
{
public:
	struct ItemInfo
	{
		std::string itemName;
		int setNum;
		std::string description;
		int hp;
		int attackPower;
		int speed;
		int defense;
		int resistance;
	};
protected:
	ItemInfo equipment;
	
public:
	EquipItem(int key);
	~EquipItem() = default;

	void SetData(int key);

	virtual void Reset() override;

	virtual void Update(float dt) override;
	
};

