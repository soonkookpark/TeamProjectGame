#include "stdafx.h"
#include "SliceSpriteGo.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "SpriteGo.h"
SliceSpriteGo::SliceSpriteGo(const std::string& textureID, sf::Rect<float> centerRect, sf::Rect<float> size, const std::string& name)
	:VertexArrayGo(textureID, name), centerRect(centerRect), spriteSize(size)
{
	sortLayer = 101;
}

void SliceSpriteGo::SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size)
{
	this->texture = &texture;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(36);

	this->centerRect = centerRect;
	this->spriteSize = size;

	SetTextureSize(centerRect, spriteSize);
	SetSize({ size.width, size.height });
}

void SliceSpriteGo::SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> spriteSize)
{
	std::vector<float> Horizontal;
	std::vector<float> Vertical;

	Horizontal.push_back(spriteSize.left);
	Horizontal.push_back(centerRect.left);
	Horizontal.push_back(centerRect.left + centerRect.width);
	Horizontal.push_back(spriteSize.left + spriteSize.width);

	Vertical.push_back(spriteSize.top);
	Vertical.push_back(centerRect.top);
	Vertical.push_back(centerRect.top + centerRect.height);
	Vertical.push_back(spriteSize.top + spriteSize.height);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].texCoords = { Horizontal[j], Vertical[i] };
			vertexArray[index + 1].texCoords = { Horizontal[j + 1], Vertical[i] };
			vertexArray[index + 2].texCoords = { Horizontal[j + 1], Vertical[i + 1] };
			vertexArray[index + 3].texCoords = { Horizontal[j], Vertical[i + 1] };
		}
	}
	origin = Origins::TL;
	position = { 0, 0 };
	originPosition = { 0, 0 };
}

void SliceSpriteGo::SetSize(sf::Vector2f size)
{
	std::vector<float> positionX;
	std::vector<float> positionY;
	sf::Vector2f borderSize = { spriteSize.width - centerRect.width, spriteSize.height - centerRect.height };

	if (borderSize.x < size.x)
	{
		positionX.push_back(spriteSize.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(centerRect.left + (size.x - borderSize.x));
		positionX.push_back(spriteSize.left + spriteSize.width - (centerRect.width - (size.x - borderSize.x)));
	}
	else
	{
		positionX.push_back(spriteSize.left);
		positionX.push_back(size.x * 0.5f);
		positionX.push_back(size.x * 0.5f);
		positionX.push_back(size.x);
	}

	if (borderSize.y < size.y)
	{
		positionY.push_back(spriteSize.top);
		positionY.push_back(centerRect.top);
		positionY.push_back(centerRect.top + (size.y - borderSize.y));
		positionY.push_back(spriteSize.top + spriteSize.height - (centerRect.height - (size.y - borderSize.y)));
	}
	else
	{
		positionY.push_back(spriteSize.top);
		positionY.push_back(size.y * 0.5f);
		positionY.push_back(size.y * 0.5f);
		positionY.push_back(size.y);
	}


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].position = { positionX[j], positionY[i] };
			vertexArray[index + 1].position = { positionX[j + 1], positionY[i] };
			vertexArray[index + 2].position = { positionX[j + 1], positionY[i + 1] };
			vertexArray[index + 3].position = { positionX[j], positionY[i + 1] };
		}
	}
	origin = Origins::TL;
	position = { 0, 0 };
	originPosition = { 0, 0 };
}

void SliceSpriteGo::Init()
{
	VertexArrayGo::Init();
}

void SliceSpriteGo::Release()
{
	VertexArrayGo::Release();
}

void SliceSpriteGo::Reset()
{
	SetTexture(*RESOURCE_MGR.GetTexture(textureId), centerRect, spriteSize);
}

void SliceSpriteGo::Update(float dt)
{
	
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = vertexArray.getBounds().contains(uiMousePos);
	if (!prevHover && isHover)
	{
		if (OnEnter != nullptr)
		{
			OnEnter();
			std::cout << "요 있다 나" << std::endl;
		}

	}

	if (prevHover && !isHover)
	{
		if (OnExit != nullptr)
			OnExit();
	}

	if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		if (OnClick != nullptr)
			OnClick();
	}
	VertexArrayGo::Update(dt);
}

sf::Vector2f SliceSpriteGo::GetSize()
{
	float x = vertexArray[9].position.x - vertexArray[0].position.x;
	float y = vertexArray[35].position.y - vertexArray[0].position.y;
	return sf::Vector2f{ x, y };
}
