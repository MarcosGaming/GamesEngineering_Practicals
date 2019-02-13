#pragma once
#include "ecm.h"

class ActorMovementComponent : public Component
{
protected:
	bool validMove(const sf::Vector2f& m);
	float _speed;

public:
	explicit ActorMovementComponent(Entity *p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float s);

	void move(const sf::Vector2f& m);
	void move(float x, float y);

	virtual void render() override;
	virtual void update(double dt) override;
};