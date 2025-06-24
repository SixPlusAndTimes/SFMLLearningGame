#include <iostream>
#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <ResourceHolder.hpp>
#include <SceneNode.hpp>

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << "\n";
	}

}