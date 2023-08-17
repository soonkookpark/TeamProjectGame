#include "stdafx.h"
#include "Tree.h"
#include "Utils.h"
#include "TileMap.h"

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
	
	/*for (int i = rect.left; i < rect.left + rect.width; i++)
	{
		tileMap->ChangeTile(i, rect.top + 1, 0);
		tileMap->ChangeTile(i, rect.top + rect.height - 1, 0);
	}
	for (int i = rect.top; i < rect.top + rect.height; i++)
	{
		tileMap->ChangeTile(rect.left + 1, i, 0);
		tileMap->ChangeTile(rect.left + rect.width - 1, i, 0);
	}
	*/
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
		int rand;
		if (rect.width >= 5)
			rand = Utils::RandomRange(-3, 4);


		if (center.y < route.y)
		{
			for (int i = center.y; i <= route.y; i++)
			{
				tileMap->ChangeTile(center.x, i, 8);
				tileMap->ChangeTile(center.x + 1, i, 8);
				tileMap->ChangeTile(center.x - 1, i, 8);


/*				if (i < center.y + 3) continue;
				if (level >= 5) continue;
				tileMap->ChangeTile(center.x + 2, i, 0);
				tileMap->ChangeTile(center.x + 3, i, 0);

				tileMap->ChangeTile(center.x - 2, i, 0);
				tileMap->ChangeTile(center.x - 3, i, 0);*/		
			}
		}
		else
		{
			for (int i = center.y; i >= route.y; i--)
			{
				tileMap->ChangeTile(center.x, i, 8);
				tileMap->ChangeTile(center.x + 1, i, 8);
				tileMap->ChangeTile(center.x - 1, i, 8);

				//if (i > center.y - 3) continue;
				//if (level >= 5) continue;
				//tileMap->ChangeTile(center.x + 2, i, 0);
				//tileMap->ChangeTile(center.x + 3, i, 0);

				//tileMap->ChangeTile(center.x - 2, i, 0);
				//tileMap->ChangeTile(center.x - 3, i, 0);
			}
		}
	}
	else
	{
		int rand;
		if (rect.height >= 5)
			rand = Utils::RandomRange(-3, 4);

		if (center.x < route.x)
		{
			for (int i = center.x; i <= route.x; i++)
			{
				tileMap->ChangeTile(i, center.y, 8);
				tileMap->ChangeTile(i, center.y + 1, 8);
				tileMap->ChangeTile(i, center.y - 1, 8);

				//if (i < center.x + 3) continue;
				//if (level >= 5) continue;
				//tileMap->ChangeTile(i, center.y + 2, 0);
				//tileMap->ChangeTile(i, center.y + 3, 0);

				//tileMap->ChangeTile(i, center.y - 2, 0);
				//tileMap->ChangeTile(i, center.y - 3, 0);
			}
		}
		else
		{
			for (int i = center.x; i >= route.x; i--)
			{
				tileMap->ChangeTile(i, center.y, 8);
				tileMap->ChangeTile(i, center.y + 1, 8);
				tileMap->ChangeTile(i, center.y - 1, 8);

				//if (i > center.x - 3) continue;
				//if (level >= 5) continue;
				//tileMap->ChangeTile(i, center.y + 2, 0);
				//tileMap->ChangeTile(i, center.y + 3, 0);

				//tileMap->ChangeTile(i, center.y - 2, 0);
				//tileMap->ChangeTile(i, center.y - 3, 0);
			}
		}
	}
	
	return;
	//tileMap->ChangeTile(0, 0, 8); //x좌표, y좌표, 타일 인덱스
}

void Tree::DrawRoom(sf::RenderWindow& window)
{
	if (child_L != nullptr && child_R != nullptr)
	{
		child_L->DrawRoom(window);
		child_R->DrawRoom(window);
	}

	room.setSize({ (float)rect.width - 1, (float)rect.width - 1 });
	room.setPosition((sf::Vector2f)GetCenter());
	room.setOutlineColor(sf::Color::Red);
	room.setOutlineThickness(3);

	window.draw(room);
}

sf::Vector2i Tree::GetCenter()
{
	return sf::Vector2i{ 
		(int)((rect.left + rect.left + rect.width) * 0.5f), 
		(int)((rect.top + rect.top + rect.height) * 0.5f) };
}
