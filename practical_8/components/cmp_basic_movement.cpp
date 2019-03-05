#include "cmp_basic_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <engine.h>

using namespace sf;
using namespace std;

// Constructor
BasicMovementComponent::BasicMovementComponent(Entity *p) : _speed(100.0f), Component(p){}

// Chekcs the keyboard and moves the player
void BasicMovementComponent::update(double dt)
{
	Vector2f direction;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction.x -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction.x += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		direction.y -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		direction.y += 1.0f;
	}

	move(_speed * (float)dt * normalize(direction));
}

// Check if the player has done a valid move
bool BasicMovementComponent::validMove(const Vector2f& pos)
{
	if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x || 
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y)
	{
		return false;
	}
	return true;
}

// Move the component's parent 
void BasicMovementComponent::move(const Vector2f& p)
{
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos))
	{
		_parent->setPosition(new_pos);
	}
}

// Move the component's parent
void BasicMovementComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}
