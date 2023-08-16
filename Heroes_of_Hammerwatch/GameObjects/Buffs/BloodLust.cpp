#include "stdafx.h"
#include "BloodLust.h"
#include "Creature.h"

BloodLust::BloodLust(Creature* owner, Creature* provider, float range)
    :Buff("BloodLust", owner, provider, range)
{
    GetBuff();
}

BloodLust::BloodLust(Creature* owner, float duration)
    :Buff("BloodLust", owner, duration)
{
}

void BloodLust::SetData(const std::string& key)
{
}

void BloodLust::GetBuff()
{
	Buff::GetBuff();
    owner->sprite.setColor({ 255U,125U,125U });
    owner->ControlCreatureInfos()->speed *= param;
}

void BloodLust::DuringBuff(float dt)
{
	Buff::DuringBuff(dt);
}

void BloodLust::LoseBuff()
{
	Buff::LoseBuff();
    owner->sprite.setColor({ 255U,255U,255U });
    owner->ControlCreatureInfos()->speed /= param;
}
