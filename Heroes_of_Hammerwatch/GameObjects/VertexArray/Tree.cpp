#include "stdafx.h"
#include "Tree.h"
#include "Utils.h"
#include "TileMap.h"
#include "Astar.h"
#include "Monster.h"
#include "Scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"

bool Tree::entrance = false;
bool Tree::starting = false;

Tree::Tree(sf::IntRect rect) 
	: parent(nullptr), childLeft(nullptr), childRight(nullptr), rect(rect) 
{
	Tree::entrance = false;
	Tree::starting = false;

	treePool = new ObjectPool<Tree>();
	treePool->Init(100);

}

Tree::~Tree()
{
	if (childLeft != nullptr)
	{
		treePool->Return(childLeft);
	}

	if (childRight != nullptr)
	{
		treePool->Return(childRight);
	}

	if (treePool != nullptr)
	{
		treePool->Release();
		delete treePool;
	}
}

void Tree::Divide(TileMap* tileMapPtr)
{
	if (childLeft != nullptr && childRight != nullptr)
	{
		childLeft->Divide(tileMapPtr);
		childRight->Divide(tileMapPtr);
		return;
	}

	//맵 분할

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


	childLeft = treePool->Get();
	childRight = treePool->Get();

	childLeft->level = this->level + 1;
	childLeft->parent = this;

	childRight->level = this->level + 1;
	childRight->parent = this;

	if (rect.height > rect.width) //가로로 자름
	{
		childLeft->rect = rect;
		childLeft->rect.width = rect.width;
		childLeft->rect.height = (rect.height * randRatio) / 10;

		childRight->rect = rect;
		childRight->rect.top = rect.top + (rect.height * randRatio) / 10;
		childRight->rect.height = rect.height - ((rect.height * randRatio) / 10);

		for (int i = rect.left; i < rect.left + rect.width; i++)
		{
			tileMap->ChangeTile(i, rect.top + childLeft->rect.height, 0);
			tileMap->ChangeTile(i, rect.top + childLeft->rect.height + 1, 0);
			tileMap->ChangeTile(i, rect.top + childLeft->rect.height - 1, 0);
		}
		return;
	}
	else //세로로 자름
	{
		childLeft->rect = rect;
		childLeft->rect.left = rect.left;
		childLeft->rect.width = (rect.width * randRatio) / 10;

		childRight->rect = rect;
		childRight->rect.left = rect.left + (rect.width * randRatio) / 10;
		childRight->rect.width = rect.width - ((rect.width * randRatio) / 10);

		for (int i = rect.top; i < rect.top + rect.height; i++)
		{
			tileMap->ChangeTile(rect.left + childLeft->rect.width, i, 0);
			tileMap->ChangeTile(rect.left + childLeft->rect.width + 1, i, 0);
			tileMap->ChangeTile(rect.left + childLeft->rect.width - 1, i, 0);
		}
		return;
	}
}

void Tree::ConnectRoom(TileMap* tileMapPtr)
{
	if (childLeft != nullptr && childRight != nullptr)
	{
		childLeft->ConnectRoom(tileMapPtr);
		childRight->ConnectRoom(tileMapPtr);
	}

	TileMap* tileMap = tileMapPtr;

	if (parent == nullptr)
	{
		for (int i = 0; i < tileMap->TileIntSize().x; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				tileMap->ChangeTile(i, j, 0);
				tileMap->ChangeTile(i, tileMap->TileIntSize().y - 1 - j, 0);
			}
		}
		for (int i = 0; i < tileMap->TileIntSize().y; i++)
		{
			for (int j = 0; j < 20; j++)
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

void Tree::Divide(TileMap* tileMapPtr, int level)
{
	for (int i = 0; i < level; i++)
	{
		Divide(tileMapPtr);
	}
}

bool Tree::Room(TileMap* tileMapPtr, Astar* finder)
{
	std::vector<Tree*> room;
	return SettingRoom(tileMapPtr, room, finder);
}

bool Tree::SettingRoom(TileMap* tileMapPtr, std::vector<Tree*>& room, Astar* finder)
{
	if (childLeft != nullptr && childRight != nullptr) //자식이 있으면 한번더 실행
	{
		childLeft->SettingRoom(tileMapPtr, room, finder);
		childRight->SettingRoom(tileMapPtr, room, finder);
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

		if (level > 5 && route.x == center.x && center.y - 2 < route.y && childLeft == nullptr)
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
	if (childLeft != nullptr && childRight != nullptr) //자식이 있으면 한번더 실행
	{
		childLeft->Debug();
		childRight->Debug();
	}

	if (childLeft == nullptr)
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
	if (childLeft != nullptr && childRight != nullptr) //자식이 있으면 한번더 실행
	{
		childLeft->Draw(window);
		childRight->Draw(window);
	}
	Debug();
	window.draw(rectangle.vertexArray);
}

void Tree::SummonMonster(sf::Vector2f start, TileMap* tileMap)
{
	if (childLeft != nullptr && childRight != nullptr) //자식이 있으면 한번더 실행
	{
		childLeft->SummonMonster(start, tileMap);
		childRight->SummonMonster(start, tileMap);
	}

	float tilePixel = tileMap->TilePixelSize().x;

	sf::Vector2f center = (sf::Vector2f)this->GetCenter() * tilePixel;
	float distance = Utils::Distance(start, center);

	if (childLeft != nullptr) return;
	if (distance < 270) return;
	if (rect.width < 7 || rect.height < 7) return;

	Scene* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());

	float rad = (this->rect.width < this->rect.height-1 ? this->rect.width-1 : this->rect.height) * tilePixel * 0.5f;
	int num = (this->rect.width * this->rect.height) / 16 / 2.5;
	
	for (int i = 0; i < num; i++)
	{
		sf::Vector2f randPos;
		int index;
		do {
			randPos = Utils::RandomInCircle(rad);
			sf::Vector2i arr = (sf::Vector2i)((randPos + center) / 16.f);
			index = tileMap->GetTileArray()[arr.y][arr.x];
		} while (index == 0);


		int type = Utils::RandomRange(0, 2);

		Monster* monster = nullptr;

		switch (type)
		{
		case 0:
			monster = new Monster("Bat", randPos + center); //타입, 이름, 좌표
			break;
		case 1:
			monster = new Monster("Tick", randPos + center); //타입, 이름, 좌표
			break;
		}


		monster->SetTileMap(tileMap);
		monster->Reset();
		monster->SetOnTileMap(dynamic_cast<SceneGame*>(scene)->GetOnTile());
		
		dynamic_cast<SceneGame*>(scene)->AddGo(monster);
		dynamic_cast<SceneGame*>(scene)->Summon(monster);
	}
}

sf::Vector2i Tree::GetCenter()
{
	return sf::Vector2i{
		(int)((rect.left) + (rect.width * 0.5f)),
		(int)((rect.top) + (rect.height * 0.5f)) };
}
