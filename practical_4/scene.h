#pragma once
#include "ecm.h"

class Scene
{
public:
	// Constructor
	Scene() = default;
	//Destructor
	virtual ~Scene() = default;
	// Other methods
	virtual void update(double dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	// Properties
	EntityManager _ents;
};