#pragma once
#include "SpriteGo.h"

class Skill;
class Buff;
class BuffToOther;

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
    CreatureInfo creatureInfo;
    float curHealth = 0.f;
    std::map<std::string, Skill*> skills;
    std::list <Buff*> buffs;
    std::list <Buff*> hadBuffs;
    SightDegree lookat = SightDegree::R;

    friend class Shield;
public:
    sf::Vector2f look;

    Creature(const std::string& textureId = "", const std::string& n = "");
    virtual ~Creature() { Release(); };

    virtual void Update(float dt) override;

    void SetData();

    void GainBuff(Buff* buff);
    void LoseBuff(Buff* buff);

    CreatureInfo* ControlCreatureInfos() { return &creatureInfo; }
    //BuffToOther* AccessSkill(const std::string& key) { return dynamic_cast<BuffToOther*>(skills[key]); }
    std::function<void(float physicalDmg, float magicalDmg, Creature* attacker)> Damaged;

    virtual void SetDead() = 0;
};

