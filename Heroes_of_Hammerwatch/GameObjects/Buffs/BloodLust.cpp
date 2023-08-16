#include "stdafx.h"
#include "BloodLust.h"
#include "Creature.h"

BloodLust::BloodLust(Creature* provider, float range)
    :Buff("BloodLust", provider, range)
{
}

BloodLust::BloodLust(float duration)
    :Buff("BloodLust", duration)
{
}

void BloodLust::SetData(const std::string& key)
{
}

void BloodLust::GetBuff()
{
	Buff::GetBuff();
    owner->sprite.setColor({ 255,125,125 });
    owner->ControlCreatureInfos()->speed *= param;
}

void BloodLust::DuringBuff(float dt)
{
	Buff::DuringBuff(dt);
}

void BloodLust::LoseBuff()
{
	Buff::LoseBuff();
    owner->sprite.setColor({ 255,255,255 });
    owner->ControlCreatureInfos()->speed /= param;
}
