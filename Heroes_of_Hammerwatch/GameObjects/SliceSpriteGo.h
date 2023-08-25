#pragma once
#include "VertexArrayGo.h"
class SliceSpriteGo : public VertexArrayGo
{
protected:
	sf::Rect<float> centerRect; //늘려야할 부분
	sf::Rect<float> spriteSize; //기존의 스프라이트 사이즈
	bool isHover = false;
	bool isClick = false;
public:
	SliceSpriteGo(const std::string& textureID, sf::Rect<float> centerRect, sf::Rect<float> size, const std::string& name = "");

	virtual void SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size);
	void SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> spriteSize);
	virtual void SetSize(sf::Vector2f size);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	sf::Vector2f GetSize();

	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;
};