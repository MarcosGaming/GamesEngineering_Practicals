#pragma once
#include "system_renderer.h"
#include <queue>

static std::queue<const sf::Drawable *> drawables;
static sf::RenderWindow *rw;

void Renderer::initialise(sf::RenderWindow &r) { rw = &r; }

sf::RenderWindow &Renderer::getWindow() { return *rw; }

void Renderer::shutdown()
{
	while (!drawables.empty())
	{
		drawables.pop();
	}
}

void Renderer::render()
{
	if (rw == nullptr)
	{
		throw("No render window set!");
	}
	while (!drawables.empty())
	{
		rw->draw(*drawables.front());
		drawables.pop();
	}
}

void Renderer::queue(const sf::Drawable *s) { drawables.push(s); }