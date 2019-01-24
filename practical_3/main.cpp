#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

void Load()
{
	
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
}

void Render(RenderWindow &window)
{

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