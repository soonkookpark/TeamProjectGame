#include "stdafx.h"
#include "Tree.h"
#include "Utils.h"

Tree::~Tree()
{
	if (child_L != nullptr)
	{
		delete child_L;
		child_L = nullptr;
	}

	if (child_R != nullptr)
	{
		delete child_R;
		child_R = nullptr;
	}
}

sf::Vector2f Tree::Divide(sf::FloatRect rect)
{
	int randRatio = Utils::RandomRange(3, 8); //3~7

	child_L = new Tree();
	child_R = new Tree();

	child_L->level = this->level + 1;
	child_L->parent = this;

	child_R->level = this->level + 1;
	child_R->parent = this;

	if (rect.height > rect.width) //가로로 자름
	{
		child_L->rect = rect;
		child_L->rect.top = rect.top;
		child_L->rect.height = (rect.height * randRatio) / 10;

		child_R->rect = rect;
		child_R->rect.top = rect.top + (rect.height * randRatio) / 10;
		child_R->rect.height = rect.height - ((rect.height * randRatio) / 10);

		return sf::Vector2f{ 0, (rect.height * randRatio) / 10 };
	}
	else //세로로 자름
	{
		child_L->rect = rect;
		child_L->rect.left = rect.left;
		child_L->rect.width = (rect.width * randRatio) / 10;

		child_R->rect = rect;
		child_R->rect.left = rect.left + (rect.width * randRatio) / 10;
		child_R->rect.width = rect.width - ((rect.width * randRatio) / 10);

		return sf::Vector2f{ (rect.width * randRatio) / 10, 0 };
	}
}
