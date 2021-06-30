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
void DrawSprite(sf::Sprite& sprite, int col, int row);
void Draw();
void DrawGameField();
void Update(int dt);
void MoveSnake();

const int SNAKE_MOVE_TIME = 300;
const int TILE_SIZE = 64;

// Horizontal amount of tiles
const int GAME_FIELD_SIZE_H = 15;
// Vertical amount of tiles
const int GAME_FIELD_SIZE_V = 15;

// Array with tile codes
char gameField[15][15];

int snakeMoveTimer = SNAKE_MOVE_TIME;

sf::RenderWindow window(sf::VideoMode(GAME_FIELD_SIZE_H * TILE_SIZE, GAME_FIELD_SIZE_V * TILE_SIZE), "Snake");
sf::Sprite treeSprite;
sf::Sprite grassSprite;
sf::Sprite snakeSprite;

sf::Texture textureTerrain;

struct SnakeSegment
{
	SnakeSegment(int row, int col) :
		col(col),
		row(row)
	{};

	void Draw()
	{
		DrawSprite(snakeSprite, col, row);
	};

	void Move()
	{
		col += deltaCol;
		row += deltaRow;
	}

	int col;
	int row;

	// Delta variables show us direction where snake will move on each frame
	// Initial moving direction is Left
	int deltaCol = -1;
	int deltaRow = 0;
};

struct Snake {
	SnakeSegment segments[4] = {
		{4, 5},
		{4, 6},
		{4, 7},
		{4, 8},
	};

	// Get the first snake segment as head
	SnakeSegment* head = segments;
	int size = 4;

	void Draw()
	{
		for (SnakeSegment& snakeSeg : segments)
		{
			snakeSeg.Draw();
		}
	}

	void Move() {
		snake.head->Move();

		for (int i = 1; i < size; i++)
		{
			auto& prevSeg = segments[i - 1];
			auto& curSeg = segments[i];

			curSeg.deltaCol = prevSeg.deltaCol;
			curSeg.deltaRow = prevSeg.deltaRow;

			curSeg.Move();
		}
	}
} snake;

int snakeSize = 4;

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
	treeSprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));

	grassSprite.setTexture(textureTerrain);
	grassSprite.setTextureRect(sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE));

	snakeSprite.setTexture(textureTerrain);
	snakeSprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

void InitGameField()
{
	// Tile codes in gameField array:
	// '#' char means tree
	// 's' char means snake
	// ' ' empty tile, draws it as grass

	for (int row = 0; row < GAME_FIELD_SIZE_V; row++)
	{
		for (int col = 0; col < GAME_FIELD_SIZE_H; col++)
		{
			if (col == 0 || col == GAME_FIELD_SIZE_H - 1
				|| row == 0 || row == GAME_FIELD_SIZE_V)
			{
				gameField[row][col] = '#';
			}
			else
			{

			// ' ' empty tile, draws it as grass
			gameField[row][col] = ' ';
			}
		}
	}

	/*gameField[4][5] = 's';
	gameField[4][6] = 's';
	gameField[4][7] = 's';
	gameField[4][8] = 's';*/
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
	if (gameField[snake.head->row][snake.head->col - 1] == '#')
	{
		cout << "You loose!" << endl;
		exit(1);
	}

	snake.Move();
}

void Draw()
{
	DrawGameField();

	snake.Draw();
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
				grassSprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
				window.draw(grassSprite);
			}
			else if (tile == '#')
			{
				treeSprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
				window.draw(treeSprite);
			}
			else if (tile == 's')
			{
				grassSprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
				window.draw(grassSprite);

				snakeSprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
				window.draw(snakeSprite);
			}
		}
	}
}

void DrawSprite(sf::Sprite& sprite, int col, int row)
{
	sprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
	window.draw(sprite);
}