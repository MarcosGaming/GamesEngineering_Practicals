#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "maths.h"

#define ls LevelSystem

class LevelSystem
{
public:
	enum TILE {EMPTY, START, END, WALL, ENEMY, WAYPOINT};

	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	// Return height
	static size_t getHeight();
	// Return width
	static size_t getWidth();
	// Get tile at grid coordinate
	static TILE getTile(sf::Vector2ul);
	// Get Screenspce coordinate of tike
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	// Get the tile at screenspace pos
	static TILE getTileAt(sf::Vector2f);
	// Return start tile position
	static sf::Vector2f getStartTilePos();
	// Return end tile position
	static sf::Vector2f getEndTilePos();
	// Return any tile position
	static std::vector<sf::Vector2f> findTilesPosition(TILE t);
	// Find tiles
	static std::vector<sf::Vector2ul> findTiles(TILE t);

protected:
	static std::unique_ptr<TILE[]> _tiles;		// Internal array of tiles
	static size_t _width;						// How many tiles wide the level is
	static size_t _height;						// How many tiles high the level is
	static sf::Vector2f _offset;				// Screenspace offset of level, when rendered
	static float _tileSize;						// Screenspace size of each tile, when rendered
	static std::map<TILE, sf::Color> _colours;	// Color to render each tile type

	// Array of sfml sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	// Generate the sprites array
	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};