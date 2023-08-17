#include "stdafx.h"
#include "Paladin.h"
#include "ResourceMgr.h"
#include "MeleeAttack.h"
#include "SceneMgr.h"

Paladin::Paladin()
{
	/*animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/MoveDR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/IdleDR.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Paladin/AttackDR.csv"));*/
	std::vector<std::string> loadString = Utils::LoadAnimationString("Paladin");
	for (const std::string& loadString : loadString)
	{
		creatureAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip(loadString));
	}

	creatureAnimation.SetTarget(&sprite);
	SetData("Paladin");
}

void Paladin::Update(float dt)
{
	Player::Update(dt);
}

void Paladin::SetData(const std::string& name)
{
	Player::SetData(name);
}

