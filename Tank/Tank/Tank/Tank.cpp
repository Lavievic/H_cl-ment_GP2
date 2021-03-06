#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "stdafx.h"
#include "Lib.h"
#include <direct.h>
#include <SFML/Graphics.hpp>
#include "Mekk.h"
//#include "Ball.h"

static std::vector<Mekk> CharList;

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

int squareSpeed = 3;
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





class Bullet
{
public :
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;


	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

void world(sf::RenderWindow &win)
{
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

	if (Left == -1)
	{
		

	}

	

}

void drawTank(sf::RenderWindow &win)
{
	for (Mekk &Elem : CharList)
	{
		win.draw(Elem.tank);
		Elem.SetPosition();
	}
}

using namespace sf;

int main()
{

	Mekk Player = Mekk(Vector2f(20, 200), Vector2f(15, 80));
	Mekk Ennemy = Mekk(Vector2f(80, 80), Vector2f(30, 30));


	// Bullet
	Bullet ball;
	std::vector<Bullet>bullets;
	bullets.push_back(Bullet(ball));
	

	CharList.push_back(Player);
	CharList.push_back(Ennemy);

	


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

	/*if (!font->loadFromFile("arial.ttf")) {
		printf("no such font\n");
	}*/

	sf::Text myFpsCounter;
	int every = 0;
#pragma endregion
	while (window.isOpen())
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
			if (x > 25 )
			{
				
				CharList[0].position.x += squareSpeed;
			
			}

		}
		if (sf::Joystick::isConnected)
		{
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			if (x < -25 )
			{
			
				CharList[0].position.x -= squareSpeed;
			

			}

		}
		if (sf::Joystick::isConnected)
		{
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (y > 25 )
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

		//Shooting

		if (sf::Joystick::isButtonPressed(0, 1))
		{
			ball.shape.setPosition(CharList);
			bullets.push_back(Bullet(ball));
		}
		

		myFpsCounter.setPosition(8, 8);
		myFpsCounter.setFillColor(sf::Color::Red);
		myFpsCounter.setFont(*font);

		if (every == 0) {
		//	myFpsCounter.setString(std::string("FPS:") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}
		every--;

		window.clear();//nettoie la frame
					   //window.draw(shape);//on demande le dessin d' une forme
					   //drawCurve(window,clock.getElapsedTime().asSeconds());
					   //drawCatmull(window,clock.getElapsedTime().asSeconds());
		drawTank(window);

		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i].shape);
		}
		
		window.draw(myFpsCounter);


		
		window.display();


		fps[step % 4] = 1.0f / (frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;

		step++;
	}

	return 0;
};


