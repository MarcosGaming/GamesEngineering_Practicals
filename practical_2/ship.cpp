#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

// SHIP
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite()
{
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {};

// Define ship deconstructor, even if its pure virtual we need to define it
Ship::~Ship() = default;

// INVADER
bool Invader::direction;
float Invader::speed;

Invader::Invader() : Ship() {};
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	setOrigin(16, 16);
	setPosition(pos);
};

void Invader::Update(const float &dt)
{
	Ship::Update(dt);
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16))
	{
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; i++)
		{
			ships[i]->move(0, 24);
		}
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
}