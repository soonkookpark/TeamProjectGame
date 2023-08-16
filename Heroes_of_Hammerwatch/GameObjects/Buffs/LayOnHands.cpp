#include "stdafx.h"
#include "LayOnHands.h"


LayOnHands::LayOnHands(Creature* provider, float range)
    :Buff("LayOnHands", provider, range)
{
}

LayOnHands::LayOnHands(float duration)
    :Buff("LayOnHands", duration)
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
