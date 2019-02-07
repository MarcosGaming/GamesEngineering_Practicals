#include <SFML/Graphics.hpp>
#include "ecm.h"
#include "Player.h"
#include "Ghost.h"
#include "system_renderer.h"
#include "pacman.h"

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void Load()
{
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;
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

	activeScene->update(dt);
}

void Render(RenderWindow &window)
{
	Renderer::initialise(window);
	activeScene->render();
	// Flush to screen
	Renderer::render();
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
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