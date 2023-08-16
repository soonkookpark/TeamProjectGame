#pragma once
#include "Buff.h"
class BloodLust :
    public Buff
{
protected:
    float param = 1.2f;
public:
    BloodLust(Creature* owner, Creature* provider, float range);
    BloodLust(Creature* owner, float duration);
    ~BloodLust() override = default;
    // Buff을(를) 통해 상속됨
    virtual void SetData(const std::string& key) override;

    virtual void GetBuff() override;
    virtual void DuringBuff(float dt) override;
    virtual void LoseBuff() override;
};

