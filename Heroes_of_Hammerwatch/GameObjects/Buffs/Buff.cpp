#include "stdafx.h"
#include "Buff.h"
#include "Creature.h"

Buff::Buff(const std::string& key, Creature& owner, ClassBuffType type)
	:owner(owner), type(type)
{
	SetData(key);
}

void Buff::Update(float dt)
{
	DuringBuff(dt);

	if (!CheckPersistan(dt))
		LoseBuff();
}

bool Buff::CheckPersistan(float dt)
{
	switch (type)
	{
	case Buff::AURA:
		return Utils::CircleToRect(provider->GetPosition(), range, owner.sprite.getGlobalBounds());		
	case Buff::NONE_AURA:
		timer += dt;
		return timer < duration;
		break;
	}
}

void Buff::GetBuff()
{
	owner.GainBuff(this);
}

void Buff::DuringBuff(float dt)
{

}

void Buff::LoseBuff()
{
	owner.LoseBuff(this);
	delete(this);
}
