#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

// World
b2World *world;
// 1 SFML unit = 30 physics units
const float physics_scale = 30.0f;
// Inverse of physics scale
const float physics_scale_inv = 1.0f / physics_scale;
// Number for accuracy of physics simulation
const int32 velocity_iterations = 6;
const int32 position_iterations = 2;

int gameWidth = 800;
int gameHeight = 600;
std::vector<sf::RectangleShape*> shapes;
std::vector<b2Body*> bodies;

// Convert from b2vec2 to a vector2f
inline const sf::Vector2f bv2_to_sv2(const b2Vec2& in)
{
	return sf::Vector2f(in.x * physics_scale, in.y * physics_scale);
}
// Convert from Vector2f to b2Vec2
inline const b2Vec2 sv2_to_bv2(const sf::Vector2f& in)
{
	return b2Vec2(in.x * physics_scale_inv, in.y * physics_scale_inv);
}
// Convert from Screenspace.y to physics.y
inline const sf::Vector2f invert_height(const sf::Vector2f& in)
{
	return sf::Vector2f(in.x, gameHeight - in.y);
}

// Create a Box2d body with a box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const sf::Vector2f& position, const sf::Vector2f& size)
{
	b2BodyDef body_def;
	// Dymanic or static
	body_def.type = dynamic ? b2_dynamicBody : b2_staticBody;
	body_def.position = sv2_to_bv2(position);
	// Create the body
	b2Body *body = World.CreateBody(&body_def);

	// Create the fixture shape
	b2PolygonShape shape;
	shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	b2FixtureDef fixture_def;
	// Fixture properties
	fixture_def.density = dynamic ? 10.0f : 0.0f;
	fixture_def.friction = dynamic ? 0.8f : 1.0f;
	fixture_def.restitution = 1.0f;
	fixture_def.shape = &shape;
	// Add to body
	body->CreateFixture(&fixture_def);
	return body;
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const sf::RectangleShape& rs)
{
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void init()
{
	const b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world which holds and simulates the physics bodies
	world = new b2World(gravity);

	// Wall dimensions
	sf::Vector2f walls[] =
	{
		// Top
		sf::Vector2f(gameWidth * .5f, 5.f), sf::Vector2f(gameWidth, 10.f),
		// Bottom
		sf::Vector2f(gameWidth * .5f, gameHeight - 5.f), sf::Vector2f(gameWidth, 10.f),
		// left
		sf::Vector2f(5.f, gameHeight * .5f), sf::Vector2f(10.f, gameHeight),
		// right
		sf::Vector2f(gameWidth - 5.f, gameHeight * .5f), sf::Vector2f(10.f, gameHeight)
	};
	//Build walls
	for (int i = 0; i < 7; i += 2)
	{
		// Create SFML shapes for each wall
		auto s = new sf::RectangleShape();
		s->setPosition(walls[i]);
		s->setSize(walls[i+1]);
		s->setOrigin(walls[i + 1]/2.0f);
		s->setFillColor(sf::Color::White);
		shapes.push_back(s);

		// Create a dynamic physics body for the wall
		auto b = CreatePhysicsBox(*world, false, *s);
		bodies.push_back(b);
	}

	// Create boxes
	for (int i = 1; i < 11; ++i)
	{
		// Create SFML shapes for each box
		auto s = new sf::RectangleShape();
		s->setPosition(sf::Vector2f(i*(gameWidth / 12.0f), gameHeight * 0.7f));
		s->setSize(sf::Vector2f(50.0f, 50.0f));
		s->setOrigin(sf::Vector2f(25.0f, 25.0f));
		s->setFillColor(sf::Color::White);
		shapes.push_back(s);
		
		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		// Give the box a spin
		b->ApplyAngularImpulse(5.0f, true);
		bodies.push_back(b);
	}
}

void Update(sf::RenderWindow &window)
{
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
	}
	// Quit Via ESC Key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	// Step physics world by dt
	world->Step(dt, velocity_iterations, position_iterations);

	for (int i = 0; i < bodies.size(); ++i)
	{
		// Sync shapes to physics positions
		shapes[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
		// Sync shapes to physics rotations
		shapes[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
	}
}

void Render(sf::RenderWindow &window)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		window.draw(*shapes[i]);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "PHYSICS");
	init();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}