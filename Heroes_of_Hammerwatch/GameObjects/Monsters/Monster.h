#pragma once
#include "Creature.h"
#include "Player.h"

class Astar;

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
        KITING,
        DIE,
        COUNT,
    };
    struct MonsterParameters
    {
        float damage = 0;
        bool isMelee = true;
        bool isFlying = false;
        float searchRange = 0;
        float moveFrequency = 0;
        float moveRange = 0;
        float attackRange = 0;
        Monster::MonsterType monsterType;
    };
protected:
    MonsterParameters monsterParameter;

    State state = State::DEFAULT;
    sf::Vector2f originalPos;
    sf::Vector2f dir;
    std::vector<std::string> strArr;
    Player* player = nullptr;
    sf::Vector2f destination;
    sf::Vector2f surround;
    float findAngle = 0.f;
    bool isBuffed;
    float timer = 0.f;
    float convertRange = 175.f;
    bool inAction;
    sf::RectangleShape nextTile;
    sf::RectangleShape box;
    
    sf::RectangleShape testTiles[8];
    sf::RectangleShape testIntersect;

    Astar* pathFinder;
    std::stack<sf::Vector2i>* chasePath;
public:
    Monster(const std::string& type, const std::string& name = "mob", sf::Vector2f pos = {});
    virtual ~Monster() = default;

    virtual void Init();
    virtual void Release() {};
    virtual void Reset();	// √ ±‚»≠
    virtual void Update(float dt);
    virtual void Draw(sf::RenderWindow& window) override;

    virtual void SetData(const std::string& name);

    virtual void Wander(float dt);
    virtual void Attack(float dt);
    virtual void Chase(float dt);
    virtual void Kiting(float dt);
    virtual void Default(float dt);
    virtual void Die(float dt);

    virtual void SetDead() override;

    //virtual bool CheckStraight();
    virtual void FindDestination();
    virtual void Move(float dt, sf::Vector2f pos);
    void Collider(int x, int y);
        
    bool DetectTarget();
    bool GetIsBuffed() { return isBuffed; };

    virtual void IdleAnimationPrint(SightDegree lookat) override;
    virtual void MoveAnimationPrint(SightDegree lookat) override;
    virtual void AttackAnimationPrint(SightDegree lookat) override;

};

