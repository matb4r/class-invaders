#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Interface.h"

class Alien : public Object
{

	sf::Texture alien1;
	sf::Texture alien2;
	sf::Texture alien3;
	sf::Texture text_dies;
	sf::Texture text_dies2;

	bool alive; // czy zyje
	bool dies; // czy jest w trakcie umierania

	int type; // jeden z trzech

	bool graphicNum; // 0/1
	int direction; // lewo/prosto/prawo (-1/1)

	float time1; // czas zmiany grafiki
	float time2; // czas zmiany kieurnku ruchu
	float time3; // czas diescia

public:
	Alien();
	void SetSprite();
	void Reset();
	void Draw(sf::RenderWindow &window, float dt);
	void Dies();

	void SetAlive(bool x);
	bool GetAlive();
	int GetType();
	bool GetDies();

	void LastDies(sf::RenderWindow &window);

};


Alien::Alien()
{

	if(rand()%2 == 0)
		direction = -1;
	else direction = 1;

	alive = 0;
	dies = 0;
	graphicNum = 0;
	time1 = 1;
	time2 = 2;

	alien1.loadFromFile("data/alien1.png");
	alien2.loadFromFile("data/alien2.png");
	alien3.loadFromFile("data/alien3.png");
	text_dies.loadFromFile("data/dies.png");
	text_dies2.loadFromFile("data/dies2.png");
}

void Alien::Reset()
{
	alive = 1;

	int x = rand()%10;

	if(x >= 0 && x <= 4)
		type = 1;

	else if(x >= 5 && x <= 7)
		type = 2;

	else if(x >= 8 && x <= 9)
		type = 3;

	SetSprite();

	position.x = rand()%554;
	position.y = 0;
}

void Alien::SetSprite()
{
	if (type == 1)
		sprite.setTexture(alien1);

	else if (type == 2)
		sprite.setTexture(alien2);

	else if (type == 3)
		sprite.setTexture(alien3);

}

void Alien::Draw(sf::RenderWindow &window, float dt)
{
	if (alive == 1)
	{
		sprite.setPosition(position.x, position.y);
		window.draw(sprite);

		if (time1 <= clk.getElapsedTime().asSeconds())
		{
			graphicNum = !graphicNum;
			time1 += 1;
		}// zmiana grafiki co sekunde
		sprite.setTextureRect(sf::IntRect(46*graphicNum,0,46,30));


		if (time2 <= clk.getElapsedTime().asSeconds())
		{
			direction = rand()%3 - 1;

			time2 += 2;
		}// ewentualana zmiana kierunku co 2 sekundy
		position.x += 100 * dt * direction * Interface::acceleration;
		position.y += 200 * dt * Interface::acceleration; // ruch

		if (position.x <= 0 || position.x >= 554)
		{
			direction = -direction;
		}// sciany ogarniczaja poruszanie sie alienow

		if (position.y > 700)
		{
			alive = 0;
		}// jak dostana sie na sam dol to gina

	}

	if (dies == 1)
	{
		Object::Draw(window);

		if(clk.getElapsedTime().asSeconds() - time3 > 0.1)
		{
			dies = 0;
		}

	}

}

bool Alien::GetAlive()
{
	return alive;
}

void Alien::SetAlive(bool x)
{
	alive = x;
}

int Alien::GetType()
{
	return type;
}

void Alien::Dies()
{
	sprite.setTextureRect(sf::IntRect(0,0,48,30));
	sprite.setTexture(text_dies);
	dies = 1;
	time3 = clk.getElapsedTime().asSeconds();
}

bool Alien::GetDies()
{
	return dies;
}

void Alien::LastDies(sf::RenderWindow &window)
{
	sprite.setTextureRect(sf::IntRect(0,0,48,30));
	sprite.setTexture(text_dies2);

	Object::Draw(window);
}
