#pragma once
#include "Buff.h"
class BloodLust :
    public Buff
{
    BloodLust(Creature& owner, Creature* provider, float range);
    BloodLust(Creature& owner, float duration);
    ~BloodLust() override = default;
    // Buff��(��) ���� ��ӵ�
    virtual void SetData(const std::string& key) override;

    virtual void GetBuff() override;
    virtual void DuringBuff(float dt) override;
    virtual void LoseBuff() override;
};

