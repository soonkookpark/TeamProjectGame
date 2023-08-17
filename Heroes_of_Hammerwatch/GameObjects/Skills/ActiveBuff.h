#pragma once
#include "ActiveSkill.h"

class Buff;
class ActiveBuff :
    public ActiveSkill
{
protected:
    std::function<Buff* (Creature*)> MakeBuff;
public:
    ActiveBuff(const std::string& key, Creature* owner);
    virtual ~ActiveBuff() = default;

    virtual void SetData(const std::string& key) override;

    virtual void Effect() override;
};

