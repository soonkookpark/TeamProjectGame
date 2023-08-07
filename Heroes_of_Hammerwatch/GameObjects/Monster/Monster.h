#pragma once
#include "SpriteGo.h"
#include "Player.h"

class MonsterTable;

class Monster :
    public SpriteGo
{
public:
    enum class MonsterType
    {
        NONE = -1,
        BEATST,
        UNDEAD,
        BOSS,
        COUNT,
    };
    enum class State
    {
        NONE = -1,
        DEFAULT,
        WANDER,
        CHASE,
        ATTACK,
        COUNT,
    };
protected:
    std::string name;
    MonsterType monsterType = MonsterType::NONE;
    int exp = 0;

    State state = State::DEFAULT;
    sf::Vector2f originalPos;
    float moveRange = 0;
    float moveFrequency = 0;

    float maxHealth = 0;
    float curHealth = 0;
    float armor = 0;
    float resistance = 0;
    AttackType attackType;
    float damage = 0;
    float searchRange = 0;
    float physicalEvade = 0;
    float MagicalEvade = 0;

    sf::Vector2f dir;
    float speed = 0;

    bool isFlying = false;
    bool isMelee = true;

    float attackRange = 0;
    int attackArc = 0;

    Player* player = nullptr;
    sf::Vector2f destination;
    bool isBuffed;
    float timer;

public:
    Monster(const std::string& type, const std::string& name = "mob");
    virtual ~Monster() = default;

    virtual void Init();
    virtual void Release() {};
    virtual void Reset();	// √ ±‚»≠
    virtual void Update(float dt);

    void SetDatas(const std::string& name);

    virtual void Wander(float dt);
    virtual void Attack(float dt);
    virtual void Chase(float dt);
    virtual void Default(float dt);
        
    bool DetectTarget();
    bool GetIsBuffed() { return isBuffed; };

    void GetBuff();
    void LoseBuff();
};

