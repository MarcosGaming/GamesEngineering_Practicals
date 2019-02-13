#include "cmp_actor_movement.h"
#include"LevelSystem.h"

// Constructor
ActorMovementComponent::ActorMovementComponent(Entity *p) : _speed(100), Component(p) {}

// Speed methods
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float s) { _speed = s; }

// Valid movement
bool ActorMovementComponent::validMove(const sf::Vector2f& m)
{
	return (LevelSystem::getTileAt(m) != LevelSystem::WALL);
}

// Movement methods
void ActorMovementComponent::move(const sf::Vector2f& m)
{
	sf::Vector2f pos = _parent->getPosition() + m;
	if (validMove(pos))
	{
		_parent->setPosition(pos);
	}
}
void ActorMovementComponent::move(float x, float y)
{
	move(sf::Vector2f(x, y));
}

// Update
void ActorMovementComponent::update(double dt) {}

// Render
void ActorMovementComponent::render() {}