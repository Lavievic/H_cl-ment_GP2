#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Entity
{

public:
	sf::Vector2f position;
	sf::RectangleShape tank;
	sf::RectangleShape Viseur;
	sf::RectangleShape BoxCollider;
	sf::FloatRect Box;
	Entity(sf::Vector2f pos, sf::Vector2f size)
	{
		Viseur.setSize(Vector2f((size.x / 5), (size.y / 1.5f)));
		Viseur.setOrigin(Vector2f((Viseur.getSize().x) / 2, 0));
		Viseur.setFillColor(sf::Color::Red);
		BoxCollider.setSize(size);
		tank.setSize(size);
		tank.setOrigin(Vector2f((size.x / 2), (size.y / 2)));
		position = pos;
		tank.setFillColor(sf::Color::Yellow);
		tank.setPosition(pos);

	};
	void SetPosition()
	{
		Viseur.setPosition(position);
		tank.setPosition(position);
	}
};



