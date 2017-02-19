#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
class Ammunition;
class Opponents;
class Interface;

class Ship : public Object
{
	friend void Collision(Ship* ship, Ammunition* ammunition, Opponents* opponents, Interface* interfejs, sf::RenderWindow* window);

	float time;
	int state; // gdy zostateie trafiony, 0 - normalnie, 1 - niesmiertelny, 2 - te�, potrzebne s� 3 parametry aby wy�wietla� miganie grafiki statku
	enum state { normal, immortal1, immortal2 };
	// niesmiertelny 1 - wyswietlany normalnie
	// niesmiertelny 2 - niewyswietlany

public:
	Ship();

	void PositionZero();
	void Draw(sf::RenderWindow &window);
	void MoveLeft(float dt);
	void MoveRight(float dt);

};


Ship::Ship()
{
	SetSprite("data/ship.png");
	sprite.setTextureRect(sf::IntRect(56,0,56,48));

	PositionZero();
	state = normal;
}

void Ship::Draw(sf::RenderWindow &window)
{
	if (time > 2.2)
	{
		state = normal;
	}

	sprite.setPosition(position.x, position.y);
	window.draw(sprite);

	if (state == immortal1)
	{
		if (clk.getElapsedTime().asSeconds() >= time)
		{
			sprite.setTextureRect(sf::IntRect(56,0,56,48));
			time += 0.1;
			state = immortal2;
		}

	}
	else if (state == immortal2)
	{

		if (clk.getElapsedTime().asSeconds() >= time)
		{
			sprite.setTextureRect(sf::IntRect(0,0,0,0));
			time += 0.1;
			state = immortal1;
		}
	}
	else if (state == normal)
	{
		sprite.setTextureRect(sf::IntRect(56,0,56,48));
	}

}

void Ship::MoveLeft(float dt)
{
	if (position.x > 2)
	{
		if (state == normal)
			sprite.setTextureRect(sf::IntRect(0,0,56,48));

		else if (state == immortal1)
			sprite.setTextureRect(sf::IntRect(0,0,0,0));

		else if (state == immortal2)
			sprite.setTextureRect(sf::IntRect(0,0,56,48));

		position.x += -1000 * dt;

	}

}

void Ship::MoveRight(float dt)
{
	if (position.x < 542)
	{
		if (state == normal)
			sprite.setTextureRect(sf::IntRect(112,0,56,48));

		else if (state == immortal1)
			sprite.setTextureRect(sf::IntRect(0,0,0,0));

		else if (state == immortal2)
			sprite.setTextureRect(sf::IntRect(112,0,56,48));

		position.x += 1000 * dt;
	}

}

void Ship::PositionZero()
{
	position.x = 268;
	position.y = 600;
}
