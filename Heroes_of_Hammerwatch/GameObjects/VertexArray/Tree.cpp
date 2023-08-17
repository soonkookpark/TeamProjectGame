#include "stdafx.h"
#include "Tree.h"
#include "Utils.h"
#include "TileMap.h"

bool Tree::entrance = false;
bool Tree::starting = false;

Tree::Tree(sf::IntRect rect) 
	: parent(nullptr), child_L(nullptr), child_R(nullptr), rect(rect) 
{

}

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

void Tree::Divide(TileMap* tileMapPtr)
{
	if (child_L != nullptr && child_R != nullptr)
	{
		child_L->Divide(tileMapPtr);
		child_R->Divide(tileMapPtr);
		return;
	}

	TileMap* tileMap = tileMapPtr;

	int randRatio = Utils::RandomRange(3, 8); //30~70
	if (rect.height > rect.width)
	{
		while (GetCenter().y + 1 > (rect.height * randRatio) / 10 &&
			GetCenter().y - 1 < (rect.height * randRatio) / 10)
		{
			randRatio = Utils::RandomRange(3, 8);
		}
	}
	else
	{
		while (GetCenter().x + 1 > (rect.width * randRatio) / 10 &&
			GetCenter().x - 1 < (rect.width * randRatio) / 10)
		{
			randRatio = Utils::RandomRange(3, 8);
		}
	}


	child_L = new Tree();
	child_R = new Tree();

	child_L->level = this->level + 1;
	child_L->parent = this;

	child_R->level = this->level + 1;
	child_R->parent = this;

	if (rect.height > rect.width) //가로로 자름
	{
		child_L->rect = rect;
		child_L->rect.width = rect.width;
		child_L->rect.height = (rect.height * randRatio) / 10;

		child_R->rect = rect;
		child_R->rect.top = rect.top + (rect.height * randRatio) / 10;
		child_R->rect.height = rect.height - ((rect.height * randRatio) / 10);

		for (int i = rect.left; i < rect.left + rect.width; i++)
		{
			tileMap->ChangeTile(i, rect.top + child_L->rect.height, 0);
			tileMap->ChangeTile(i, rect.top + child_L->rect.height + 1, 0);
			tileMap->ChangeTile(i, rect.top + child_L->rect.height - 1, 0);
		}
		return;
	}
	else //세로로 자름
	{
		child_L->rect = rect;
		child_L->rect.left = rect.left;
		child_L->rect.width = (rect.width * randRatio) / 10;

		child_R->rect = rect;
		child_R->rect.left = rect.left + (rect.width * randRatio) / 10;
		child_R->rect.width = rect.width - ((rect.width * randRatio) / 10);

		for (int i = rect.top; i < rect.top + rect.height; i++)
		{
			tileMap->ChangeTile(rect.left + child_L->rect.width, i, 0);
			tileMap->ChangeTile(rect.left + child_L->rect.width + 1, i, 0);
			tileMap->ChangeTile(rect.left + child_L->rect.width - 1, i, 0);
		}
		return;
	}
}

void Tree::ConnectRoom(TileMap* tileMapPtr)
{
	if (child_L != nullptr && child_R != nullptr)
	{
		child_L->ConnectRoom(tileMapPtr);
		child_R->ConnectRoom(tileMapPtr);
	}

	if (parent == nullptr) return;

	TileMap* tileMap = tileMapPtr;

	sf::Vector2i center = this->GetCenter();
	sf::Vector2i route = parent->GetCenter();
	
	for (int i = 0; i < tileMap->TileIntSize().x; i++)
	{
		tileMap->ChangeTile(i, 0, 0);
		tileMap->ChangeTile(i, tileMap->TileIntSize().y - 1, 0);
	}
	for (int i = 0; i < tileMap->TileIntSize().y; i++)
	{
		tileMap->ChangeTile(0, i, 0);
		tileMap->ChangeTile(tileMap->TileIntSize().x - 1, i, 0);
	}

	if (route.x == center.x)
	{	
		int rand = Utils::RandomRange(0, 4);

		if (center.y < route.y)
		{
			for (int i = center.y; i <= route.y; i++)
			{
				tileMap->ChangeTile(center.x, i, 8);
				tileMap->ChangeTile(center.x + 1, i, 8);
				tileMap->ChangeTile(center.x - 1, i, 8);	
			}
		}
		else
		{
			for (int i = center.y; i >= route.y; i--)
			{
				tileMap->ChangeTile(center.x, i, 8);
				tileMap->ChangeTile(center.x + 1, i, 8);
				tileMap->ChangeTile(center.x - 1, i, 8);
			}
		}
	}
	else
	{
		if (center.x < route.x)
		{
			for (int i = center.x; i <= route.x; i++)
			{
				tileMap->ChangeTile(i, center.y, 8);
				tileMap->ChangeTile(i, center.y + 1, 8);
				tileMap->ChangeTile(i, center.y - 1, 8);
			}
		}
		else
		{
			for (int i = center.x; i >= route.x; i--)
			{
				tileMap->ChangeTile(i, center.y, 8);
				tileMap->ChangeTile(i, center.y + 1, 8);
				tileMap->ChangeTile(i, center.y - 1, 8);
			}
		}
	}
	
	return;
	//tileMap->ChangeTile(0, 0, 8); //x좌표, y좌표, 타일 인덱스
}

void Tree::SettinRoom()
{
	if (child_L != nullptr && child_R != nullptr)
	{
		child_L->SettinRoom();
		child_R->SettinRoom();
	}
	if (entrance || starting) return;

 





}

sf::Vector2i Tree::GetCenter()
{
	return sf::Vector2i{ 
		(int)((rect.left + rect.left + rect.width) * 0.5f), 
		(int)((rect.top + rect.top + rect.height) * 0.5f) };
}
