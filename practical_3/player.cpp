#include "player.h"

using namespace std;
using namespace sf;

void Player::update(double dt)
{
	// Move the player in four directions based on the keys
	float directionY = 0.0f;
	float directionX = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		directionY--;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		directionX--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		directionY++;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		directionX++;
	}
	move(Vector2f(dt * directionX * _speed, dt * directionY * _speed));

	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f))
{
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const
{
	window.draw(*_shape);
}