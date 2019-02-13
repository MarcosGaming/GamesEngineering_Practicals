#include "cmp_enemy_AI.h"
#include "LevelSystem.h"

// Constructor
EnemyAIComponent::EnemyAIComponent(Entity *p) : ActorMovementComponent(p) {}

// Update
static const sf::Vector2i directions[] = { {1, 0},{ 0, 1 },{ 0, -1 },{ -1, 0 } };
void EnemyAIComponent::update(double dt)
{
	// Amount to move
	const auto mva = (float)(dt * _speed);
	// Current position
	const sf::Vector2f current_pos = _parent->getPosition();
	// Next position
	const sf::Vector2f next_pos = current_pos + _direction * mva;
	// Inverse of our current position
	const sf::Vector2i bad_direction = -1 * sf::Vector2i(_direction);
	// Random new direction
	sf::Vector2i new_direction = directions[(rand() % 4)];

	switch (_state)
	{
	case ROAMING:
		// Wall in front or waypoint
		if (ls::getTileAt(next_pos) == ls::WALL || ls::getTileAt(next_pos) == ls::WAYPOINT)
		{
			// Start rotate
			_state = ROTATING;
		}
		else
		{
			//std::cout << "here 1";
			// Keep moving
			move(_direction * mva);
		}
		break;

	case ROTATING:
		// New direction needs to be different from bad direction and can't lead to a wall
		while (new_direction == bad_direction || ls::getTileAt(current_pos + sf::Vector2f(new_direction) * mva) == ls::WALL)
		{
			// Set new direction
			new_direction = directions[(rand() % 4)];
		}
		_direction = sf::Vector2f(new_direction);
		_state = ROTATED;
		break;

	case ROTATED:
		// Check if the AI has left the way point
		if (ls::getTileAt(current_pos) != ls::WAYPOINT)
		{
			_state = ROAMING;
		}
		move(_direction * mva);
		break;
	}
}