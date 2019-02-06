#include "Player.h"

// Constructor
Player::Player() : _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.0f))
{
	_shape->setFillColor(sf::Color::Yellow);
	_shape->setOrigin(sf::Vector2f(25.0f, 25.0f));
}

// Render
void Player::render(sf::RenderWindow &window) const { window.draw(*_shape); }

// Update
void Player::update(double dt)
{
	// Directions
	float directionY = 0.0f;
	float directionX = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		directionY--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		directionX--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		directionY++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		directionX++;
	}

	move(sf::Vector2f(dt * directionX * _speed, dt * directionY * _speed));
	
	Entity::update(dt);
}