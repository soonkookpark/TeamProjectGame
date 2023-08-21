#include "stdafx.h"
#include "Astar.h"
#include "Creature.h"

void Astar::CreatePool(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Node* newNode = new Node();
		nodePool.push_back(newNode);
	}
}

Astar::Node* Astar::Get()
{	
	if(nodePool.empty())
		CreatePool(100);
	Node* rtn = nodePool.front();
	nodePool.pop_front();
	return rtn;
}

void Astar::SetBack(Node* node)
{
	nodePool.push_back(node);
}

void Astar::Clear()
{
	for (auto obj : openNodes)
	{
		nodePool.push_back(obj);
	}
	for (auto obj : closedNodes)
	{
		nodePool.push_back(obj);
	}
	openNodes.clear();
	closedNodes.clear();
}

Astar::Astar()
{
	CreatePool(100);
}

Astar::~Astar()
{
	Clear();
	for (auto obj : nodePool)
	{
		delete(obj);
	}
	nodePool.clear();
}

std::stack<sf::Vector2i>* Astar::FindPath(Creature* stalker, Creature* target)
{
	Clear();
	this->stalker = stalker;
	this->target = target;
	if (stalker->GetTileIndex() == target->GetTileIndex())
	{
		return nullptr;
	}
	MaxFindValue = Utils::Distance(stalker->GetTileIndex(), target->GetTileIndex()) * MaxFindValueRate;

	Node* newNode = Get();
	newNode->pos = stalker->GetTileIndex();
	newNode->prevNode = nullptr;
	newNode->distance = 0.f;
	newNode->heuristic = 0.f;
	newNode->value = 0.f;
	Node* finalNode(nullptr);
	MakeNode(newNode);

	while (!(finalNode != nullptr || openNodes.empty()))
	{
		finalNode = MakeNode(SelectNextNode());
	}	

	std::stack<sf::Vector2i>* path = new std::stack<sf::Vector2i>();
 	MakePath(finalNode, path);
	return path;
}

bool Astar::FindPath(sf::Vector2i start, sf::Vector2i end)
{
	Clear();
	MaxFindValue = Utils::Distance(start, end) * MaxFindValueRate;

	Node* newNode = Get();
	newNode->pos = start;
	newNode->prevNode = nullptr;
	newNode->distance = 0.f;
	newNode->heuristic = 0.f;
	newNode->value = 0.f;
	Node* finalNode(nullptr);
	MakeNode(newNode, start, end);

	while (!(finalNode != nullptr || openNodes.empty()))
	{
		finalNode = MakeNode(SelectNextNode(), start, end);
	}

	std::stack<sf::Vector2i>* path = new std::stack<sf::Vector2i>();
	MakePath(finalNode, path);

	if (path == nullptr) return false;

	return true;
}

Astar::Node* Astar::MakeNode(Node* node, sf::Vector2i start, sf::Vector2i end)
{
	std::vector<sf::Vector2i> positions =
	{
		{node->pos.x , node->pos.y + 1},
		{node->pos.x + 1, node->pos.y},
		{node->pos.x , node->pos.y - 1},
		{node->pos.x - 1, node->pos.y},
		{node->pos.x + 1, node->pos.y + 1},
		{node->pos.x + 1, node->pos.y - 1},
		{node->pos.x - 1, node->pos.y + 1},
		{node->pos.x - 1, node->pos.y - 1},
	};
	if (node->value > MaxFindValue)
	{
		closedNodes.push_back(node);
		openNodes.remove(node);
		return nullptr;
	}
	for (int i = 0; i < positions.size(); i++)
	{
		if (positions[i].x < 0 || positions[i].y < 0)
			continue;
		if (tileArray[positions[i].y][positions[i].x] == 0 || CheckClosedNodes(positions[i]))
			continue;

		float distance = abs(positions[i].x) + abs(positions[i].y) == 2 ? 1.4f : 1.f;
		float heuristic = Utils::Distance(end, positions[i]);

		Node* newNode = Get();
		newNode->pos = positions[i];
		newNode->prevNode = node;
		newNode->distance = distance;
		newNode->heuristic = heuristic;
		newNode->value = distance + heuristic;

		RefineNode(newNode);
		openNodes.push_back(newNode);
		if (positions[i] == end)
			return newNode;
	}
	closedNodes.push_back(node);
	if (node->prevNode != nullptr)
		openNodes.remove(node);
	return nullptr;
}

void Astar::MakePath(Node* node, std::stack<sf::Vector2i>* path)
{
	if (node == nullptr)
		return;	
	if (node->prevNode == nullptr)
		return;
	else
	{
		path->push(node->pos);
		MakePath(node->prevNode, path);
	}
}

void Astar::RefineNode(Node* node)
{
	for (auto openNode : openNodes)
	{
		if (openNode->pos == node->pos)
		{
			openNodes.remove(openNode);
			SetBack(openNode);
			return;
		}
	}
}

bool Astar::CheckClosedNodes(sf::Vector2i position)
{
	for (Node* closedNode : closedNodes)
	{
		if (position == closedNode->pos)
			return true;
	}
	return false;
}

Astar::Node* Astar::SelectNextNode()
{
	Node* rtn = openNodes.front();
	for (auto openNode : openNodes)
	{
		rtn = rtn->value < openNode->value ? rtn : openNode;
	}
	return rtn;
}

Astar::Node* Astar::MakeNode(Node* node)
{
	std::vector<sf::Vector2i> positions =
	{
		{node->pos.x , node->pos.y + 1},
		{node->pos.x + 1, node->pos.y},
		{node->pos.x , node->pos.y - 1},
		{node->pos.x - 1, node->pos.y},
		{node->pos.x + 1, node->pos.y + 1},
		{node->pos.x + 1, node->pos.y - 1},
		{node->pos.x - 1, node->pos.y + 1},
		{node->pos.x - 1, node->pos.y - 1},
	};
	if (node->value > MaxFindValue)
	{
		closedNodes.push_back(node);
		openNodes.remove(node);
		return nullptr;
	}
	for (int i = 0; i < positions.size(); i++)
	{		
		if (positions[i].x < 0 || positions[i].y < 0)
			continue;
		if (tileArray[positions[i].y][positions[i].x] == 0 || CheckClosedNodes(positions[i]))
			continue;
		
		float distance = abs(positions[i].x) + abs(positions[i].y) == 2 ? 1.4f : 1.f;
		float heuristic = Utils::Distance(target->GetTileIndex(), positions[i]);
				 
		Node* newNode = Get();
		newNode->pos = positions[i];
		newNode->prevNode = node;
		newNode->distance = distance;
		newNode->heuristic = heuristic;
		newNode->value = distance + heuristic;

		RefineNode(newNode);
		openNodes.push_back(newNode);
		if (positions[i] == target->GetTileIndex())
			return newNode;
	}
	closedNodes.push_back(node);
	if(node->prevNode != nullptr)
		openNodes.remove(node);
	return nullptr;
}
