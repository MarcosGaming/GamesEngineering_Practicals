#include "cmp_player_movement.h"

// Constructor
PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p){}

// Update
void PlayerMovementComponent::update(double dt)
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
}
