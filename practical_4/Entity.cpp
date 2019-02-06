#include "Entity.h"

// Constructor
Entity::Entity(std::unique_ptr<sf::Shape> shp) : _shape(std::move(shp)) {}

// Position methods
const sf::Vector2f Entity::getPosition() { return _position; }
void Entity::setPosition(sf::Vector2f &pos) { _position = pos; }
void Entity::move(const sf::Vector2f &pos) { _position += pos; }

// Update Entity
void Entity::update(const double dt) { _shape->setPosition(_position); }

// EntityManager update
void EntityManager::update(double dt)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->update(dt);
	}
}

// EntityManager render
void EntityManager::render(sf::RenderWindow &window)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->render(window);
	}
}