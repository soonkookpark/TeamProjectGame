#include "stdafx.h"
#include "TextGo.h"
#include "Utils.h"
#include "ResourceMgr.h"

TextGo::TextGo(const std::string rId, const std::string n)
	: GameObject(n), resourceId(rId)
{
}

TextGo::~TextGo()
{
}

void TextGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	text.setPosition(p);
}

void TextGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	text.setPosition(position);
}

void TextGo::SetOrigin(Origins origin)
{
	Utils::SetOrigin(text, origin);

	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(text, origin);
	}
}

void TextGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	text.setOrigin(x, y);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
	auto font = RESOURCE_MGR.GetFont(resourceId);
	if (font != nullptr)
	{
		text.setFont(*font);
	}
}

void TextGo::Update(float dt)
{
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
