#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "LevelSystem.h"
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

Player* player;

void Load()
{
	player = new Player();
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

	player->update(dt);
}

void Render(RenderWindow &window)
{
	player->render(window);
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