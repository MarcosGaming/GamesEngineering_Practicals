#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

// SHIP
Ship::Ship() {}

Ship::Ship(IntRect ir) : Sprite()
{
	_exploded = false;
	_bottom = false;
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float &dt) {}

void Ship::Explode()
{
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

bool Ship::is_exploded() const
{
	return _exploded;
}

// Define ship deconstructor, even if its pure virtual we need to define it
Ship::~Ship() = default;

// INVADER
bool Invader::direction;
float Invader::speed = 60;

Invader::Invader() : Ship() {};
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	explosiontime = 0.3f;
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt)
{
	Ship::Update(dt);
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16))
	{
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; i++)
		{
			ships[i]->move(0, 10);
		}
	}
	// Invader shoots at random
	static float firetime = 0.0f;
	firetime -= dt;
	if (_bottom && firetime <= 0 && rand() % 100 == 0)
	{
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60) + invaders_left * 0.1;
	}
	if (_exploded)
	{
		explosiontime -= dt;
		if (explosiontime <= 0)
		{
			speed += 5;
			setTextureRect(IntRect(0, 0, 0, 0));
			// Remove the invader
			ptrdiff_t pos = distance(ships.begin(), find(ships.begin(), ships.end(), this));
			ships.erase(ships.begin() + pos);
		}
	}
}

void Invader::Explode()
{
	Ship::Explode();
	invaders_left -= 1;
	_bottom = false;
	// Set the invader in the upper row as the bottom
	ptrdiff_t pos = distance(ships.begin(), find(ships.begin(), ships.end(), this));
	if (pos - invaders_columns >= 0 && !ships.at(pos - invaders_columns)->is_exploded())
	{
		ships.at(pos - invaders_columns)->_bottom = true;
	}
}

// PLAYER
float Player::speed = 150;

Player::Player() : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameWidth * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt)
{
	Ship::Update(dt);
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction++;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction--;
	}
	// Do not allow the player to move beyond the screen
	if (getPosition().x < 0)
	{
		setPosition(0, getPosition().y);
	}
	else if (getPosition().x > gameWidth - 32)
	{
		setPosition(gameWidth - 32, getPosition().y);
	}
	move(dt * direction * speed, 0);
	// Player shoots
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::W))
	{
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}

void Player::Explode()
{
	Ship::Explode();
	gameOver = true;
}