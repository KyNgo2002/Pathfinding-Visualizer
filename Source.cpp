#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;

int main()
{
	cout << "Hello world" << endl;
	Game game(900, 900);
	game.run();
	return 0;
}