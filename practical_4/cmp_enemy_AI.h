#pragma once
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent
{
protected:
	sf::Vector2f _direction;
	enum state{ROAMING, ROTATING, ROTATED};
	state _state = ROTATING;

public:
	EnemyAIComponent() = delete;
	explicit EnemyAIComponent(Entity *p);

	void update(double dt) override;
};