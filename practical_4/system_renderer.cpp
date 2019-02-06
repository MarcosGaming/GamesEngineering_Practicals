#pragma once
#include "system_renderer.h"
#include <queue>

static std::queue<const sf::Drawable *> sprites;
static sf::RenderWindow *rw;

void Renderer::initialise(sf::RenderWindow &r) { rw = &r; }

sf::RenderWindow &Renderer::getWindow() { return *rw; }

void Renderer::shutdown()
{
	while (!sprites.empty())
	{
		sprites.pop();
	}
}

void Renderer::update(const double &){}

void Renderer::render()
{
	if (rw == nullptr)
	{
		throw("No render window set!");
	}
	while (!sprites.empty())
	{
		rw->draw(*sprites.front());
		sprites.pop();
	}
}

void Renderer::queue(const sf::Drawable *s) { sprites.push(s); }