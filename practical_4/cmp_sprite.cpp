#include "cmp_sprite.h"
#include "system_renderer.h"

// Constructor
ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

// Update
void ShapeComponent::update(double dt)
{
	_shape->setPosition(_parent->getPosition());
}

// Render
void ShapeComponent::render()
{
	Renderer::queue(_shape.get());
}

// Get shape method
sf::Shape &ShapeComponent::getShape() const
{
	return *_shape;
}