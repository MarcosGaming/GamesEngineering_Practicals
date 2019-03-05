#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() 
{
	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("Decision Demos\nPress 1 for States Machines\nPress 2 for Decision Trees");
	setLoaded(true);
}

void MenuScene::Update(const double& dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		Engine::ChangeScene(&stateScene);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		Engine::ChangeScene(&decisionScene);
	}
	Scene::Update(dt);
}
