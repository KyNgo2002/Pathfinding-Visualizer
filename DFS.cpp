#include "DFS.h"
#include <thread>

DFS::DFS(Graph& graph) :
	graph(graph) 
{
	/*if (!font.loadFromFile("fonts/arial.ttf")) {}
	text.setString("Solving BFS");
	text.setPosition(sf::Vector2f(400, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(25);
	text.setOutlineThickness(5);
	text.setFont(font);*/
}

void DFS::solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window)
{
	for (auto& obstacle : obstacleMap)
	{
		graph.getNode(obstacle).isObstacle = true;
	}

	this->source = source;
	this->target = target;

	Node* sourceNode = &(graph.getNode(source));
	stack.push(sourceNode);
	sourceNode->visited = true;

	while (!stack.empty() && !targetFound)
	{
		Node* currentNode = stack.top();
		stack.pop();
		grid.colorVisitedTile(currentNode->nodeLocation);
		grid.drawGrid();
		window.display();

		if (currentNode->nodeLocation == target)
		{
			targetFound = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		for (auto& neighbor : currentNode->neighbors)
		{
			if (neighbor->nodeLocation == target)
			{
				targetFound = true;
			}
			if (neighbor->visited || neighbor->isObstacle)
			{
				continue;
			}
			else
			{
				stack.push(neighbor);
				neighbor->parent = currentNode;
				neighbor->visited = true;
				grid.colorVisitingTile(neighbor->nodeLocation);
			}
		}
	}
	if (stack.empty() && !targetFound)
	{
		std::cout << "Unable to find target node from source node(DFS)" << std::endl;
	}
}

void DFS::constructPath(Grid& grid)
{
	Node* targetNode = &(graph.getNode(target));
	if (targetNode != nullptr)
	{
		while (targetNode != nullptr)
		{
			grid.colorPathTile(targetNode->nodeLocation);
			targetNode = targetNode->parent;
		}
	}
}