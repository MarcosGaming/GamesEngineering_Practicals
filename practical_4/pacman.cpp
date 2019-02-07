#include "pacman.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"
#include "cmp_sprite.h"

#define GHOST_COUNT 4

// Scene base class
void Scene::render() { _ents.render(Renderer::getWindow()); }
void Scene::update(double dt) { _ents.update(dt); }
std::vector<std::shared_ptr<Entity>> &Scene::getEnts() { return _ents.list; }

// Menu scene class
void MenuScene::load()
{
	// Load font
	font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(20);
	// Set text position
	text.setPosition((gameWidth * .5f) - 55.0f, gameHeight * 0.5f);
}
void MenuScene::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}
void MenuScene::render()
{
	Renderer::queue(&text);
	Scene::render();
}

// Game scene
void GameScene::load()
{
	// Player
	auto player = std::make_shared<Entity>();
	auto p = player->addComponent<ShapeComponent>();
	p->setShape<sf::CircleShape>(12.0f);
	p->getShape().setFillColor(sf::Color::Yellow);
	p->getShape().setOrigin(sf::Vector2f(12.0f, 12.0f));
	_ents.list.push_back(player);

	// Ghosts
	const sf::Color ghost_cols[]{ { 208, 62,25 }, { 219, 133, 28 }, { 70, 191, 238 }, { 234, 130, 229 } };
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		auto ghost = std::make_shared<Entity>();
		auto g = ghost->addComponent<ShapeComponent>();
		g->setShape<sf::CircleShape>(12.0f);
		g->getShape().setFillColor(ghost_cols[i % 4]);
		g->getShape().setOrigin(sf::Vector2f(12.0f, 12.0f));
		_ents.list.push_back(ghost);
	}
}

void GameScene::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	Scene::update(dt); 
}

void GameScene::render() { Scene::render(); }

void GameScene::respawn()
{

}