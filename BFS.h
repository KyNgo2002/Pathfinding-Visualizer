#pragma once
#include "Algorithm.h"
#include <iostream>
#include <queue>
#include "Graph.h"
#include "Grid.h"

class BFS : public Algorithm
{
public:

	//Constructors
	BFS(Graph& graph);
	virtual void solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window) override;
	virtual void constructPath(Grid& grid) override;
private:
	std::queue<Node*> queue;
	Graph& graph;
	Location source;
	Location target;
	sf::Text text;
	sf::Font font;
	bool targetFound = false;

};

 