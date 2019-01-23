#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite
{
protected:
	sf::IntRect _sprite;
	bool _exploded;
	// Default constructor is hidden
	Ship();
public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor making this class abstract
	virtual ~Ship() = 0;
	// Update, virtual so it can be overrided
	virtual void Update(const float &dt);
	bool is_exploded() const;
	virtual void Explode();
	bool _bottom;
};

class Invader : public Ship 
{
public:
	// Properties
	static bool direction;
	static float speed;
	float explosiontime;

	// Constructors
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();

	// Methods
	void Update(const float &dt) override;
	void Explode();
};

class Player : public Ship
{
	// Properties
	static float speed;
public:
	Player();
	void Update(const float &dt) override;
	void Explode();
};