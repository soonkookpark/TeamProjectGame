#include "stdafx.h"
#include "EffectText.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

EffectText::EffectText(const std::string& text, sf::Vector2f pos, sf::Color color)
	:TextGo("","")
{
	this->text.setFont(*ResourceMgr::Instance().GetFont("fonts/arialuni.ttf"));
	this->text.setFillColor(color);
	this->text.setCharacterSize(8);
	this->text.setString(text);
	SetPosition(pos + Utils::RandomInCircle(5.f));
	sortLayer = SortLayer::EFFECT_TEXT;
}

void EffectText::Update(float dt)
{
	timer += dt;
	SetPosition(position + sf::Vector2f(0.f, -1.f) * 20.f * dt);
	if (timer > 2.f)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
	}
}
