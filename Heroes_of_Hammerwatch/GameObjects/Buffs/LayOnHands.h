#pragma once
#include "Buff.h"
class LayOnHands :
    public Buff
{
    LayOnHands(Creature* owner, Creature* provider, float range);
    LayOnHands(Creature* owner, float duration);
    virtual ~LayOnHands() override = default;
    // Buff��(��) ���� ��ӵ�
    virtual void SetData(const std::string& key) override;

    virtual void GetBuff() override;
    virtual void DuringBuff(float dt) override;
    virtual void LoseBuff() override;
};

