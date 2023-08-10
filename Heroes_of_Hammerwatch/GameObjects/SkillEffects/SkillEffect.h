#pragma once
#include "SpriteGo.h"
class SkillEffect :
    public SpriteGo
{
protected:
    float phisicalDamage;
    float magicalDamage;
public:
    SkillEffect(const std::string& key);
    virtual ~SkillEffect() = default;

    void SetDatas(const std::string& key);

    //virtual void Update(float dt);

    //virtual bool IsDamaged();
};