#include "stdafx.h"
#include "Buff.h"
#include "Creature.h"

Buff::Buff(const std::string& key, Creature* owner, Creature* provider, float range)
	:type(Buff::AURA),provider(provider), range(range),owner(owner)
{
	SetData(key);	
	GetBuff();
}

Buff::Buff(const std::string& key, Creature* owner, float duration)
	:type(Buff::NONE_AURA), duration(duration), owner(owner)
{
	SetData(key);
	GetBuff();
}

void Buff::Update(float dt)
{
	if (type == NONE_AURA)
		timer += dt;

	DuringBuff(dt);

	if (!CheckPersistan(dt))
		LoseBuff();
}

bool Buff::CheckPersistan(float dt)
{
	switch (type)
	{
	case Buff::AURA:
		return Utils::CircleToRect(provider->GetPosition(), range, owner->sprite.getGlobalBounds());		
	case Buff::NONE_AURA:
		timer += dt;
		return timer < duration;
		break;
	}
}

void Buff::DuringBuff(float dt)
{

}

void Buff::LoseBuff()
{
	owner->LoseBuff(this);
}