#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite
{
public:
	// Updates all bullets
	static void Update(const float &dt);
	// Render all bullets
	static void Render(sf::RenderWindow &window);
	// Chose an inactive bullet and use it
	static void Fire(const sf::Vector2f &pos, const bool mode);
	
	~Bullet() = default;
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	// Called by the static update
	void _Update(const float &dt);
	// Never called 
	Bullet();
	// False means player bullet, true means invader bullet
	bool _mode;
};