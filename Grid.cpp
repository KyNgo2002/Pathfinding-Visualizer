#include "Grid.h"
#include <iostream>

//Grid constructor
Grid::Grid(int screenWidth, int screenHeight, sf::RenderWindow& window, sf::Mouse& mouse) : 
	window(window),
	mouse(mouse)
{
	numTilesX = screenWidth / TILE_DIMENSIONS;
	numTilesY = screenHeight / TILE_DIMENSIONS;
	TileMap.resize(numTilesX);

	srcPosition = { 0, 0 };
	targetPosition = { numTilesX - 1, numTilesY - 1 };

	for (int i = 0; i < numTilesX; i++)
	{
		for (int j = 0; j < numTilesY; j++)
		{
			TileMap[i].emplace_back(sf::Vector2f(TILE_DIMENSIONS, TILE_DIMENSIONS));
		}
	}

	for (int x = 0; x < numTilesX; x++)
	{
		for (int y = 0; y < numTilesY; y++)
		{
			TileMap[x][y].setPosition(sf::Vector2f(x * TILE_DIMENSIONS, y * TILE_DIMENSIONS));
			TileMap[x][y].setFillColor(openTileColor);
			TileMap[x][y].setOutlineColor(sf::Color::Black);
			TileMap[x][y].setOutlineThickness(-1.0f);
		}
	}

	TileMap[srcPosition.x][srcPosition.y].setFillColor(srcTileColor);
	TileMap[targetPosition.x][targetPosition.y].setFillColor(targetTileColor);

}

Grid::~Grid()
{
}

void Grid::drawGrid()
{
	for (const auto& Row : TileMap)
	{
		for (const auto& Tile : Row)
		{
			window.draw(Tile);
		}
	}
}

void Grid::resetGrid()
{
	for (auto& row : TileMap)
	{
		for (auto& tile : row)
		{
			auto tileColor = tile.getFillColor();
			if (tileColor == obstacleTileColor || tileColor == srcTileColor || tileColor == targetTileColor)
			{
				continue;
			}
			tile.setFillColor(openTileColor);
		}
	}
}

void Grid::setObstacle()
{
	int x = mouse.getPosition(window).x / TILE_DIMENSIONS;
	int y = mouse.getPosition(window).y / TILE_DIMENSIONS;

	Location mouseLocation = { x, y };

	std::cout << "x: " << x << "y: " << y << std::endl;
	if (outOfBounds(x, y)) return;

	if (TileMap[x][y].getFillColor() == obstacleTileColor)
	{
		TileMap[x][y].setFillColor(openTileColor);
		obstacleMap.erase(std::remove(obstacleMap.begin(), obstacleMap.end(), mouseLocation), obstacleMap.end());
		std::cout <<  "ObstacleMap size: " << obstacleMap.size() << std::endl;
		return;
	}

	if (TileMap[x][y].getFillColor() == openTileColor)
	{
		TileMap[x][y].setFillColor(obstacleTileColor);
		obstacleMap.emplace_back(mouseLocation);
		std::cout << "ObstacleMap size: " << obstacleMap.size() << std::endl;
		return;
	}
	
}

bool Grid::outOfBounds(int x, int y)
{
	return (x < 0 || y < 0 || x >= numTilesX || y >= numTilesY);
}

std::pair<int, int> Grid::getNumTiles()
{
	return std::pair<int, int>(numTilesX, numTilesY);
}

Location Grid::getSourcePosition()
{
	return srcPosition;
}

Location Grid::getTargetPosition()
{
	return targetPosition;
}

std::vector<Location> Grid::getObstacles()
{
	return obstacleMap;
}

void Grid::colorVisitedTile(const Location& location)
{
	if (location == srcPosition || location == targetPosition) return;
	TileMap[location.x][location.y].setFillColor(visitedTileColor);
}

void Grid::colorVisitingTile(const Location& location)
{
	if (location == srcPosition || location == targetPosition) return;
	TileMap[location.x][location.y].setFillColor(visitingTileColor);
}

void Grid::colorPathTile(const Location& location)
{
	if (location == srcPosition || location == targetPosition) return;
	TileMap[location.x][location.y].setFillColor(pathTileColor);
}

