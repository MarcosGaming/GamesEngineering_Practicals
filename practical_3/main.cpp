#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

// AS SAM IF THIS IS OKAY OR IF AS BEING SMART POINTERS IT SHOULD BE DIFFERENT??
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
	// ASK SAM HOW DOES THIS METHOD WORK EXACTLY
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