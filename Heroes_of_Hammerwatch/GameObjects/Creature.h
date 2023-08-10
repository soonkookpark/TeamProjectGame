#pragma once
#include "SpriteGo.h"
class Creature :
    public SpriteGo
{
public:
    struct CreatureInfo
    {
        float maxHealth = 0.f;
        float armor = 0.f;
        float resistance = 0.f;
        float speed = 0.f;
        float physicalEvade = 0.f;
        float MagicalEvade = 0.f;
        float exp = 0.f;
    };
protected:
    float curHealth = 0.f;
    SightDegree lookat = SightDegree::R;
    std::map<std::string, std::function<void(Creature*)>> skills;
public:
    Creature(const std::string& textureId = "", const std::string& n = "")
        : SpriteGo(textureId, n) {};
    virtual ~Creature() { Release(); };

    virtual void Damaged(float physicalDmg, float magicalDmg) = 0;
};

