#include "stdafx.h"
#include "LayOnHands.h"
#include "Creature.h"



LayOnHands::LayOnHands(Creature* owner, Creature* provider, float range)
    :Buff("LayOnHands",owner, provider, range)
{
    kindOfBuff = KindOfBuff::LAY_ON_HANDS;
    GetBuff();
}

LayOnHands::LayOnHands(Creature* owner, float duration)
    :Buff("LayOnHands",owner, duration)
{
    kindOfBuff = KindOfBuff::LAY_ON_HANDS;
    GetBuff();
}

void LayOnHands::SetData(const std::string& key)
{
    healValue = 1;
}

void LayOnHands::GetBuff()
{
    Buff::GetBuff();
}

void LayOnHands::DuringBuff(float dt)
{
    Buff::DuringBuff(dt);
    owner->HealHP(1 + healValue + (owner->ControlCreatureInfos()->maxHealth * 0.02));
}

void LayOnHands::LoseBuff()
{
    Buff::LoseBuff();
}
