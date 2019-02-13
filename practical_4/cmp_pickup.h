#pragma once
#include "ecm.h"

class PickUpComponent : public Component
{
public:
	PickUpComponent() = delete;
	explicit PickUpComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	std::vector<std::shared_ptr<Entity>> _ents;
	float _multiplier;
};