#include "Graph.h"
#include <assert.h>

Graph::Graph(std::pair<int, int> numTiles)
{
	numXTiles = numTiles.first;
	numYTiles = numTiles.second;
	
	//Creating the nodes of the graph;
	for (int i = 0; i < numXTiles; i++)
	{
		for (int j = 0; j < numYTiles; j++)
		{
			nodes.emplace_back(i, j);
		}
	}

	//Filling in the neighbors of individual nodes
	for (int x = 0; x < numXTiles; x++)
	{
		for (int y = 0; y < numYTiles; y++)
		{
			int currentNode = x * numXTiles + y;
			if (y > 0)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[x * numXTiles + (y - 1)]);
			}
			if (y < numYTiles - 1)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[x * numXTiles + (y + 1)]);
			}
			if (x > 0)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x - 1) * numXTiles + y]);
			}
			if (x < numXTiles - 1)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x + 1) * numXTiles + y]);
			}

			if (x > 0 && y > 0)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x - 1) * numXTiles + (y - 1)]);
			}
			if (x < numXTiles - 1 && y < numYTiles - 1)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x + 1) * numXTiles + (y + 1)]);
			}
			if (x < numXTiles - 1 && y > 0)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x + 1) * numXTiles + (y - 1)]);
			}
			if (x > 0 && y < numYTiles - 1)
			{
				nodes[currentNode].neighbors.emplace_back(&nodes[(x - 1) * numXTiles + (y + 1)]);
			}
		}
	}
}

Node& Graph::getNode(const Location& loc)
{
	assert(loc.x * numXTiles + loc.y <= numXTiles * numYTiles);
	assert(loc.x >= 0 && loc.y >= 0);
	return nodes[loc.x * numXTiles + loc.y];
}

void Graph::resetGraph()
{
	for (auto& node : nodes)
	{
		node.parent = nullptr;
		node.visited = false;
		node.isObstacle = false;
		node.dCost = INFINITY;
		node.gCost = INFINITY;
		node.hCost = INFINITY;
	}
}
