#include "astar.h"
#include <LevelSystem.h>
#include <array>
#include <queue>

using namespace std;
using namespace sf;

// Node in the search group
class Node
{
private:
	Vector2i _pos;
	int _level;
	int _priority;

public:
	Node() = default;
	Node(const Vector2i& pos, int level, int priority) : _pos(pos), _level(level), _priority(priority) {}

	const Vector2i& getPos() { return _pos; }

	int getLevel() { return _level; }

	int getPriority() { return _priority; }

	unsigned int estimate(const Vector2i& dest) const
	{
		Vector2i delta = dest - _pos;
		return static_cast<unsigned int>(length(delta));
	}

	void updatePriority(const Vector2i& dest)
	{
		// Heuristic is just eucledian distance
		_priority = _level + estimate(dest) * 10;
	}

	void nextLevel() { _level += 10; }

	// Used for priority ordering
	bool operator<(const Node& other) const
	{
		return _priority > other._priority;
	}
};

// Path finding A*
vector<Vector2i> pathFind(Vector2i start, Vector2i finish)
{
	static std::array<sf::Vector2i, 4> directions = { Vector2i(1, 0), Vector2i(0, 1), Vector2i(-1, 0), Vector2i(0, -1) };

	vector<vector<bool>> closed_nodes_map(ls::getWidth());
	vector<vector<int>> open_nodes_map(ls::getWidth());
	vector<vector<Vector2i>> direction_map(ls::getWidth());
	// Queue of nodes to test.  Priority ordered.
	// We need two for when we redirect and copy the path.
	priority_queue<Node> queue[2];
	// Index of current queue
	size_t queue_index = 0;

	// Initialise the lookup maps.  Initially everything looks traversable and no route has been planned.
	for (size_t y = 0; y < ls::getHeight(); ++y) 
	{
		for (size_t x = 0; x < ls::getWidth(); ++x)
		{
			closed_nodes_map[x].push_back(false);
			open_nodes_map[x].push_back(0);
			direction_map[x].emplace_back(Vector2i(0, 0));
		}
	}
}