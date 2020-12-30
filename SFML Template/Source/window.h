#pragma once

#include <SFML/Graphics.hpp>
#include "drop.h"

class Window
{
public:
	sf::Color color;
	unsigned int defaultYMousePos;
	float maxYSpawn = 300.0f;

	sf::RenderWindow window;
	sf::Event Event;

	

	Window();
	void ChooseDropColor();
	void Init();

	int IntInput();
};
