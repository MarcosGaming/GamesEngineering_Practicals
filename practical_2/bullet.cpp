#include "bullet.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet() : Sprite() { setTexture(spritesheet); }

void Bullet::Update(const float &dt)
{
	for (int i = 0; i < 256; i++)
	{
		bullets[i]._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow &window)
{
	for (int i = 0; i < 256; i++)
	{
		window.draw(bullets[i]);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode)
{
	if (mode)
	{
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
	}
	else
	{
		bullets[bulletPointer].setTextureRect(IntRect(32, 32, 32, 32));
	}
	bullets[bulletPointer]._mode = mode;
	bullets[bulletPointer].setPosition(pos);
	bulletPointer++;
}


void Bullet::_Update(const float &dt)
{
	// If the bullet is off screen do nothing
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		return;
	}
	else
	{
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships)
		{
			if (!_mode && s == player)
			{
				// Player bullets do not collide with the player
				continue;
			}
			if (_mode && s != player)
			{
				// Invader bullets do not collide with other invaders
				continue;
			}
			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox))
			{
				// Explode the ship
				s->Explode();
				// Warp bullet of screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}