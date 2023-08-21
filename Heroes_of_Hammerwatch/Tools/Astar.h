#pragma once
class Creature;

class Astar
{
public:
	struct Node
	{
		sf::Vector2i pos;
		Node* prevNode;
		float distance = 0.f;
		float heuristic = 0.f;
		float value = 0.f;
	};
private:
	Creature* target;
	Creature* stalker;

	float MaxFindValue = 0.f;
	float MaxFindValueRate = 1.5f;

	std::vector<std::vector<int>> tileArray;


	std::list<Node*> openNodes;
	std::list<Node*> closedNodes;

	Node* selecetedNode;
	std::list<Node*> nodePool;

	void CreatePool(int amount);
	Node* Get();
	void SetBack(Node* node);
	void Clear();

	Node* MakeNode(Node* node);
	void MakePath(Node* node, std::stack<sf::Vector2i>* path);
	bool CheckClosedNodes(sf::Vector2i position);
	void RefineNode(Node* node);
	Node* SelectNextNode();
public:
	Astar();
	virtual ~Astar();

	//사용할 씬 안에서 타일 생성 된 이후 적용
	void SetTileArray(std::vector<std::vector<int>> tileArray) { this->tileArray = tileArray; }
	void SetMaxFindValueRate(float rate) { MaxFindValueRate = rate; }

	std::stack<sf::Vector2i>* FindPath(Creature* stalker, Creature* target);
};

