#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Font font;
Text text;
Text scoreMarker;

std::vector<Ship *> ships;
Player* player;
MotherShip* motherShip;
int invaders_left = invaders_columns * invaders_rows;
bool gameOver = false;
int score = 0;
int initialSpeed = 60;
int level = 1;

void Load()
{
	// Load font
	font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	scoreMarker.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(24);
	scoreMarker.setCharacterSize(20);
	// Set string
	text.setString("GAME OVER \nTo restart the game press R");
	scoreMarker.setString("Your Score: " + to_string(score));
	// Set text position
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), gameHeight * 0.5f - 20.0f);
	scoreMarker.setPosition(10.0f, 10.0f);

	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spridesheet" << endl;
	}

	for (int r = 0; r < invaders_rows; r++)
	{
		auto rect = sf::IntRect(r * 32, 0, 32, 32);
		for (int c = 0; c < invaders_columns; c++)
		{
			Vector2f position = Vector2f(220 + 32*c, 100 +32*r);
			Invader* inv = new Invader(rect, position);
			if (r == invaders_rows - 1)
			{
				inv->_bottom = true;
			}
			ships.push_back(inv);
		}
	}
	
	motherShip = new MotherShip(sf::IntRect(192, 0, 64, 32), Vector2f(gameWidth * 0.5, 50));
	ships.push_back(motherShip);
	player = new Player();
	ships.push_back(player);
}

void Reset()
{
	if (gameOver)
	{
		gameOver = false;
		// Reset speed
		Invader::speed = initialSpeed;
		// Restart the score
		score = 0;
		// Restart level
		level = 1;
	}
	else
	{
		// Increase difficulty
		level++;
	}
	// Remove all ships
	ships.clear();
	// Reset number of invaders left
	invaders_left = invaders_columns * invaders_rows;
	Load();
	Invader::speed = initialSpeed + level * 10;
}

void Update(RenderWindow &window)
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	// Update score
	scoreMarker.setString("Your Score: " + to_string(score));

	for (auto &s : ships)
	{
		s->Update(dt);
	}

	Bullet::Update(dt);

	// Restart the game
	if (gameOver && Keyboard::isKeyPressed(Keyboard::R))
	{
		Reset();
	}
	static float restartTime = 1.0f;
	restartTime -= dt;
	if (invaders_left == 0 && restartTime <= 0)
	{
		restartTime = 1.0f;
		Reset();
	}
}

void Render(RenderWindow &window)
{
	if (!gameOver)
	{
		// Draw Everything
		for (const auto s : ships)
		{
			window.draw(*s);
		}
		Bullet::Render(window);
		window.draw(scoreMarker);
	}
	else
	{
		window.draw(text);
		window.draw(scoreMarker);
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}