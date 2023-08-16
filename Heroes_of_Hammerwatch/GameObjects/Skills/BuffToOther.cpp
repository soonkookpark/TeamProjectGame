#include "stdafx.h"
#include "BuffToOther.h"
#include "Buffs/AllBuffs.hpp"
#include "Utils.h"
#include "SceneMgr.h"
#include "AllCreutures.hpp"

void BuffToOther::SetData(const std::string& key)
{
	GiveThis = new BloodLust(owner, range);
}

void BuffToOther::Update(float dt)
{
	GiveBuff();
}

void BuffToOther::GiveBuff()
{
	for (auto target : targets)
	{		
		bool hasThis = false;
		for (auto checker : buffedTarget)
		{
			if (target == checker)
			{
				hasThis = true;
			}
		}
		if (!hasThis)
		{
			target->GainBuff(GiveThis);

			buffedTarget.push_back(target);
		}
	}
}