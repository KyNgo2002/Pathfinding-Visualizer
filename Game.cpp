#include "Game.h"
#include <thread>
#include <iostream>


// Constructors
Game::Game(int width, int height) :
	screenWidth(width),
	screenHeight(height),
	window(sf::VideoMode(width, height), "Pathfinding Visualizer", sf::Style::Close | sf::Style::Titlebar),
	grid(width, height, window, mouse),
	graph(grid.getNumTiles())
{
	this->window.setFramerateLimit(60);
	/*algorithmType = "Select an Algorithm 1-4";
	if (!font.loadFromFile("fonts/arial.ttf")) {}
	text.setString(algorithmType);
	text.setPosition(sf::Vector2f(320, 0));
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(25);
	text.setOutlineThickness(5);
	text.setFont(font);*/
}

//Destructor
Game::~Game()
{
}

// Main game loop
void Game::run()
{
	while (this->window.isOpen())
	{
		this->update();
		this->render();
	}
}

// Updates Pathfinding Logic
void Game::update()
{
	this->updatePollEvents();
	if (mouse.isButtonPressed(sf::Mouse::Button::Left))
	{
		grid.setObstacle();
		std::this_thread::sleep_for(std::chrono::milliseconds(90));
		return;
	}
	if (!solving)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			grid.resetGrid();
			graph.resetGraph();
			algorithmType = "BFS";
			std::cout << "BFS" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			grid.resetGrid();
			graph.resetGraph();
			algorithmType = "DFS";
			std::cout << "DFS" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			grid.resetGrid();
			graph.resetGraph();
			algorithmType = "Dijkstra";
			std::cout << "Dijkstra" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			grid.resetGrid();
			graph.resetGraph();
			algorithmType = "A*";
			std::cout << "A*" << std::endl;
		}
		algorithm = AlgorithmGenerator::generateAlgorithm(algorithmType, graph);
		//text.setString(algorithmType);
	}



	if (algorithm != nullptr)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			solving = true;
			std::cout << "Now solving: " << algorithmType << std::endl;
		}
	}

	if (solving)
	{
		Location sourcePosition = grid.getSourcePosition();
		Location targetPosition = grid.getTargetPosition();
		algorithm->solveAlgorithm(sourcePosition, targetPosition, grid.getObstacles(), grid, window);
		algorithm->constructPath(grid);
		solving = false;
	}
}

// Renders elements to the window
void Game::render()
{
	this->window.clear();
	grid.drawGrid();
	//this->window.draw(text);
	this->window.display();
}

// While the window is open, repeatedly poll for user events.
void Game::updatePollEvents()
{
	// Polls user events through an event object(Game.h)
	while (this->window.pollEvent(event))
	{
		// Clicked close window
		if (event.Event::type == sf::Event::Closed)
		{
			this->window.close();
		}
		// Clicked escape
		//if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
		//{
		//	this->window.close();
		//}
	}
}
