#pragma once
#include "SpriteGo.h"

class Player;
class FieldItem :
    public SpriteGo
{
public:
    enum class ItemType
    {
        NONE = -1,
        HP_POTION,
        MP_POTION,
        MONEY,
        ORE,
        KEY,
        ITEM,
        COUNT,
    };
protected:
    Player* player;
    ItemType itemType = ItemType::NONE;
    int value;
    
public:
    FieldItem(const std::string& key);
    virtual ~FieldItem() = default;

    void SetData(const std::string& key);

    void Reset();

    void Update(float dt);

    void IntersectsWithItem();   
};
