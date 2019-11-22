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
#include <Box2D/Box2D.h>

using namespace sf;
/*Vector2i Point1(100, 100);
Vector2i Point2(200, 200);
Vector2i Point3(300, 300);
Vector2i Point4(400, 400);
Vector2i Point5(500, 500);
Vector2i Point6(600, 600);
Vector2i Point7(700, 700);*/
static std::vector<Entity> CharList;
static std::vector<Ball> BallList;
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
//static Vector2f ballpos(shPos);

int squareSpeed = 3;
int BallSpeed = 5;
int Left = -1;
int Right = 1;

sf::FloatRect boundingBox;
Vector2f Alpha;
sf::FloatRect otherBox;

bool collision = false;
bool collisionR = false;
bool collisionL = false;
bool collisionU = false;
bool collisionD = false;
Vector2f Beta;

void world(sf::RenderWindow &win)
{
	if (CharList[0].tank.getGlobalBounds().intersects(CharList[1].tank.getGlobalBounds()))
	{
		CharList[0].position.x = Beta.x;
		CharList[0].position.y = Beta.y;
		squareSpeed = 0;
		/*if (collision==false)
		{
			Alpha = CharList[0].position;
			printf("collision",collision);
			collision = true;
		}
		if (collision == true)
		{
			CharList[0].position = Alpha;
		}
		boundingBox = CharList[0].tank.getGlobalBounds();
		//boundingBox.left
		squareSpeed = 3;*/
	}
	else
	{
		/*if (collision == true)
		{
			collisionD = false;
			collisionR= false;
			collisionL= false;
			collisionU = false;
			collision = false;
		}*/
		Beta.x = CharList[0].position.x;
		Beta.y = CharList[0].position.y;
		squareSpeed = 3;
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
		Elem.SetPosition();
	}
}

int main()
{

	Entity Player = Entity(Vector2f(30, 30), Vector2f(80, 80));
	Entity Ennemy = Entity(Vector2f(80, 80), Vector2f(30, 30));

	Ball Balle = Ball(Vector2f(400, 300), 20);

	CharList.push_back(Player);
	CharList.push_back(Ennemy);

	BallList.push_back(Balle);


	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	static RectangleShape sh;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
#pragma region MyRegion




	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	sf::Time appStart = clock.getElapsedTime();
	sf::Time frameStart = clock.getElapsedTime();
	sf::Time prevFrameStart = clock.getElapsedTime();

	float fps[4] = { 0.f,0.f,0.f,0.f };
	int step = 0;
	sf::Font * font = new sf::Font();

	if (font->loadFromFile("Fonts/DejaVuSans.ttf") == false) {
		printf("no such font\n");
	}

	sf::Text myFpsCounter;
	int every = 0;
#pragma endregion
	while (window.isOpen())//on passe tout le temps DEBUT DE LA FRAME 
	{
		sf::Event event;//recup les evenement clavier/pad
		frameStart = clock.getElapsedTime();
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyReleased:

				if (event.key.code == sf::Keyboard::I)
					printf("instant fps %f\n", fps[(step - 1) % 4]);

				if (event.key.code == sf::Keyboard::F)
					printf("fps %f\n", 0.25f*(fps[0] + fps[1] + fps[2] + fps[3]));

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
			}


		}
		myFpsCounter.setPosition(8, 8);
		myFpsCounter.setFillColor(sf::Color::Red);
		myFpsCounter.setFont(*font);

		if (every == 0) {
			myFpsCounter.setString(std::string("FPS:") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}
		every--;

		window.clear();

		drawTank(window);
		drawViseur(window);
		drawBall(window);
		window.draw(myFpsCounter);
		window.display();//ca dessine et ca attend la vsync


		fps[step % 4] = 1.0f / (frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;

		step++;
	}

	return 0;
}
