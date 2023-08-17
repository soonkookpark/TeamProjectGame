#pragma once

class Creature;
class Buff
{
public:
	enum ClassBuffType
	{
		NONE,
		AURA,
		NONE_AURA,
	};
	enum class KindOfBuff
	{
		BLOOD_LUST,
		LAY_ON_HANDS,
	};
protected:
	Creature* owner;
	ClassBuffType type = NONE;
	KindOfBuff kindOfBuff;

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

