#pragma once
#include "Location.h"
#include "Grid.h"
#include <vector>
#include <iostream>
 
class Algorithm
{
public:
	virtual void solveAlgorithm(const Location& source, const Location& target, const std::vector<Location>& obstacleMap, Grid& grid, sf::RenderWindow& window) = 0;
	virtual void constructPath(Grid& grid) = 0;
};

