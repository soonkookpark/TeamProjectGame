#include "stdafx.h"
#include "Tree.h"
#include "Utils.h"
#include "TileMap.h"
#include "Astar.h"

bool Tree::entrance = false;
bool Tree::starting = false;

Tree::Tree(sf::IntRect rect) 
	: parent(nullptr), child_L(nullptr), child_R(nullptr), rect(rect) 
{
	Tree::entrance = false;
	Tree::starting = false;
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

	TileMap* tileMap = tileMapPtr;

	if (parent == nullptr)
	{
		for (int i = 0; i < tileMap->TileIntSize().x; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				tileMap->ChangeTile(i, j, 0);
				tileMap->ChangeTile(i, tileMap->TileIntSize().y - 1 - j, 0);
			}
		}
		for (int i = 0; i < tileMap->TileIntSize().y; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				tileMap->ChangeTile(j, i, 0);
				tileMap->ChangeTile(tileMap->TileIntSize().x - 1 - j, i, 0);
			}
		}
		return;
	}

	sf::Vector2i center = this->GetCenter();
	sf::Vector2i route = parent->GetCenter();
	
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

void Tree::Room(TileMap* tileMapPtr, Astar* finder)
{
	std::vector<Tree*> room;
	SettingRoom(tileMapPtr, room, finder);
}

bool Tree::SettingRoom(TileMap* tileMapPtr, std::vector<Tree*>& room, Astar* finder)
{
	if (child_L != nullptr && child_R != nullptr) //자식이 있으면 한번더 실행
	{
		child_L->SettingRoom(tileMapPtr, room, finder);
		child_R->SettingRoom(tileMapPtr, room, finder);
	}

	TileMap* tileMap = tileMapPtr;

	if (parent != nullptr) //부모가 있으면 자기랑 부모 위치 비교
	{
		sf::Vector2i center = this->GetCenter();
		sf::Vector2i route = parent->GetCenter();

		/*if (this->rect.top == 0 && this->rect.width > 3)
		{
			room.push_back(this);
			return true;
		}*/

		if (level > 5 && route.x == center.x && center.y - 2 < route.y && child_L == nullptr)
		{
			room.push_back(this);
		}
		return true;
	}

	if (room.empty()) return true;
	if (room.size() < 2)
	{
		std::cout << "사이즈가 작음" << std::endl;
		return false;
	}

	

	int count = 0;

	int forStart;
	do
	{
		forStart = Utils::RandomRange(0, room.size());
		count++;
		if (count > 50)
		{
			std::cout << "에러" << std::endl;
			return false;
		}

	} while (room[forStart]->GetCenter().y > rect.height * 0.25);


	int forEnt;
	do
	{
		count++;
		if (count > 150) 
		{
			std::cout << "에러" << std::endl;
			return false;
		}
		forEnt = Utils::RandomRange(0, room.size());

	} while (room[forEnt]->GetCenter().y < rect.height * 0.6
		|| room[forEnt]->GetCenter().x > rect.width * 0.25 && room[forEnt]->GetCenter().x < rect.width * 0.25
		|| forStart == forEnt ||
		tileMapPtr->ReturnTile(room[forStart]->GetCenter().x + 1, rect.top - 2) == 8 || room[forEnt]->rect.height < 4);

	sf::IntRect start = room[forStart]->rect;
	sf::IntRect ent = room[forEnt]->rect;

	if (!entrance)
	{
		for (int i = ent.top; i < (ent.top + ent.height); i++)
		{
			for (int j = ent.left; j < (ent.left + ent.width); j++)
			{
				//tileMap->ChangeTile(j, i, 0);
			}
		}
		entrance = true;
	}

	if (!starting)
	{
		for (int i = start.top; i < (start.top + start.height); i++)
		{
			for (int j = start.left; j < (start.left + start.width); j++)
			{
				//tileMap->ChangeTile(j, i, 0);
			}
		}
		starting = true;
	}
	ConnectRoom(tileMapPtr);

	tileMap->CreateDoor(
		sf::Vector2i{ (start.left + start.left + start.width) / 2, start.top-4},
		sf::Vector2i{ (ent.left + ent.left + ent.width) / 2, ent.top-2});

	sf::Vector2i startPos = room[forStart]->GetCenter();
	sf::Vector2i endPos = room[forEnt]->GetCenter();
	startPos += {1, 1};
	endPos += {1, 1};


	bool check = finder->FindPath(startPos, endPos);
	 
	if (!check)
	{
		std::cout << check << std::endl;
		starting = false;
		entrance = false;
		room.clear();
		SettingRoom(tileMapPtr, room, finder);
	}

	return true;
}

void Tree::Debug()
{
	if (child_L != nullptr && child_R != nullptr) //자식이 있으면 한번더 실행
	{
		child_L->Debug();
		child_R->Debug();
	}

	if (child_L == nullptr)
	{
		rectangle.vertexArray.setPrimitiveType(sf::LinesStrip);
		rectangle.vertexArray.resize(5);
		rectangle.vertexArray[0].position = { (float)rect.left * 16.f, (float)rect.top * 16.f };
		rectangle.vertexArray[1].position = { ((float)rect.left + rect.width) * 16.f, (float)rect.top * 16.f };
		rectangle.vertexArray[2].position = { ((float)rect.left + rect.width) * 16.f, ((float)rect.top+rect.height) * 16.f };
		rectangle.vertexArray[3].position = { (float)rect.left * 16.f, ((float)rect.top + rect.height) * 16.f };
		rectangle.vertexArray[4].position = { (float)rect.left * 16.f, (float)rect.top * 16.f };

		rectangle.vertexArray[0].color = sf::Color::Blue;
		rectangle.vertexArray[1].color = sf::Color::Blue;
		rectangle.vertexArray[2].color = sf::Color::Blue;
		rectangle.vertexArray[3].color = sf::Color::Blue;
		rectangle.vertexArray[4].color = sf::Color::Blue;
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	if (child_L != nullptr && child_R != nullptr) //자식이 있으면 한번더 실행
	{
		child_L->Draw(window);
		child_R->Draw(window);
	}

	window.draw(rectangle.vertexArray);
}

sf::Vector2i Tree::GetCenter()
{
	return sf::Vector2i{
		(int)((rect.left) + (rect.width * 0.5f)),
		(int)((rect.top) + (rect.height * 0.5f)) };
}
