#include "drop.h"

void Drop::SetSettings()
{
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(x, y));
}

void Drop::SetNewPosition()
{
	rect.setPosition(sf::Vector2f(x, y));
}
