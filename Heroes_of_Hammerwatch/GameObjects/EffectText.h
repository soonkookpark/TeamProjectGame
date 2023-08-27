#pragma once
#include "TextGo.h"
class EffectText :
    public TextGo
{
protected:
    float timer = 0.f;
public:
    EffectText(const std::string& text, sf::Vector2f pos, sf::Color color);
    virtual ~EffectText() =default;

    virtual void Update(float dt) override;
};

