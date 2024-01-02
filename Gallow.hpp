#pragma once

#include<SFML/Graphics.hpp>

#define MAIN_TEXTURE_FILE "main_texture.png"

class Gallow
{
public:
	Gallow()
	{
		texture.loadFromFile(MAIN_TEXTURE_FILE);
		sprite.setTexture(texture);
		sprite.setTextureRect({0,0, 124, 81});
		sprite.setPosition(0,0);
	}

	void Update()
	{
		if (!isUpdateing || IsEnd())
			return;
		if (updateClock.getElapsedTime().asSeconds() >= 0.5)
		{
			updateClock.restart();
			currendpiCture++;
		}
		if (currendpiCture >= MaxCaprures)
		{
			isUpdateing = false;
			currendpiCture = 0;
			currendLine++;
			if (currendLine > MaxLines)
				currendLine = MaxLines;
		}
		sprite.setTextureRect({ 125 * (int)currendpiCture,82 * (int)currendLine, 124, 81 });
	}

	void NextLine()
	{
		if (isUpdateing || IsEnd())
			return;
		isUpdateing = true;
		updateClock.restart();
	}

	bool IsEnd() const
	{
		return currendLine >= MaxLines && currendpiCture == 0;
	}

	bool IsUpdateing()
	{
		return isUpdateing;
	}

	void Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
	}

private:
	sf::Texture texture;

	sf::Sprite sprite;

	unsigned currendLine = 0;
	unsigned currendpiCture = 0;
	bool isUpdateing = false;
	sf::Clock updateClock;


	static const constexpr int MaxLines = 8;
	static const constexpr int MaxCaprures = 3;

};