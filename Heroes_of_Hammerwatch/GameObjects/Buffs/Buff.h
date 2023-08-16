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
	Buff(const std::string& key, Creature* provider, float range);
	Buff(const std::string& key, float duration);
	virtual ~Buff() = default;

	virtual void Update(float dt);

	virtual bool CheckPersistan(float dt);

	virtual void SetData(const std::string& key) {};
	virtual void SetOwner() { this->owner = owner; }

	virtual void GetBuff();
	virtual void DuringBuff(float dt);
	virtual void LoseBuff();

};

