
#pragma once
#include <SFML/Graphics.hpp>
class Ball
{


public:
	sf::Vector2f position;
	sf::Vector2f Prepos;
	sf::CircleShape ball;
	sf::CircleShape BallCollider;
	int BallLife;
	bool spawned = true;
	float u, r;
	Ball(sf::Vector2f pos, float size)
	{

		ball.setRadius(size);
		ball.setOrigin(sf::Vector2f(size / 2, size / 2));
		position = pos;
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(pos);
	}
	void SetPosition()
	{
		ball.setPosition(position);
	}
};