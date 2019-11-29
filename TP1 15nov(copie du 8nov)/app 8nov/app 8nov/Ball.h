#pragma once
#include <SFML/Graphics.hpp>
class Ball
{


public:
	sf::Vector2f position;
	sf::CircleShape ball;
	sf::CircleShape BallCollider;
	float u, r;
	Ball(sf::Vector2f pos, float size)
	{
		ball.setRadius(size);
		position = pos;
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(pos);


	}
	void SetPosition()
	{
		ball.setPosition(position);
	}
};