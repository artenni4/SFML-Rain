#pragma once

#include <SFML/Graphics.hpp>

class Drop
{
public:
	float x, y, height, width;
	float fallingSpeed = 3.0f;
	

	sf::RectangleShape rect;

	void SetSettings();
	void SetNewPosition();
};
