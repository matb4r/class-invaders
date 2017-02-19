#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Ammunition
{
	struct bullet
	{
		sf::Sprite sprite;
		bool active;
	};

	bullet p[5];
	sf::Texture texture;
	Ship* Ship_ptr;

public:
	Ammunition(Ship* s);

	void Shoot();
	void Draw(sf::RenderWindow &window, float dt);
	float GetPosX(int i);
	float GetPosY(int i);
	bool GetActive(int i);
	void ToggleActive(int i);

};


Ammunition::Ammunition(Ship* s)
{
	Ship_ptr = s;

	texture.loadFromFile("data/shoot.png");

	p[0].sprite.setTexture(texture);
	p[0].active = 0;

	p[4] = p[3] = p[2] = p[1] = p[0];

}

void Ammunition::Shoot()
{
	for (int i = 0; i < 5; i++)
	{
		if (p[i].active == 0)
		{
			p[i].active = 1;
			p[i].sprite.setPosition(Ship_ptr->GetPosX() + 22, Ship_ptr->GetPosY());
			break;
		}
	}
}

void Ammunition::Draw(sf::RenderWindow &window, float dt)
{
	for (int i = 0; i < 5; i++)
	{
		if (p[i].sprite.getPosition().y < 0)
		{
			p[i].active = 0;
		}

		if(p[i].active == 1)
		{
			p[i].sprite.move(0, -900 * dt);
			window.draw(p[i].sprite);
		}

	}

}

float Ammunition::GetPosX(int i)
{
	return p[i].sprite.getPosition().x;
}

float Ammunition::GetPosY(int i)
{
	return p[i].sprite.getPosition().y;
}

bool Ammunition::GetActive(int i)
{
	return p[i].active;
}

void Ammunition::ToggleActive(int i)
{
	p[i].active = !p[i].active;
}

// w Amunicji nie mog� stosowa� metody, �e do pozycji sprita
// przypisuj� Vector2f polozenia, poniewaz:
// mam piec roznych bulletow, dla kazdego musialbym inicjalizowac osobny vector
