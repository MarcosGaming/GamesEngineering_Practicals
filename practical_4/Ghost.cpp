#include "Ghost.h"

// Constructor
Ghost::Ghost(sf::Color c) : _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.0f))
{
	_shape->setFillColor(c);
	_shape->setOrigin(sf::Vector2f(25.0f, 25.0f));
}

// Render
void Ghost::render(sf::RenderWindow &window) const { window.draw(*_shape); }

// Update
void Ghost::update(double dt)
{
	// Directions
	float directionY = 0.0f;
	float directionX = 0.0f;
	// Random X direction
	float random = std::rand() % 2 - 1;
	directionX = ((random >= 0) ? 1.0f : -1.0f);
	// Random Y direction
	random = std::rand() % 2 - 1;
	directionY = ((random >= 0) ? 1.0f : -1.0f);

	move(sf::Vector2f(dt * directionX * _speed, dt * directionY * _speed));

	Entity::update(dt);
}
