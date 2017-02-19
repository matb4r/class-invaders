#pragma once
#include <SFML/Graphics.hpp>

class Time
{
protected:
	sf::Clock clk;
	float tick;
	float newTick;
	float dt;

public:
	void Recalculate();
	float GetDT();

};


void Time::Recalculate()
{
	newTick = clk.getElapsedTime().asMilliseconds();
	dt = newTick > tick ? (newTick - tick) / 1000.0 : 0.0;
	tick = newTick;
}

float Time::GetDT()
{
	return dt;
}
