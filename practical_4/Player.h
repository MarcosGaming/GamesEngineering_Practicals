#pragma once
#include "ecm.h"

class Player : public Entity
{
private:
	float _speed;

public:
	Player();

	void update(double dt) override;
	void render(sf::RenderWindow &window) const override;
};