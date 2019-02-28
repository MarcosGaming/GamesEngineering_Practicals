#pragma once
#include <ecm.h>

class BasicMovementComponent : public Component 
{
protected:
	float _speed;
	bool validMove(const sf::Vector2f&);

public:
	BasicMovementComponent() = delete;
	explicit BasicMovementComponent(Entity *p);

	void update(double) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
};
