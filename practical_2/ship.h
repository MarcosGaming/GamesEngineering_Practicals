#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite
{
protected:
	sf::IntRect _sprite;
	// Default constructor is hidden
	Ship();
public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor making this class abstract
	virtual ~Ship() = 0;
	// Update, virtual so it can be overrided
	virtual void Update(const float &dt);
};

class Invader : public Ship 
{
public:
	// Properties
	static bool direction;
	static float speed;

	// Constructors
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();

	// Methods
	void Update(const float &dt) override;
};

class Player : public Ship
{
	// Properties
	static float speed;
public:
	Player();
	void Update(const float &dt) override;
};