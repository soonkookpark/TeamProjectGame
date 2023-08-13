#pragma once
#include "GameObject.h"

class Creature;

class Skill
{
public:
    enum class SkillType
    {
        None = -1,
        MELEE_ATTACK,
        RANGE_ATTACK,
        COUNT,
    };
    enum class TargetType
    {
        None = 01,
        SELF,
        ALLY,
        ENEMY,
        COUNT,
    };

    struct SkillInfo
    {
        std::string Using_Class;
        std::string Skill_Name;
        std::string Skill_Type;
        int Learning_Tier;
        int Star_Cost;
        int Star_Cost_Up;
        float Skill_CoolTime;
        int Cost_Mana;
        int Cost_Mana_Per_Tier;
        std::string Skill_Explain;
        std::string Skill_Image; // 불러오는 방식
        float Charge_Length;
        float Charge_Length_Per_Tier;
        int Heal;
        int Heal_Per_Tier;
        float Duration;
        float Duration_Per_Tier;
        int Skill_Arc_Range;
        int Skill_Arc_Range_Per_Tier;
        int Reduce_Magic_Damage;
        int Reduce_Magic_Damage_Per_Tier;
        int Reduce_Physics_Damage;
        int Reduce_Physics_Damage_Per_Tier;
        int Rate;
        int Rate_Per_Tier;
        int Stack;
        int Stack_Per_Tier;

    };
protected:
    Creature* owner = nullptr;
    float range = 0.f;
    TargetType targetType = TargetType::None;
    std::vector<Creature*> targets;
public:
    Skill(const std::string& name);
  
    virtual void Init() ;
    virtual void Reset() ;
    virtual void Update(float dt) ;
    
    virtual void SetData(const std::string& key) = 0;
    virtual void SetOwner(Creature* owner) { this->owner = owner; };

    void SetTarget();
    virtual void Active();
    virtual void Effect() = 0;
};

