#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"

class Background
{
	sf::Texture texture1, texture2, texture3, texture4;
	sf::Sprite sprite1, sprite2, sprite3, sprite4;
	sf::Sprite sprite1x, sprite2x, sprite3x, sprite4x;

	float p1, p2, p3, p4; // odpowiada za pozycje tla
	float q1, q2, q3, q4; // tez


public:
	Background();
	void Draw(sf::RenderWindow &window, float dt);
	void Scroll(float dt);

};


Background::Background()
{
	texture1.loadFromFile("data/bg1.png");
	sprite1.setTexture(texture1);
	sprite1x = sprite1;

	texture2.loadFromFile("data/bg2.png");
	sprite2.setTexture(texture2);
	sprite2x = sprite2;

	texture3.loadFromFile("data/bg3.png");
	sprite3.setTexture(texture3);
	sprite3x = sprite3;

	texture4.loadFromFile("data/bg4.png");
	sprite4.setTexture(texture4);
	sprite4x = sprite4;

	p1 = p2 = p3 = p4 = 0;
	q1 = q2 = q3 = q4 = -1067;

}

void Background::Draw(sf::RenderWindow &window, float dt)
{
	Scroll(dt);

	window.draw(sprite4);
	window.draw(sprite4x);
	window.draw(sprite3);
	window.draw(sprite3x);
	window.draw(sprite2);
	window.draw(sprite2x);
	window.draw(sprite1);
	window.draw(sprite1x);
}

void Background::Scroll(float dt)
{

	p1 += 400 * dt * Interface::acceleration;
	if(p1 >= 1067)
		p1 = 0;

	q1 += 400 * dt * Interface::acceleration;
	if(q1 >= 0)
		q1 = -1067;

	sprite1.setPosition(0,p1);
	sprite1x.setPosition(0,q1);



	p2 += 250 * dt * Interface::acceleration;
	if(p2 >= 1067)
		p2 = 0;

	q2 += 250 * dt * Interface::acceleration;
	if(q2 >= 0)
		q2 = -1067;

	sprite2.setPosition(0,p2);
	sprite2x.setPosition(0,q2);



	p3 += 150 * dt * Interface::acceleration;
	if(p3 >= 1067)
		p3 = 0;

	q3 += 150 * dt * Interface::acceleration;
	if(q3 >= 0)
		q3 = -1067;

	sprite3.setPosition(0,p3);
	sprite3x.setPosition(0,q3);



	p4 += 100 * dt * Interface::acceleration;
	if(p4 >= 1067)
		p4 = 0;

	q4 += 100 * dt * Interface::acceleration;
	if(q4 >= 0)
		q4 = -1067;

	sprite4.setPosition(0,p4);
	sprite4x.setPosition(0,q4);

}
