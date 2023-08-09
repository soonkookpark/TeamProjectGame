#pragma once
#include "Player.h"
class Paladin :	public Player
{
private:
public:
	Paladin();
	virtual ~Paladin() override { Release(); }


};

