#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Object.h"
#include "Ship.h"
#include "Background.h"
#include "Alien.h"
#include "Ammunition.h"
#include "Opponents.h"
#include "Time.h"
#include "Collision.h"
#include "Interface.h"

int main()
{
	srand((unsigned int)time(NULL));

	sf::RenderWindow window (sf::VideoMode(600,700), "Class Invaders");
	window.setKeyRepeatEnabled(false);

	Time time;
	Ship ship;
	Background background;
	Ammunition ammunition(&ship);
	Opponents opponents;
	Interface interface(&window);

	interface.Start();
	interface.PlayStart();
	opponents.ClkRestart();

	while(window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape))
				window.close();
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Space))
			{
				ammunition.Shoot();
				interface.PlayShoot();
			}
		}

		time.Recalculate();

		Collision(&ship, &ammunition, &opponents, &interface, &window);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship.MoveLeft(time.GetDT());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship.MoveRight(time.GetDT());

		window.clear();

		background.Draw(window, time.GetDT());
		ship.Draw(window);
		opponents.Draw(window, time.GetDT());
		ammunition.Draw(window, time.GetDT());
		interface.Draw();

		window.display();
	}

	return 0;
}
