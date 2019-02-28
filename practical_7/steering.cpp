#include "steering.h"

using namespace sf;

SteeringOutput Seek::getSteering() const noexcept
{
	SteeringOutput steering;
	steering.direction = normalize(_target->getPosition() - _character->getPosition()) * _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput Flee::getSteering() const noexcept
{
	SteeringOutput steering;
	steering.direction = normalize(_character->getPosition() - _target->getPosition()) * _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}