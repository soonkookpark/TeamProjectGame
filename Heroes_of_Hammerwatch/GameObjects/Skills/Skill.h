#pragma once
#include "GameObject.h"
class Skill :
    public GameObject
{
protected:
public:
    Skill(const std::string& name) : GameObject(name) {};
    virtual ~Skill() { Release(); };
    // GameObject��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    virtual void Active() = 0;
};

