#include "scene_steering.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_ai_steering.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace sf;

void SteeringScene::Load()
{
	// Player
	{
		auto player = makeEntity();
		player->setPosition(Vector2f(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2));
		player->addTag("player");
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<CircleShape>(10.0f);
		s->getShape().setFillColor(Color::Red);
		s->getShape().setOrigin(Vector2f(5.0f, 5.0f));
		player->addComponent<BasicMovementComponent>();
	}

	// Setup C++ random number generation
	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0.0f, Engine::getWindowSize().x);
	uniform_real_distribution<float> y_dist(0.0f, Engine::getWindowSize().y);

	for (size_t n = 0; n < 100; ++n)
	{
		auto enemy = makeEntity();
		enemy->setPosition(Vector2f(x_dist(engine), y_dist(engine)));
		auto s = enemy->addComponent<ShapeComponent>();
		s->setShape<RectangleShape>(Vector2f(10.0f, 10.0f));
		s->getShape().setFillColor(Color::Blue);
		enemy->addComponent<SteeringComponent>(ents.find("player")[0].get());
	}
}

void SteeringScene::UnLoad() { Scene::UnLoad(); }

void SteeringScene::Update(const double& dt) { Scene::Update(dt); }

void SteeringScene::Render() { Scene::Render(); }