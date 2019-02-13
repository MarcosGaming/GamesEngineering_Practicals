#include "cmp_pickup.h"
#include "maths.h"
#include "cmp_actor_movement.h"

// Constructor
PickUpComponent::PickUpComponent(Entity *p) : _multiplier(1), Component(p){}

// Update
void PickUpComponent::update(double dt)
{
	// Go through all the entities in the scene
	for (auto &e : _ents)
	{
		// If there is an entity in my range
		if (sf::length(e->getPosition() - _parent->getPosition()) < 10.0f)
		{
			// Check that the entity has an actor movement component
			std::vector<std::shared_ptr<ActorMovementComponent>> actors = e->getCompatibleComponents<ActorMovementComponent>();
			if (!actors.empty())
			{
				// Speed up the actor
				actors[0]->setSpeed(actors[0]->getSpeed() + 1 * _multiplier);
				// Delete this entity
				_parent->setForDelete();
				break;
			}
		}
	}
}

// Render
void PickUpComponent::render(){}