#include "stdafx.h"
#include "LayOnHands.h"


LayOnHands::LayOnHands(Creature* owner, Creature* provider, float range)
    :Buff("LayOnHands",owner, provider, range)
{
}

LayOnHands::LayOnHands(Creature* owner, float duration)
    :Buff("LayOnHands",owner, duration)
{
}

void LayOnHands::SetData(const std::string& key)
{
}

void LayOnHands::GetBuff()
{
    Buff::GetBuff();
}

void LayOnHands::DuringBuff(float dt)
{
    Buff::DuringBuff(dt);
}

void LayOnHands::LoseBuff()
{
    Buff::LoseBuff();
}
