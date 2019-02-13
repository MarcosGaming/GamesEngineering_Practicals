#pragma once

#include "LevelSystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 30.0f);
float LevelSystem::_tileSize(100.0f);
std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {START, Color::Blue},{ WALL, Color::White },{ END, Color::Red } };

vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;


size_t LevelSystem::getHeight()
{
	return _height;
}

size_t LevelSystem::getWidth()
{
	return _width;
}

sf::Color LevelSystem::getColor(LevelSystem::TILE t)
{
	auto it = _colours.find(t);
	if (it == _colours.end())
	{
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c)
{
	LevelSystem::_colours.insert(std::pair<LevelSystem::TILE, sf::Color>(t, c));
}


void LevelSystem::loadLevelFile(const std::string& path, float tileSize)
{
	LevelSystem::_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	if (f.good())
	{
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else
	{
		throw string("Couldnt open level file: ") + path;
	}

	std::vector<TILE> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i)
	{
		const char c = buffer[i];
		switch (c)
		{
		case 'w':
			temp_tiles.push_back(WALL);
			break;
		case 's':
			temp_tiles.push_back(START);
			break;
		case 'e':
			temp_tiles.push_back(END);
			break;
		case ' ':
			temp_tiles.push_back(EMPTY);
			break;
		case '+':
			temp_tiles.push_back(WAYPOINT);
			break;
		case 'n':
			temp_tiles.push_back(ENEMY);
			break;
			// end of line
		case '\n':
			// If width has not been written yet
			if (w == 0)
			{
				// Set width
				w = i;
			}
			// Increment height
			h++;
			break;
		default:
			// Do not know what this tile type is
			std::cout << c << endl;
		}
	}
	if (temp_tiles.size() != (w * h))
	{
		throw string("Can't parse level file") + path;
	}
	_tiles = std::make_unique<TILE[]>(w * h);
	_width = w;
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	std::cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
	buildSprites();
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p)
{
	return (Vector2f(p.x, p.y) * _tileSize);
}

void LevelSystem::buildSprites()
{
	_sprites.clear();
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y)
	{
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x)
		{
			auto s = make_unique<sf::RectangleShape>();
			s->setPosition(getTilePosition({ x, y }));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({ x, y })));
			_sprites.push_back(move(s));
		}
	}
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul p)
{
	if (p.x > _width || p.y > _height)
	{
		throw string("Tile out opf range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

LevelSystem::TILE LevelSystem::getTileAt(Vector2f v)
{
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0)
	{
		throw string("Tile out of range");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

void LevelSystem::render(RenderWindow &window)
{
	for (size_t i = 0; i < _width * _height; i++)
	{
		window.draw(*_sprites[i]);
	}
}

sf::Vector2f LevelSystem::getStartTilePos()
{
	for (size_t y = 0; y < LevelSystem::_height; ++y)
	{
		for (size_t x = 0; x < LevelSystem::_width; ++x)
		{
			if (getTile({x , y}) == START)
			{
				return getTilePosition({ x, y });
			}
		}
	}
}

sf::Vector2f LevelSystem::getEndTilePos()
{
	for (size_t y = 0; y < LevelSystem::_height; ++y)
	{
		for (size_t x = 0; x < LevelSystem::_width; ++x)
		{
			if (getTile({ x , y }) == END)
			{
				return getTilePosition({ x, y });
			}
		}
	}
}


std::vector<sf::Vector2f> LevelSystem::findTilesPosition(TILE t)
{
	std::vector<sf::Vector2f> ret;
	for (size_t y = 0; y < LevelSystem::_height; ++y)
	{
		for (size_t x = 0; x < LevelSystem::_width; ++x)
		{
			if (getTile({ x , y }) == t)
			{
				ret.push_back(getTilePosition({ x, y }));
			}
		}
	}
	return ret;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(TILE t)
{
	std::vector<sf::Vector2ul> ret;
	for (size_t y = 0; y < LevelSystem::_height; ++y)
	{
		for (size_t x = 0; x < LevelSystem::_width; ++x)
		{
			if (getTile({ x , y }) == t)
			{
				ret.push_back(sf::Vector2ul{ x, y });
			}
		}
	}
	return ret;
}