#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>

class Interface
{
	sf::RenderWindow *window;
	sf::Font font;

	std::string str_level;
	std::string str_points;
	std::string str_hp;
	std::string str_record;

	sf::Text txt_level;
	sf::Text txt_points;
	sf::Text txt_hp;
	sf::Text txt_record;

	sf::Texture texture;
	sf::Sprite sprite_hp;

	sf::Texture gameover_texture;
	sf::Sprite gameover;

	sf::SoundBuffer buffer_shoot;
	sf::SoundBuffer buffer_hit;
	sf::SoundBuffer buffer_dies;
	sf::SoundBuffer buffer_start;
	sf::SoundBuffer buffer_end;

	sf::Sound shoot;
	sf::Sound hit;
	sf::Sound dies;
	sf::Sound start;
	sf::Sound end;

	int hp;
	int level;
	int points;
	int record;
	bool new_record;

public:
	Interface(sf::RenderWindow *window);

	static float acceleration;

	void Start();
	void GameOver();
	void Draw();
	void AddPoints(int typ);
	void DecreaseHp();
	int GetHp();

	void PlayStart();
	void PlayEnd();
	void PlayShoot();
	void PlayHit();
	void PlayDies();
};

float Interface::acceleration;

Interface::Interface(sf::RenderWindow *window)
{
	this->window = window;

	std::ifstream file;
	file.open("data/sc.bin");
	file>>record;
	file.close();

	font.loadFromFile("data/font.ttf");

	txt_level = sf::Text (str_level,font,100);
	txt_level.setCharacterSize(25);
	txt_level.setPosition(5,650);

	txt_points = sf::Text (str_points,font,100);
	txt_points.setCharacterSize(25);
	txt_points.setPosition(5,670);

	txt_hp = sf::Text (str_hp,font,100);
	txt_hp.setCharacterSize(25);
	txt_hp.setPosition(425,650);
	str_hp = "Lives: ";
	txt_hp.setString(str_hp);

	txt_record = sf::Text (str_record,font,100);
	txt_record.setCharacterSize(25);
	txt_record.setPosition(425,670);

	if (record > 999)
		record = 999;
	if (record >= 100)
		str_record = "HI-score:";
	else
		str_record = "HI-score: ";
	str_record += std::to_string(record);
	txt_record.setString(str_record);

	texture.loadFromFile("data/hp.png");
	sprite_hp.setTexture(texture);
	sprite_hp.setPosition(508,658);

	gameover_texture.loadFromFile("data/gameover.png");
	gameover.setTexture(gameover_texture);

	level = 1;
	points = 0;
	hp = 3;
	acceleration = 1;
	new_record = 0;

	buffer_shoot.loadFromFile("data/shoot.wav");
	shoot.setBuffer(buffer_shoot);

	buffer_hit.loadFromFile("data/hit.wav");
	hit.setBuffer(buffer_hit);

	buffer_dies.loadFromFile("data/dies.wav");
	dies.setBuffer(buffer_dies);

	buffer_start.loadFromFile("data/start.wav");
	start.setBuffer(buffer_start);

	buffer_end.loadFromFile("data/end.wav");
	end.setBuffer(buffer_end);

}

void Interface::Start()
{
	sf::Texture starttx;
	starttx.loadFromFile("data/start.png");
	sf::Sprite start;
	start.setTexture(starttx);

	window->draw(start);
	window->display();

	while(true)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			break;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
			return;
		}
	}

}

void Interface::Draw()
{
	str_level = "Level: ";
	str_level += std::to_string(level);
	txt_level.setString(str_level);

	str_points = "Points: ";
	str_points += std::to_string(points);
	txt_points.setString(str_points);

	window->draw(txt_level);
	window->draw(txt_points);
	window->draw(txt_hp);
	window->draw(txt_record);
	window->draw(sprite_hp);
}

void Interface::AddPoints(int typ)
{
	if (typ == 1)
		points += 1;
	else if (typ == 2)
		points += 2;
	else if (typ == 3)
		points += 3;

	if (points >= level*10)
	{
		level++;
		acceleration += 0.25;
	}

	if (points > 999)
	{
		points = 999;
	}

	if (points > record)
	{
		new_record = 1;
		record = points;
		if(record >= 100)
			str_record = "HI-score:";
		else
			str_record = "HI-score: ";
		str_record += std::to_string(record);
		txt_record.setString(str_record);
	}
}

void Interface::DecreaseHp()
{
	hp--;

	if (hp >= 0)
		sprite_hp.setTextureRect(sf::IntRect(0,0,28*hp,20));

}

void Interface::GameOver()
{
	window->draw(gameover);
	window->display();

	if (new_record == 1)
	{
		std::ofstream file;
		file.open("data/sc.bin");
		file<<record;
		file.close();
	}

	while(true)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			break;
	}

	sprite_hp.setTextureRect(sf::IntRect(0,0,86,20));
	hp = 3;
	level = 1;
	points = 0;
	acceleration = 1;

	PlayStart();

}

int Interface::GetHp()
{
	return hp;
}

void Interface::PlayStart()
{
	start.play();
}

void Interface::PlayEnd()
{
	end.play();
}

void Interface::PlayShoot()
{
	shoot.play();
}

void Interface::PlayHit()
{
	hit.play();
}

void Interface::PlayDies()
{
	dies.play();
}
