#pragma once

#include <SFML/Graphics.hpp>

class Mekk
{
public:
	sf::Vector2f position;
	sf::RectangleShape tank;
	sf::RectangleShape BoxCollider;
	sf::FloatRect Box;
	Mekk(sf::Vector2f pos, sf::Vector2f size)
	{
		BoxCollider.setSize(size);
		tank.setSize(size);
		position = pos;
		tank.setFillColor(sf::Color::Yellow);
		tank.setPosition(pos);

	};
	void SetPosition()
	{
		tank.setPosition(position);
	}

};


