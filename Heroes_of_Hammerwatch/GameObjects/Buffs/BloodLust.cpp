#include "stdafx.h"
#include "BloodLust.h"

BloodLust::BloodLust(Creature& owner, Creature* provider, float range)
    :Buff("LayOnHands", owner, Buff::AURA)
{
    this->provider = provider;
    this->range = range;
}

BloodLust::BloodLust(Creature& owner, float duration)
    :Buff("LayOnHands", owner, Buff::NONE_AURA)
{
    this->duration = duration;
}

void BloodLust::SetData(const std::string& key)
{
}

void BloodLust::GetBuff()
{
	Buff::GetBuff();
}

void BloodLust::DuringBuff(float dt)
{
	Buff::DuringBuff(dt);
}

void BloodLust::LoseBuff()
{
	Buff::LoseBuff();
}
