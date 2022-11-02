#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Location.h"
#include <unordered_set>
#include <list>

class AStar : public Algorithm
{
public:
	AStar(Graph& graph);
	virtual void solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window) override;
	virtual void constructPath(Grid& grid) override;
	double findDistance(Node* firstNode, Node* secondNode);

private:
	Graph& graph;
	sf::Font font;
	sf::Text text;

	Location source;
	Location target;
	
	bool targetFound = false;

	std::unordered_set<Node*> nodeSet;
	std::list<Node*> pq;
};

