#pragma once

#include "steering.h"
#include "components\cmp_state_machine.h"

class StationaryState : public State
{
public:
	StationaryState() = default;
	void execute(Entity*, double) noexcept override;
};

class SeekState : public State
{
private:
	Seek _steering;

public:
	SeekState(std::shared_ptr<Entity>, std::shared_ptr<Entity>);
	void execute(Entity*, double) noexcept override;
};

class FleeState : public State
{
private:
	Flee _steering;

public:
	FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player);
	void execute(Entity*, double) noexcept override;
};
