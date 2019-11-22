// app 8nov.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

// app 8nov.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Lib.h"
#include <direct.h>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Ball.h"
#include "Wall.h"
#include <Box2D/Box2D.h>

using namespace sf;
static std::vector<Entity> CharList;
static std::vector<Ball> BallList;
static std::vector<Wall> WallList;
sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}
static Vector2f shPos(0, 0);
static int height;
static int width;
//static Vector2f ballpos(shPos);

int squareSpeed = 3;
int BallSpeed = 5;
int Left = -1;
int Right = 1;

sf::FloatRect boundingBox;
Vector2f Alpha;
sf::FloatRect otherBox;

Vector2f Beta;

void world(sf::RenderWindow &win)
{

	for (int i = 0; i < WallList.size(); i++)
	{
		if (CharList[0].tank.getGlobalBounds().intersects(WallList[i].wallet.getGlobalBounds()))
		{
			CharList[0].position.x = Beta.x;
			CharList[0].position.y = Beta.y;
			squareSpeed = 0;
		}
	}
	if (CharList[0].tank.getGlobalBounds().intersects(CharList[1].tank.getGlobalBounds()))
	{
		CharList[0].position.x = Beta.x;
		CharList[0].position.y = Beta.y;
		squareSpeed = 0;
	}
	else
	{
		Beta.x = CharList[0].position.x;
		Beta.y = CharList[0].position.y;
		squareSpeed = 3;
	}
	for (int i = 0; i < BallList.size(); i++)
	{
		if (WallList[0].wallet.getGlobalBounds().intersects(BallList[i].ball.getGlobalBounds()))
		{
			BallList[i].r = -BallList[i].r;
			int A = 0;
		}
		if (WallList[1].wallet.getGlobalBounds().intersects(BallList[i].ball.getGlobalBounds()))
		{
			BallList[i].r = -BallList[i].r;
			int A = 0;
		}
		if (WallList[2].wallet.getGlobalBounds().intersects(BallList[i].ball.getGlobalBounds()))
		{
			BallList[i].u = -BallList[i].u;
			int A = 0;
		}
		if (WallList[3].wallet.getGlobalBounds().intersects(BallList[i].ball.getGlobalBounds()))
		{
			BallList[i].u = -BallList[i].u;
			int A = 0;
		}
	}


}
void drawWallet(sf::RenderWindow &win)
{
	for (Wall &Elem : WallList)
	{
		win.draw(Elem.wallet);
		Elem.SetPosition();
	}
}
void drawTank(sf::RenderWindow &win)
{
	for (Entity &Elem : CharList)
	{
		win.draw(Elem.tank);
		Elem.SetPosition();
	}
}
void drawViseur(sf::RenderWindow &win)
{
	for (Entity &Elem : CharList)
	{
		win.draw(Elem.Viseur);
		Elem.SetPosition();
	}
}
void drawBall(sf::RenderWindow &win)
{
	for (Ball &Elem : BallList)
	{

		win.draw(Elem.ball);
		Elem.ball.move(Elem.u / 8, Elem.r / 8);

	}
}

int main()
{
	bool Shoot = false;
	Entity Player = Entity(Vector2f(500, 500), Vector2f(80, 80));
	Entity Ennemy = Entity(Vector2f(80, 80), Vector2f(30, 30));


	CharList.push_back(Player);
	CharList.push_back(Ennemy);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	static RectangleShape sh;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Default, settings);
	height = window.getSize().y;
	width = window.getSize().x;
	Wall Up = Wall(Vector2f(0, 0), Vector2f(window.getSize().x, 3));
	Wall Down = Wall(Vector2f(0, (window.getSize().y) - 3), Vector2f(window.getSize().x, 3));
	Wall Left = Wall(Vector2f(0, 0), Vector2f(3, height));
	Wall Right = Wall(Vector2f(window.getSize().x - 3, 0), Vector2f(3, height));
	WallList.push_back(Up);
	WallList.push_back(Down);
	WallList.push_back(Left);
	WallList.push_back(Right);
#pragma region MyRegion




	window.setVerticalSyncEnabled(true);

#pragma endregion
	while (window.isOpen())//on passe tout le temps DEBUT DE LA FRAME 
	{
		sf::Event event;//recup les evenement clavier/pad
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:

				break;


			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		world(window);
		sf::Vector2i globalPosition = sf::Mouse::getPosition();


		if (sf::Joystick::isConnected)
		{
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			if (x > 25)
			{
				CharList[0].position.x += squareSpeed;
			}

		}
		if (sf::Joystick::isConnected)
		{
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			if (x < -2)
			{
				CharList[0].position.x -= squareSpeed;

			}

		}
		if (sf::Joystick::isConnected)
		{
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (y > 25)
			{
				CharList[0].position.y += squareSpeed;

			}

		}
		if (sf::Joystick::isConnected)
		{
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (y < -25)
			{
				Alpha = CharList[0].position;
				CharList[0].position.y -= squareSpeed;
			}

		}
		if (sf::Joystick::isConnected)
		{

			float u = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
			float r = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
			if (u > 25 || u < -25 || r>25 || r < -25)
			{
				float angle = (atan2(u, r) * 180) / 3.141592654;
				CharList[0].Viseur.setRotation(-angle);


				if (!Shoot && sf::Joystick::isButtonPressed(0, 5))
				{
					Ball Balle = Ball(CharList[0].Viseur.getPosition(), 5);
					Balle.u = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
					Balle.r = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
					BallList.push_back(Balle);
				}
				if (sf::Joystick::isButtonPressed(0, 5))
				{
					Shoot = true;
				}
				else
				{
					Shoot = false;
				}
			}

		}


		window.clear();
		drawWallet(window);
		drawTank(window);
		drawViseur(window);
		drawBall(window);
		window.display();//ca dessine et ca attend la vsync

	}

	return 0;
}