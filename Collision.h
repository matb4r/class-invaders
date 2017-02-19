#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Ammunition.h"
#include "Opponents.h"
#include "Interface.h"

void Collision(Ship* ship, Ammunition* ammunition, Opponents* opponents, Interface* interface, sf::RenderWindow* window);


void Collision(Ship* ship, Ammunition* ammunition, Opponents* opponents, Interface* interface, sf::RenderWindow* window)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (ammunition->GetActive(i) == 1 &&
				opponents->aliens[j].GetAlive() == 1 &&
				ammunition->GetPosY(i) > opponents->aliens[j].GetPosY() &&
				ammunition->GetPosY(i) < opponents->aliens[j].GetPosY() + 30 &&
				ammunition->GetPosX(i) + 8 > opponents->aliens[j].GetPosX() &&
				ammunition->GetPosX(i) + 4 < opponents->aliens[j].GetPosX() + 46
				) // kolizja strzal <-> alien

			{
				interface->PlayHit();
				ammunition->ToggleActive(i);
				opponents->aliens[j].SetAlive(0);
				opponents->aliens[j].Dies();
				interface->AddPoints(opponents->aliens[j].GetType());


			}

			if (ship->state == 0 &&
				opponents->aliens[j].GetAlive() == 1 &&
				opponents->aliens[j].GetPosY() + 30 > ship->GetPosY() &&
				opponents->aliens[j].GetPosY() < ship->GetPosY() + 48 &&
				opponents->aliens[j].GetPosX() + 46 > ship->GetPosX() + 8 &&
				opponents->aliens[j].GetPosX() < ship->GetPosX() + 48
				) // kolizja ship <-> alien

			{

				interface->PlayDies();
				interface->DecreaseHp();
				ship->clk.restart();
				ship->time = 0;

				if (interface->GetHp() != -1)
				{
					ship->state = ship->immortal1;
					opponents->aliens[j].SetAlive(0);
					opponents->aliens[j].Dies();
				}

				else
				{
					interface->PlayEnd();
					opponents->aliens[j].LastDies(*window);
					interface->GameOver();

					for (int k = 0; k < 5; k++)
					{
						opponents->aliens[k].SetAlive(0);
					}

					opponents->ClkRestart();
					ship->state = ship->normal;
					ship->PositionZero();
				} // game over


			}

		}
	}
}
