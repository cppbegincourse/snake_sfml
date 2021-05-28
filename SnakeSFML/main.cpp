#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "Snake");
	window.setFramerateLimit(60);

	bool isRunning = true;

	sf::Texture textureTerrain;
	if (!textureTerrain.loadFromFile("snakeset.png")) {
		std::cerr << "Can't load texture" << endl;
		return 1;
	}

	sf::Sprite treeSprite;
	treeSprite.setTexture(textureTerrain);
	treeSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	sf::Sprite grassSprite;
	grassSprite.setTexture(textureTerrain);
	grassSprite.setTextureRect(sf::IntRect(0, 64, 64, 64));

	sf::Sprite snakeSprite;
	snakeSprite.setTexture(textureTerrain);
	snakeSprite.setTextureRect(sf::IntRect(128, 128, 64, 64));

	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Draw sprites example
		// Draw tree sprite
		// Format: <sprite>.setPosition(x, y), where x, y - coordinates in pixels where sprite will be drawn
		treeSprite.setPosition(0, 0);
		window.draw(treeSprite);

		// Draw grass sprite
		grassSprite.setPosition(64, 0);
		window.draw(grassSprite);

		// Draw grass sprite
		grassSprite.setPosition(128, 0);
		window.draw(grassSprite);

		// Draw snake sprite on top of grass
		snakeSprite.setPosition(128, 0);
		window.draw(snakeSprite);

		// TODO: Draw game field filled with grass and trees on border

		window.display();
	}

	return 0;
}