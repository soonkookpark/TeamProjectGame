#pragma once

class Creature;
class Buff
{
public:
	enum ClassBuffType
	{
		AURA,
		NONE_AURA,
	};
protected:
	Creature* owner;
	ClassBuffType type;

	Creature* provider;
	float range;

	float duration = 0;
	float timer = 0;
public:
	Buff(const std::string& key, Creature* owner, Creature* provider, float range);
	Buff(const std::string& key, Creature* owner, float duration);
	virtual ~Buff() {};

	virtual void Update(float dt);

	virtual bool CheckPersistan(float dt);

	virtual void SetData(const std::string& key) {};

	virtual void GetBuff() {};
	virtual void DuringBuff(float dt);
	virtual void LoseBuff();

};

