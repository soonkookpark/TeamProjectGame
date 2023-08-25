#pragma once
#include "UIButton.h"
class ItemSlot : public UIButton
{
protected:

public:
	ItemSlot(const std::string& textureId = "", const std::string& n = "");
	virtual ~ItemSlot() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

