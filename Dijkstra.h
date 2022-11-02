#pragma once
#include "Algorithm.h"
#include "Graph.h"
#include "Location.h"
#include <list>
#include <set>

class Dijkstra : public Algorithm
{
public:
	Dijkstra(Graph& graph);
	virtual void solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window) override;
	virtual void constructPath(Grid& grid) override;

private:
	std::list<Node*> pq;
	std::set<Node*> containsNode;

	Graph& graph;
	Location source;
	Location target;
	
	sf::Font font;
	sf::Text text;

	bool targetFound = false;

	double nodeDistance(Node* firstNode, Node* secondNode);
};

