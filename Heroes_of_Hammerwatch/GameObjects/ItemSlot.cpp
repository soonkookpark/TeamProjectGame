#include "stdafx.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot(const std::string& textureId, const std::string& n)
	: UIButton(textureId, n)
{
}

ItemSlot::~ItemSlot()
{
}

void ItemSlot::Init()
{
	UIButton::Init();
	OnEnter = [this]() {
		
	};
}

void ItemSlot::Release()
{
	UIButton::Release();
}

void ItemSlot::Reset()
{
	UIButton::Reset();
}

void ItemSlot::Update(float dt)
{
	UIButton::Update(dt);
	
}

void ItemSlot::Draw(sf::RenderWindow& window)
{
}
