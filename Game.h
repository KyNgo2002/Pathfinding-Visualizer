#pragma once

#include <SFML/Graphics.hpp>
#include "Algorithm.h"
#include "Grid.h"
#include "Graph.h"
#include "AlgorithmGenerator.h"

class Game
{
public:
	//Constructors/Destructors
	Game(int width, int height);
	~Game();

	//Functions that allow window to run;
	void run();
	void update();
	void render();
	void updatePollEvents();

private:
	// Members
	sf::RenderWindow window;
	sf::Event event;
	sf::Mouse mouse;
	sf::Font font;
	sf::Text text;


	Grid grid;
	Graph graph;

	int screenWidth;
	int screenHeight;
	
	std::string algorithmType;

	bool solving = false;

	std::unique_ptr<Algorithm> algorithm;

	bool movingSrc = false;
	bool movingTarget = false;
};

