#pragma once
#include "Buff.h"
class LayOnHands :
    public Buff
{
    LayOnHands(Creature* provider, float range);
    LayOnHands(float duration);
    virtual ~LayOnHands() override = default;
    // Buff을(를) 통해 상속됨
    virtual void SetData(const std::string& key) override;

    virtual void GetBuff() override;
    virtual void DuringBuff(float dt) override;
    virtual void LoseBuff() override;
};

