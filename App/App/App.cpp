#include "pch.h"
#include "Lib.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>
#include <functional>
#include <cmath>

using namespace sf;




static Vector2f mousePos[4] = {
	Vector2f(0,0),
	Vector2f(100,100),
	Vector2f(200,200),
	Vector2f(300,800)
};

float lerp(float a, float b, float r) {
	return a + (b - a) * r;
}

float rd() {
	return 1.0 * rand() / RAND_MAX;
}

//// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f 
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

void drawCurve(sf::RenderWindow &win, float now) {
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Yellow;
	int nb = 320;
	float stride = 1280.0 / nb;

	int ofsX = 0;
	if (fmodf(now, 2.0) <= 1) {
		red.a = 0;
	}

	for (int i = 0; i < nb + 1; ++i) {
		double ratio = 1.0 * i / nb;
		double x = ofsX + stride * i;
		double y = 400;

		//y += (ratio*ratio*1.33)* sin( ratio * now * 8.0) * 256 + rd() * 8;

		//x = 500 + cos(ratio * 2 * 3.141569) * (now * 20);
		//y = 500 + sin(ratio * 2 * 3.141569) * ( now * 20);

		//x = 500 + cos(ratio * 2 * 3.141569) * ( now * now * 20 * (0.5 + rd() * 0.5));
		//y = 500 + sin(ratio * 2 * 3.141569) * (now * now * 20 * (0.5 + rd() * 0.5));

		//y += sin(now) * 200;
		//y += ratio * ratio * sin(ratio * 8.0 + now) * 256;

		y += sin(ratio * 8.0 + now * 1.5) * 120;

		//y += sin(ratio * 8.0 + now) * (128 * 1.0 + cos(now*16) * 4);

		/*
		int radius = 160;
		x = 500 + radius * cos( ratio * 2 * 3.141569) + sin(now*10 * cos(ratio)) * 8 * (1.0 + rd() * 100);
		y = 500 + radius * sin( ratio * 2 * 3.141569) + cos(now * 10 * sin(ratio)) * 10 * (1.0 + rd() * 100);
		*/
		/*
	sf::Color c = sf::Color(
		lerp(blue.r, red.r,ratio),
		lerp(blue.g, red.g, ratio),
		lerp(blue.b, red.b, ratio)
	);
	*/
	//sf::Color c = i % 2 ? red : blue;

		sf::Color c = hsv(ratio * 360, 0.8, 0.8);

		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);
	}
	win.draw(va);
}


static RectangleShape	* sh = nullptr;
static Vector2f			shPos;
static Vector2f			shDir;

static RectangleShape	* shTarget = nullptr;




static int shSize = 48;
static void initMovingSquare() {
	sh = new RectangleShape(Vector2f(shSize, shSize));
	sh->setPosition(shPos.x = 400, shPos.y = 400);
	sh->setOrigin(shSize >> 1, shSize >> 1);
	sh->setFillColor(Color(0x7034AD1));
	sh->setOutlineColor(Color(0x7034AD));

	shTarget = new RectangleShape(Vector2f(shSize *1.5, 4));
	shTarget->setOrigin(0, 2);
	shTarget->setFillColor(Color(0xFFFF99));

}

/*sf::CircleShape shape(100.f, (int)(2 * 3.141569 * 100));
shape.setPosition(30, 30);
shape.setFillColor(sf::Color(0xF9FA7C));
shape.setOutlineThickness(4);
shape.setOutlineColor(sf::Color(0xF9FA7C));*/




static void drawMovingSquare(sf::RenderWindow& win) {
	win.draw(*sh);

	Vector2i mpos = sf::Mouse::getPosition(win);
	shTarget->setPosition(sh->getPosition());
	float angle = atan2f(mpos.y - sh->getPosition().y, mpos.x - sh->getPosition().x) / (2 * 3.141569) * 360;
	shTarget->setRotation(angle);

	shDir.x = mpos.x - sh->getPosition().x;
	shDir.y = mpos.y - sh->getPosition().y;

	win.draw(*shTarget);
}




class Particle {
public:

	sf::Shape * spr;
	Vector2f dir;

	int life = 100;
	bool killed = false;

	std::function<void(Particle*)> bhv;

	Particle(sf::Shape * spr) {
		this->spr = spr;
		dir.y = 1;
	}

	~Particle() {
		delete(spr);
		spr = nullptr;
	}

	void update() {
		if (bhv) {
			bhv(this);
		}
		life--;
		if (life == 0) killed = true;
	}

	void draw(RenderWindow & win) {
		win.draw(*spr);
	}
};


/*class Bullet {
public :
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Magenta);
	}
};*/

int main()
{
	std::cout << "Hello World!\n";

	sf::Texture texture;

	if (!texture.loadFromFile("res/Block.png"))
	{

	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::Sprite sprite2;
	sprite2.setTexture(texture);
	sprite2.setPosition(sf::Vector2f(300, 400));
	sprite.setScale(sf::Vector2f(0.3f, 0.5f)); // facteurs d'échelle absolus
	sprite.scale(sf::Vector2f(0.5f, 0.3f)); // facters d'échelle relatifs à l'échelle actuelle
	sprite2.setScale(sf::Vector2f(0.3f, 0.5f)); // facteurs d'échelle absolus
	sprite2.scale(sf::Vector2f(0.5f, 0.3f)); // facters d'échelle relatifs à l'échelle actuelle


	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;


	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);


	sf::CircleShape shape(100.f, (int)(2 * 3.141569 * 100));
	shape.setPosition(30, 30);
	shape.setFillColor(sf::Color(0xF9FA7C));
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color(0xF9FA7C));

	sf::Clock clock;

	sf::Time appStart = clock.getElapsedTime();
	sf::Time frameStart = clock.getElapsedTime();
	sf::Time prevFrameStart = clock.getElapsedTime();

	float fps[4] = { 0.f,0.f,0.f,0.f };
	int step = 0;
	sf::Font * font = new sf::Font();
	if (font->loadFromFile("res/arial.ttf") == false) {
		printf("no such font\n");
	}

	std::vector< Particle * > vec;

	initMovingSquare();



	/*if ((std::abs((shape.getPosition().x + 24) - (sprite2.getPosition().x + 24)) < sprite2.scale) &&
		(std::abs((shape.getPosition().y + 24) - (sprite2.getPosition().y + 24)) < sprite2.scale))
	{
		std::cout << "Collision !" << std::endl;
	}*/

	sf::Text myFpsCounter;
	int every = 0;
	while (window.isOpen())//on passe tout le temps DEBUT DE LA FRAME 
	{
		sf::Event event;//recup les evenement clavier/pad
		frameStart = clock.getElapsedTime();
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::I)
					printf("instant fps %f\n", fps[(step - 1) % 4]);
				if (event.key.code == sf::Keyboard::F)
					printf("fps %f\n", 0.25f*(fps[0] + fps[1] + fps[2] + fps[3]));
				break;

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::F1) mousePos[0] = sf::Vector2f(sf::Mouse::getPosition(window));
				if (event.key.code == sf::Keyboard::F2) mousePos[1] = sf::Vector2f(sf::Mouse::getPosition(window));
				if (event.key.code == sf::Keyboard::F3) mousePos[2] = sf::Vector2f(sf::Mouse::getPosition(window));
				if (event.key.code == sf::Keyboard::F4) mousePos[3] = sf::Vector2f(sf::Mouse::getPosition(window));


			}
			break;

			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		int squareSpeed = 3;
		Vector2f Alpha;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			shPos.x -= squareSpeed;
			shDir.x = -1;
			shDir.y = 0;




		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			shPos.x += squareSpeed;
			shDir.x = 1;
			shDir.y = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			shPos.y -= squareSpeed;
			shDir.x = 0;
			shDir.y = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			shPos.y += squareSpeed;
			shDir.x = 0;
			shDir.y = 1;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (shDir.x == 0 && shDir.y == 0) shDir.y = 1;

			RectangleShape * pr = new RectangleShape(Vector2f(8, 8));
			pr->setFillColor(Color(0xBFE1FF));
			pr->setOrigin(4, 4);
			pr->setPosition(sh->getPosition());
			Particle * p = new Particle(pr);

			float shDirLen = sqrt(shDir.x*shDir.x + shDir.y*shDir.y);
			p->dir.x = shDir.x / shDirLen;
			p->dir.y = shDir.y / shDirLen;
			p->bhv = [](Particle * part) {
				Vector2f ppos = part->spr->getPosition();
				ppos.x += part->dir.x * 6;
				ppos.y += part->dir.y * 6;
				part->spr->setPosition(ppos);



			};
			vec.push_back(p);
		}
		sh->setPosition(shPos);


		myFpsCounter.setPosition(8, 8);
		myFpsCounter.setFillColor(sf::Color::Magenta);
		myFpsCounter.setFont(*font);

		if (every == 0) {
			myFpsCounter.setString(std::string("FPS:") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}
		every--;

		window.clear(sf::Color(0xB38841));//nettoie la frame



		if (sh->getGlobalBounds().intersects(sprite2.getGlobalBounds()))
		{
			std::cout << "Collision !" << std::endl;




		}

		/*else
		{
			sprite2.move(sf::Vector2f(0, -0.1));
		}*/

		drawMovingSquare(window);
		window.draw(sprite);
		window.draw(sprite2);

		//drawCurve(window, clock.getElapsedTime().asSeconds() );
		//drawCatmull(window, clock.getElapsedTime().asSeconds());

		//window.draw(shape);//on demande le dessin d' une forme
		window.draw(myFpsCounter);

		for (int k = 0; k < (int)vec.size(); k++) {
			Particle * p = vec[vec.size() - k - 1];
			p->update();
			if (p->killed) {
				vec.erase(vec.begin() + k);
			}
			else {
				p->draw(window);
			}
		}

		window.display();

		fps[step % 4] = 1.0f / (frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;

		step++;
	}

	return 0;
}
