#include "stdafx.h"
#include "Paladin.h"
#include "ResourceMgr.h"
#include "MeleeAttack.h"
#include "SceneMgr.h"

Paladin::Paladin()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveDR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleDR.csv"));

	//skills.insert({ "",(Skill*) SCENE_MGR.GetCurrScene()->AddGo(new MeleeAttack("sdfg")) });
	animation.SetTarget(&sprite);
	SetData("Paladin");
}

