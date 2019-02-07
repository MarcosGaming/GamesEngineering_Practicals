#include "ecm.h"

// Entity class 
//Constructor
Entity::Entity(){}

// Update method
void Entity::update(double dt) { }

// Render methods
void Entity::render(){}

// Position methods
const sf::Vector2f &Entity::getPosition() const { return _position; }
void Entity::setPosition(const sf::Vector2f &pos) { _position = pos; }

// Deletion methods
bool Entity::is_fordeletion() const { return _fordeletion; }
void Entity::setForDelete() { _fordeletion = true; }

// Rotation methods
float Entity::getRotation() const { return _rotation; }
void Entity::setRotation(float rot) { _rotation = rot; }

// Alive methods
bool Entity::isAlive() const { return _alive; }
void Entity::setAlive(bool alv) { _alive = alv; }

// Visible methods
bool Entity::isVisible() const { return _visible; }
void Entity::setVisible(bool vis) { _visible = vis; }

// Component class
// Constructor
Component::Component(const Entity *p) { _parent = p; }

// Destructor
Component::~Component(){}

// Deletion method
bool Component::is_fordeletion() const { return _fordeletion; }

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