#include "steering_states.h"
#include "components\cmp_sprite.h"

// Stationary state
void StationaryState::execute(Entity* owner, double dt) noexcept
{
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(sf::Color::Blue);
}

// Seek state
SeekState::SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : _steering(owner.get(), player.get(), 50.0f) {}
void SeekState::execute(Entity* owner, double dt) noexcept
{
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(sf::Color::Green);
	auto output = _steering.getSteering();
	owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}

// Flee state
FleeState::FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : _steering(owner.get(), player.get(), 50.0f) {}
void FleeState::execute(Entity* owner, double dt) noexcept
{
	auto s = owner->get_components<ShapeComponent>();
	s[0]->getShape().setFillColor(sf::Color::Yellow);
	auto output = _steering.getSteering();
	owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}