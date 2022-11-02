#include "BFS.h"
#include <thread>

BFS::BFS(Graph& graph) :
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

void BFS::solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window)
{
	for (auto &obstacle : obstacleMap)
	{
		graph.getNode(obstacle).isObstacle = true;
	}

	this->source = source;
	this->target = target;

	Node* sourceNode = &(graph.getNode(this->source));
	grid.colorVisitedTile(sourceNode->nodeLocation);
	queue.push(sourceNode);
	sourceNode->visited = true;

	while (queue.empty() == false && targetFound == false)
	{
		Node* currentNode = queue.front();
		queue.pop();
		grid.colorVisitedTile(currentNode->nodeLocation);

		if (currentNode->nodeLocation == this->target)
		{
			std::cout << "Found target Node BFS" << std::endl;
			targetFound = true;
		}

		grid.drawGrid();
		//window.draw(text);
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		for (auto& neighbor : currentNode->neighbors)
		{
			if (!neighbor->visited && !neighbor->isObstacle)
			{
				queue.push(neighbor);
				neighbor->parent = currentNode;
				neighbor->visited = true;
				grid.colorVisitingTile(neighbor->nodeLocation);
			}
		}
	}
	if (queue.empty() && !targetFound)
	{
		std::cout << "Unable to find target node from source node" << std::endl;
	}
}

void BFS::constructPath(Grid& grid)
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
