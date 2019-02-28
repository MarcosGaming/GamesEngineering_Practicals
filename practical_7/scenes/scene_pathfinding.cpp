#include "scene_pathfinding.h"
#include <LevelSystem.h>
#include "../components/cmp_sprite.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> character;

void PathfindingScene::Load()
{
	ls::loadLevelFile("res/pacman.txt", 20.0f);

	character = makeEntity();
	Vector2f startPos(ls::getOffset().x + 1 * ls::getTileSize(), ls::getOffset().y + 1 * ls::getTileSize());
	character->setPosition(startPos);
	auto s = character->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Red);
}

void PathfindingScene::UnLoad() { Scene::UnLoad(); }

void PathfindingScene::Update(const double& dt) { Scene::Update(dt); }

void PathfindingScene::Render()
{
	ls::render(Engine::GetWindow());
	Scene::Render();
}
