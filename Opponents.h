#pragma once
#include <SFML/Graphics.hpp>
#include "Alien.h"
#include "Ammunition.h"
#include "Interface.h"
#include "Time.h"

class Opponents : public Time
{
	friend void Collision(Ship* ship, Ammunition* ammunition, Opponents* opponents, Interface* interfejs, sf::RenderWindow* window);

	std::vector<Alien> aliens;

public:
	Opponents();
	void Draw(sf::RenderWindow &window, float dt);
	void ClkRestart();
};


Opponents::Opponents()
{

	for (int i = 0; i < 5; i++)
	{
		aliens.push_back(Alien());
	}

}

void Opponents::Draw(sf::RenderWindow &window, float dt)
{

	if (1.75 * 1/Interface::acceleration <= clk.getElapsedTime().asSeconds())
	{
		for (int i = 0; i < 5; i++)
		{
			if(aliens[i].GetAlive() == 0 && aliens[i].GetDies() == 0)
			{
				aliens[i].Reset();
				clk.restart();
				break;
			}
		}

	} // respawn alienow co 1.75s

	for (int i = 0; i < 5; i++)
	{
		aliens[i].Draw(window, dt);
	}

}

void Opponents::ClkRestart()
{
	clk.restart();
}
