#pragma once
#include "Algorithm.h"
#include <stack>
#include "Graph.h"

class DFS : public Algorithm
{
public:
	DFS(Graph& graph);
	virtual void solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window) override;
	virtual void constructPath(Grid& grid) override;

private:
	Graph& graph;
	Location source;
	Location target;

	sf::Font font;
	sf::Text text;

	std::stack<Node*> stack;
	bool targetFound = false;
};

