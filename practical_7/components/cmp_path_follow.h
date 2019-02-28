#pragma once
#include <ecm.h>

class PathfindingComponent : public Component
{
protected:
	std::vector<sf::Vector2i> _path;
	size_t _index = 0;
	double _elapsed = 0.0;

public:
	PathfindingComponent() = delete;
	explicit PathfindingComponent(Entity *p);

	void update(double) override;
	void render() override;
	void setPath(std::vector<sf::Vector2i>& path);
};