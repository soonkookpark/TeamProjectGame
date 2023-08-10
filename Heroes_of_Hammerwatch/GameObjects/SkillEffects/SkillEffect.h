#pragma once
#include "SpriteGo.h"
class SkillEffect :
    public GameObject
{
protected:
    float phisicalDamage;
    float magicalDamage;

    std::vector<GameObject*> targets;
public:
    SkillEffect(const std::string& key);
    virtual ~SkillEffect() = default;

    void SetDatas(const std::string& key);

    //virtual void Update(float dt);

    virtual bool CheckIntersected() = 0;
};