#include "AStar.h"
#include <thread>

AStar::AStar(Graph& graph)
	: graph(graph)
{
	/*if (!font.loadFromFile("fonts/arial.ttf")) {}
	text.setString("Solving A*");
	text.setPosition(sf::Vector2f(400, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(25);
	text.setOutlineThickness(5);
	text.setFont(font);*/
}

void AStar::solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window)
{
	for (auto& obstacle : obstacleMap)
	{
		graph.getNode(obstacle).isObstacle = true;
	}
	this->source = source;
	this->target = target;
	
	auto fCostcomparator = [](Node* leftnode, Node* rightnode)
	{
		return leftnode->fCost < rightnode->fCost;
	};

	Node* sourceNode = &(graph.getNode(source));
	Node* targetNode = &(graph.getNode(target));
	sourceNode->gCost = 0;
	sourceNode->hCost = findDistance(sourceNode, targetNode);
	pq.emplace_back(sourceNode);

	while (!pq.empty() && !targetFound)
	{
		pq.sort(fCostcomparator);
		Node* currentNode = pq.front();
		pq.pop_front();
		currentNode->visited = true;

		grid.colorVisitedTile(currentNode->nodeLocation);

		if (currentNode->nodeLocation == this->target)
		{
			targetFound = true;
		}

		grid.drawGrid();
		//window.draw(text);
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		for (auto& neighbor : currentNode->neighbors)
		{
			if (neighbor->isObstacle || neighbor->visited)
			{

			}
			else
			{
				double newGCost = currentNode->gCost + findDistance(currentNode, neighbor);
				if (newGCost < neighbor->gCost)
				{
					neighbor->parent = currentNode;
					neighbor->gCost = newGCost;
					neighbor->hCost = findDistance(neighbor, targetNode);
					neighbor->fCost = neighbor->gCost + neighbor->hCost;
					auto find = nodeSet.find(neighbor);
					if (find == nodeSet.end())
					{
						nodeSet.insert(neighbor);
						grid.colorVisitingTile(neighbor->nodeLocation);
						pq.emplace_back(neighbor);
					}
				}
			}
		}
	}
	if (pq.empty() && !targetFound)
	{
		std::cout << "Unable to find target node from source node(A*)" << std::endl;
	}
	
}

void AStar::constructPath(Grid& grid)
{
	Node* targetNode = &(graph.getNode(target));
	if (targetNode->parent != nullptr)
	{
		while (targetNode->parent != nullptr)
		{
			grid.colorPathTile(targetNode->nodeLocation);
			targetNode = targetNode->parent;
		}
	}
}

double AStar::findDistance(Node* firstNode, Node* secondNode)
{
	double x = pow(firstNode->nodeLocation.x - secondNode->nodeLocation.x, 2);
	double y = pow(firstNode->nodeLocation.y - secondNode->nodeLocation.y, 2);
	return sqrt(x + y);
}