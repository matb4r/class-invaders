#pragma once
#include <SFML/Graphics.hpp>
#include "Time.h"

class Object : public Time
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;

public:
	void SetSprite(std::string sciezka);
	virtual void Draw(sf::RenderWindow &window);

	float GetPosX();
	float GetPosY();

};

void Object::SetSprite(std::string sciezka)
{
	texture.loadFromFile(sciezka);
	sprite.setTexture(texture);
}

void Object::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position.x, position.y);
	window.draw(sprite);
}

float Object::GetPosX()
{
	return position.x;
}

float Object::GetPosY()
{
	return position.y;
}
