#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer
{
	void initialise(sf::RenderWindow &);
	sf::RenderWindow &getWindow();

	void shutdown();
	void queue(const sf::Drawable *s);
	void render();
};