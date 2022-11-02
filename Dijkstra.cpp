#include "Dijkstra.h"
#include <thread>


Dijkstra::Dijkstra(Graph& graph) :
	graph(graph)
{
	/*if (!font.loadFromFile("arial.ttf")) {}
	text.setString("Solving Dijsktra's");
	text.setPosition(sf::Vector2f(400, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(25);
	text.setOutlineThickness(5);
	text.setFont(font);*/
}

void Dijkstra::solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window)
{
	for (auto& obstacle : obstacleMap)
	{
		graph.getNode(obstacle).isObstacle = true;
	}

	this->source = source;
	this->target = target;

	auto dCostcomparator = [](Node* leftnode, Node* rightnode)
	{
		return leftnode->fCost < rightnode->fCost;
	};

	Node* sourceNode = &(graph.getNode(source));
	sourceNode->dCost = 0;
	pq.emplace_back(sourceNode);

	while (!pq.empty() && !targetFound)
	{
		pq.sort(dCostcomparator);
		Node* currentNode = pq.front();
		pq.pop_front();
		currentNode->visited = true;
		grid.colorVisitedTile(currentNode->nodeLocation);

		if (currentNode->nodeLocation == target)
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
				continue;
			}
			else
			{
				double newDCost = currentNode->dCost + nodeDistance(currentNode, neighbor);
				if (newDCost < neighbor->dCost)
				{
					neighbor->parent = currentNode;
					neighbor->dCost = newDCost;
					auto find = containsNode.find(neighbor);
					if (find == containsNode.end())
					{
						grid.colorVisitingTile(neighbor->nodeLocation);
						containsNode.insert(neighbor);
						pq.emplace_back(neighbor);
					}
				}
			}
		}
	}
	if (pq.empty() && !targetFound)
	{
		std::cout << "Unable to find target node from source node(Dijkstra)" << std::endl;
	}
}

void Dijkstra::constructPath(Grid& grid)
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

double Dijkstra::nodeDistance(Node* n1, Node* n2)
{
	double xDirection = pow(n1->nodeLocation.x - n2->nodeLocation.x, 2);
	double yDirection = pow(n1->nodeLocation.y - n2->nodeLocation.y, 2);
	return sqrt(xDirection + yDirection);
}
