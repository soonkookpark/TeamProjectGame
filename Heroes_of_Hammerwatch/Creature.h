#pragma once
#include "SpriteGo.h"
class Creature :
    public SpriteGo
{
public:
    struct CreatureInfo
    {
        float maxHealth = 0;
        float armor = 0;
        float resistance = 0;
        float speed = 0;
        float physicalEvade = 0;
        float MagicalEvade = 0;
        float exp = 0;
    };
protected:
    float curHealth;
public:
    Creature(const std::string& textureId = "", const std::string& n = "")
        : SpriteGo(textureId, n) {};
    virtual ~Creature() { Release(); };

};

