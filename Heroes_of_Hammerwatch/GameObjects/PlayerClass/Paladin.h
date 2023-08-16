#pragma once
#include "Player.h"
class Paladin :	public Player
{
	
public:
	struct SkillInfo
	{

	};
protected:
public:
	Paladin();
	virtual ~Paladin() override { Release(); }
	
	virtual void Update(float dt);

	

	void SetData(const std::string& name);

};

