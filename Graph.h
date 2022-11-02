#pragma once
#include <vector>
#include "Location.h"

struct Node
{
	Node(int x, int y) : nodeLocation({x, y}) {}
	Location nodeLocation;
	Node* parent = nullptr;
	bool visited = false;
	bool isObstacle = false;
	double dCost = INFINITY;		//Dijkstras algorithm minimum cost
	double gCost = INFINITY;		//Heuristic for A* (Start node -> current node distance)
	double hCost = INFINITY;		//Heuristic for A* (Current node -> target node distance)
	double fCost;					//Heuristic for A*
	std::vector<Node*> neighbors;
};

class Graph
{
public:
	Graph(std::pair<int, int> numTiles);
	Node& getNode(const Location &loc);
	void resetGraph();

private:
	//Members
	std::vector<Node> nodes;
	int numXTiles;
	int numYTiles;
};

