#pragma once
class Creature;
class Skill
{
public:
    enum class SKillType
    {
        NONE = -1,
        MELEE_ATTACK,
        RANGE_ATTACK,
        BUFF,
        PASSIVE,
        COUNT,
    };
    enum class TargetType
    {
        NONE = -1,
        SELF,
        ALLY,
        ENEMY,
        COUNT,
    };
protected:
    Creature* owner = nullptr;
    float range = 0.f;

    TargetType targetType = TargetType::NONE;
    std::list<Creature*> targets;
public:
    Skill(const std::string& name, Creature* owner);
    virtual void Init();
    virtual void Reset();
    virtual void Update(float dt);

    virtual void SetData(const std::string& key) = 0;
    
    virtual void SetTarget();
    virtual void Active();
    virtual void Effect() = 0;
};

