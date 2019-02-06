#pragma once
#include "scene.h"

// Game scenes
extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;
// Game width and height
extern int gameWidth;
extern int gameHeight;

// Menu scene
class MenuScene : public Scene
{
private:
	sf::Text text;
	sf::Font font;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

// Game scene
class GameScene : public Scene
{
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();
public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};