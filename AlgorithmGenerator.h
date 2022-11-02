#pragma once

#include "Algorithm.h"
#include <string>
#include <memory>
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "Astar.h"

class AlgorithmGenerator
{
public:
	static std::unique_ptr<Algorithm> generateAlgorithm(const std::string& AlgorithmType, Graph& graph)
	{
		if (AlgorithmType == "BFS")
		{
			return std::make_unique<BFS>(graph);
		}
		else if (AlgorithmType == "DFS")
		{
			return std::make_unique<DFS>(graph);
		}
		else if (AlgorithmType == "Dijkstra")
		{
			return std::make_unique<Dijkstra>(graph);
		}
		else if (AlgorithmType == "A*")
		{
			return std::make_unique<AStar>(graph);
		}
		else return nullptr;
	}
};