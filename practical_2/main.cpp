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

std::vector<Ship *> ships;
Player* player;
int invaders_left = invaders_columns * invaders_rows;
bool gameOver = false;

void Load()
{
	// Load font
	font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(24);
	// Set string
	text.setString("GAME OVER");
	// Set text position
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), gameHeight * 0.5);

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
	
	player = new Player();
	ships.push_back(player);
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

	for (auto &s : ships)
	{
		s->Update(dt);
	}

	Bullet::Update(dt);
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
	}
	else
	{
		window.draw(text);
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