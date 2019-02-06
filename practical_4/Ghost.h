#pragma once
#include "Entity.h"

class Ghost : public Entity
{
private:
	float _speed;
public:
	Ghost() = delete;
	Ghost(sf::Color c);

	void update(double dt) override;
	void render(sf::RenderWindow &window) const override;
};