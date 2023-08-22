#pragma once
#include "Projectile.h"
class Arrow :
    public Projectile
{
public:
    Arrow();
    virtual ~Arrow() = default;


    virtual bool CheckIsCollied(Creature* target) override;
    virtual void Effect(Creature* target) override;
};

