#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

Player* player;
Clock globalClock;
Time timer;
Time bestTime;
Time lastTime;
Font font;
Text textTimer;

void Reset()
{
	// Return player to start position
	player->setPosition(ls::getStartTilePos() + Vector2f(50.0f, 50.0f));

	// Set best and last times
	if (bestTime > timer || bestTime == Time::Zero)
	{
		bestTime = timer;
	}
	lastTime = timer;

	// Restart global clock
	globalClock.restart();
}

void Load()
{
	// Load font
	font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	// Set text element to use font
	textTimer.setFont(font);
	// Set the character size to 24 pixels
	textTimer.setCharacterSize(20);
	// Set text position
	textTimer.setPosition(0 - (textTimer.getLocalBounds().width * .5f), gameHeight - 40.0f);

	// Level
	ls::loadLevelFile("res/maze_2.txt");
	// Print level to console
	for (size_t y = 0; y < ls::getHeight(); ++y)
	{
		for (size_t x = 0; x < ls::getWidth(); ++x)
		{
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}

	// Player
	player = new Player();
	player->setPosition(ls::getStartTilePos() + Vector2f(50.0f,50.0f));
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

	// Plater
	player->update(dt);

	// Timer
	timer = globalClock.getElapsedTime();
	textTimer.setString("Best Time: " + to_string(bestTime.asSeconds()) + " || Previous Time: " + to_string(lastTime.asSeconds()) + " || Current Time: " + to_string(timer.asSeconds()));

	// Game over
	if (ls::getTileAt(player->getPosition()) == ls::END)
	{
		Reset();
	}
}

void Render(RenderWindow &window)
{
	ls::render(window);
	player->render(window);
	window.draw(textTimer);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
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