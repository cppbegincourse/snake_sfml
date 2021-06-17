#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

void Init();
void SetupWindow();
void InitSprites();
void InitGameField();
void Draw();
void DrawGameField();

char gameField[15][15];

sf::RenderWindow window(sf::VideoMode(960, 960), "Snake");
sf::Sprite treeSprite;
sf::Sprite grassSprite;
sf::Sprite snakeSprite;

sf::Texture textureTerrain;

void SetupWindow()
{
	window.setFramerateLimit(60);
}

void InitSprites()
{
	
	if (!textureTerrain.loadFromFile("snakeset.png")) {
		std::cerr << "Can't load texture" << endl;
		exit(1);
	}

	treeSprite.setTexture(textureTerrain);
	treeSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	grassSprite.setTexture(textureTerrain);
	grassSprite.setTextureRect(sf::IntRect(0, 64, 64, 64));

	snakeSprite.setTexture(textureTerrain);
	snakeSprite.setTextureRect(sf::IntRect(128, 128, 64, 64));
}

void InitGameField()
{
	// Tile codes in gameField array:
	// '#' char means tree
	// 's' char means snake
	// ' ' empty tile, draws it as grass

	for (int row = 0; row < 15; row++)
	{
		for (int col = 0; col < 15; col++)
		{
			// ' ' empty tile, draws it as grass
			gameField[row][col] = ' ';
		}
	}
}

void Init()
{
	SetupWindow();

	InitSprites();

	InitGameField();
}

int main()
{
	Init();

	bool isRunning = true;

	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Draw();

		window.display();
	}

	return 0;
}

void Draw()
{
	DrawGameField();
}

void DrawGameField()
{
	for (int row = 0; row < 15; row++)
	{
		for (int col = 0; col < 15; col++)
		{
			char tile = gameField[row][col];

			if (tile == ' ')
			{
				grassSprite.setPosition(col * 64, row * 64);
				window.draw(grassSprite);
			}
			else if (tile == '#')
			{
				treeSprite.setPosition(col * 64, row * 64);
				window.draw(treeSprite);
			}
			else if (tile == 's')
			{
				grassSprite.setPosition(col * 64, row * 64);
				window.draw(grassSprite);

				snakeSprite.setPosition(col * 64, row * 64);
				window.draw(snakeSprite);
			}
		}
	}
}
