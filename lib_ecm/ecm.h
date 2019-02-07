#pragma once
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include <SFML/Graphics.hpp>

// Forward declare
class Component;

class Entity
{
protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive;		// Should be updated
	bool _visible;		// Should be rendered
	bool _fordeletion;	// Should be deleted

public:
	Entity();
	virtual ~Entity();
	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f &getPosition() const;
	void setPosition(const sf::Vector2f &_position);
	bool is_fordeletion() const;
	void setForDelete();
	float getRotation() const;
	void setRotation(float _rotation);
	bool isAlive() const;
	void setAlive(bool _alive);
	bool isVisible() const;
	void setVisible(bool _visible);

	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params)
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}
};

// Component class
class Component
{
protected:
	const Entity *_parent;
	bool _fordeletion;		
	explicit Component(const Entity *p);

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};

struct EntityManager
{
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render(sf::RenderWindow &window);
};