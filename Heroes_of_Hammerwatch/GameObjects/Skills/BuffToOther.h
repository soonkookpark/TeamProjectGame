#pragma once
#include "PassiveSkill.h"

class Buff;
class BuffToOther :
    public PassiveSkill
{
protected:
    std::list<Creature*> buffedTarget;
    std::list<Creature*> hadBuffedTarget;
public:
    BuffToOther(const std::string& key, Creature* owner);
    virtual ~BuffToOther() override = default;        

    void SetData(const std::string& key);

    void Update(float dt);


    virtual void Effect() override;
};

