#include "pacman.h"
#include "system_renderer.h"
#include "cmp_shape.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_AI.h"
#include "LevelSystem.h"
#include "cmp_pickup.h"

#define GHOST_COUNT 4

// Scene base class
void Scene::render() { _ents.render(); }
void Scene::update(double dt) { _ents.update(dt); }
std::vector<std::shared_ptr<Entity>> &Scene::getEnts() { return _ents.list; }

// Make cherry method
std::shared_ptr<Entity> makeCherry(const sf::Vector2ul& cl, float multiplier, Scene &scene)
{
	std::shared_ptr<Entity> cherry = std::make_shared<Entity>();
	cherry->setPosition(ls::getTilePosition(cl));
	std::shared_ptr<ShapeComponent> c = cherry->addComponent<ShapeComponent>();
	c->setShape<sf::CircleShape>(5.0f);
	c->getShape().setFillColor(sf::Color::Red);
	c->getShape().setOrigin(sf::Vector2f(5.0f, 5.0f));
	std::shared_ptr<PickUpComponent> pick = cherry->addComponent<PickUpComponent>();
	pick->_multiplier = multiplier;
	pick->_ents = scene.getEnts();
	return cherry;
}

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
std::shared_ptr<Entity> player;
std::vector<std::shared_ptr<Entity>> ghosts;
std::vector<std::shared_ptr<Entity>> cherries;
void GameScene::load()
{
	// Level
	ls::loadLevelFile("res/pacman.txt", 25.0f);

	// Player
	player = std::make_shared<Entity>();
	player->addComponent<PlayerMovementComponent>();
	std::shared_ptr<ShapeComponent> p = player->addComponent<ShapeComponent>();
	p->setShape<sf::CircleShape>(12.0f);
	p->getShape().setFillColor(sf::Color::Yellow);
	p->getShape().setOrigin(sf::Vector2f(12.0f, 12.0f));
	player->setPosition((ls::getTilePosition(ls::findTiles(ls::START)[0])));
	player->getCompatibleComponents<ActorMovementComponent>()[0]->setSpeed(150.0f);
	_ents.list.push_back(player);


	// Ghosts
	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	const sf::Color ghost_cols[]{ { 208, 62,25 }, { 219, 133, 28 }, { 70, 191, 238 }, { 234, 130, 229 } };
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		std::shared_ptr<Entity> ghost = std::make_shared<Entity>();
		ghost->addComponent<EnemyAIComponent>();
		ghost->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		std::shared_ptr<ShapeComponent> g = ghost->addComponent<ShapeComponent>();
		g->setShape<sf::CircleShape>(12.0f);
		g->getShape().setFillColor(ghost_cols[i % 4]);
		g->getShape().setOrigin(sf::Vector2f(12.0f, 12.0f));
		ghost->getCompatibleComponents<ActorMovementComponent>()[0]->setSpeed(100.0f);
		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
	}

	respawn();
}

void GameScene::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	for (auto &g : ghosts)
	{
		if (sf::length(g->getPosition() - player->getPosition()) < 20.0f)
		{
			respawn();
		}
	}
	Scene::update(dt); 
}

void GameScene::render() 
{ 
	ls::render(Renderer::getWindow());
	Scene::render(); 
}

void GameScene::respawn()
{
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->getCompatibleComponents<ActorMovementComponent>()[0]->setSpeed(150.0f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& ghost : ghosts)
	{
		ghost->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		ghost->getCompatibleComponents<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}

	for (auto n : cherries)
	{
		n->setForDelete();
		n.reset();
	}
	cherries.clear();

	auto cherriesLoc = ls::findTiles(ls::EMPTY);
	for (const auto &cl : cherriesLoc)
	{
		auto cherry = makeCherry(cl, 1, *gameScene);
		_ents.list.push_back(cherry);
		cherries.push_back(cherry);
	}
	cherriesLoc = ls::findTiles(ls::WAYPOINT);
	for (const auto& cl : cherriesLoc)
	{
		auto cherry = makeCherry(cl, 2, *gameScene);
		_ents.list.push_back(cherry);
		cherries.push_back(cherry);
	}
}