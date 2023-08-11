#pragma once
#include "Creature.h"
#include "Player.h"


class Monster :
    public Creature
{
public:
    enum class MonsterType
    {
        NONE = -1,
        BEATST,
        UNDEAD,
        STRUCTURE,
        COUNT,
    };
    enum class State
    {
        NONE = -1,
        DEFAULT,
        WANDER,
        CHASE,
        ATTACK,
        DIE,
        COUNT,
    };
    struct MonsterParameters
    {
        CreatureInfo creatureInfo;
        //int exp = 0;
        //float maxHealth = 0;
        //float armor = 0;
        //float resistance = 0;
        //AttackType attackType;
        float damage = 0;
        bool isMelee = true;
        bool isFlying = false;
        float searchRange = 0;
        float moveFrequency = 0;
        float moveRange = 0;
        //float physicalEvade = 0;
        //float MagicalEvade = 0;
        //float speed = 0;
        //int attackArc = 0;
        float attackRange = 0;
        Monster::MonsterType monsterType;
    };
protected:
    MonsterParameters param;

    State state = State::DEFAULT;
    sf::Vector2f originalPos;
    sf::Vector2f dir;

    Player* player = nullptr;
    sf::Vector2f destination;
    bool isBuffed;
    float timer;
    bool inAction;
public:
    Monster(const std::string& type, const std::string& name = "mob");
    virtual ~Monster() = default;

    virtual void Init();
    virtual void Release() {};
    virtual void Reset();	// √ ±‚»≠
    virtual void Update(float dt);

    virtual void SetData(const std::string& name);

    virtual void Wander(float dt);
    virtual void Attack(float dt);
    virtual void Chase(float dt);
    virtual void Default(float dt);
    virtual void Die(float dt);

    virtual void Damaged(float physicalDmg, float magicalDmg);
        
    bool DetectTarget();
    bool GetIsBuffed() { return isBuffed; };
    /*
    void GetBuff();
    void LoseBuff();

    bool meleeAttack();
    */
};

