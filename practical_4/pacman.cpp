#include "pacman.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"

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
	std::shared_ptr<Entity> player = std::make_shared<Player>();
	_ents.list.push_back(std::move(player));
	// Ghosts
	std::shared_ptr<Entity> ghost1 = std::make_shared<Ghost>(sf::Color::Red);
	_ents.list.push_back(std::move(ghost1));
	std::shared_ptr<Entity> ghost2 = std::make_shared<Ghost>(sf::Color::Green);
	_ents.list.push_back(std::move(ghost2));
	std::shared_ptr<Entity> ghost3 = std::make_shared<Ghost>(sf::Color::Magenta);
	_ents.list.push_back(std::move(ghost3));
	std::shared_ptr<Entity> ghost4 = std::make_shared<Ghost>(sf::Color::Blue);
	_ents.list.push_back(std::move(ghost4));
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