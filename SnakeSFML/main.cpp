#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>

using namespace std;

chrono::milliseconds elapsedTime;
chrono::milliseconds timer;

void Init();
void InitTimer();
void SetupWindow();
void InitSprites();
void InitGameField();
void Draw();
void DrawGameField();
void Update(int dt);
void MoveSnake();

// Array with tile codes
char gameField[15][15];

int snakeHeadCol = 8;
int snakeHeadRow = 4;

const int SNAKE_MOVE_TIME = 300;
int snakeMoveTimer = SNAKE_MOVE_TIME;

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
			if (col == 14)
				gameField[row][col] = '#';
			else
			{

			// ' ' empty tile, draws it as grass
			gameField[row][col] = ' ';
			}
		}
	}

	gameField[4][5] = 's';
	gameField[4][6] = 's';
	gameField[4][7] = 's';
	gameField[4][8] = 's';
}

void Init()
{
	SetupWindow();

	InitSprites();

	InitGameField();

	InitTimer();
}

void InitTimer()
{
	timer = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
}

int main()
{
	Init();

	bool isRunning = true;

	while (isRunning)
	{
		std::chrono::milliseconds newTime = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
		elapsedTime = newTime - timer;
		timer = newTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Update(elapsedTime.count());

		Draw();

		window.display();
	}

	return 0;
}

void Update(int dt)
{
	snakeMoveTimer -= dt;

	if (snakeMoveTimer <= 0)
	{
		MoveSnake();
		snakeMoveTimer = SNAKE_MOVE_TIME;
	}
}

void MoveSnake()
{
	// Crash to the tree
	if (gameField[snakeHeadRow][snakeHeadCol + 1] == '#')
	{
		cout << "You loose!" << endl;
		exit(1);
	}

	gameField[snakeHeadRow][snakeHeadCol - 3] = ' ';
	snakeHeadCol++;
	gameField[snakeHeadRow][snakeHeadCol] = 's';
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
