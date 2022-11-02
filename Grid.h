#pragma once
#include <SFML/Graphics.hpp>
#include "Location.h"

// Class for grid tiles
class Grid
{
public:
	//Constructors
	Grid(int screenWidth, int screenHeight, sf::RenderWindow& window, sf::Mouse& mouse);
	~Grid();

	// Members
	int numTilesX;
	int numTilesY;

	sf::RenderWindow& window;
	sf::Mouse& mouse;

	Location srcPosition;
	Location targetPosition;

	std::vector<std::vector<sf::RectangleShape>> TileMap;
	std::vector<Location> obstacleMap;

	//Functions
	
	void drawGrid();
	void resetGrid();
	void setObstacle();
	bool outOfBounds(int x, int y);

	//Getters and setters

	std::pair<int, int> getNumTiles();
	Location getSourcePosition();
	Location getTargetPosition();
	std::vector<Location> getObstacles();
	void colorVisitedTile(const Location& location);
	void colorVisitingTile(const Location& location);
	void colorPathTile(const Location& location);


private:
	const int TILE_DIMENSIONS = 30;

	//Tile Colors
	sf::Color openTileColor = sf::Color::White;
	sf::Color visitingTileColor = sf::Color::Cyan;
	sf::Color visitedTileColor = sf::Color::Blue;
	sf::Color pathTileColor = sf::Color::Yellow;
	sf::Color obstacleTileColor = sf::Color::Black;
	sf::Color srcTileColor = sf::Color::Green;
	sf::Color targetTileColor = sf::Color::Red;

};

