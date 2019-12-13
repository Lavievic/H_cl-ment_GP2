#pragma once
#include <SFML/Graphics.hpp>
class Wall
{
public:
	sf::Vector2f position;
	sf::RectangleShape wallet;
	sf::Texture *Brick;
	Wall(sf::Vector2f pos, sf::Vector2f size, sf::Texture *tex)
	{
		Brick = tex;
		wallet.setSize(size);
		position = pos;
		//wallet.setFillColor(sf::Color::Red);
		wallet.setPosition(pos);
		if (Brick)
		{
			wallet.setTexture(Brick);
		}
	};
	void SetPosition()
	{
		wallet.setPosition(position);
	}
};
