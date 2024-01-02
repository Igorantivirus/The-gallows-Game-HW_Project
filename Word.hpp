#pragma once

#include<SFML/Graphics.hpp>

#define FONT_FILE "consola.ttf"

class Word
{
public:

public:
	Word()
	{
		font.loadFromFile(FONT_FILE);
		text.setFont(font);
		FillAlphabet();
		
	}

	bool NextSymvol(const wchar_t symb)
	{
		if (!ClearFromALphabet(symb))
			return true;
		countPop++;
		bool res = false;
		for(size_t i = 0; i < resWord.getSize(); ++i)
			if (resWord[i] == symb && curentWord[i] != symb)
			{
				curentWord[i] = symb;
				res = true;
			}
		text.setString(curentWord + '\n' + alphabet);
		return res;
	}

	bool NextSymbolAtMousePosition(const sf::Vector2f& pos)
	{

		auto rect = text.getGlobalBounds();
		
		rect.left = text.getPosition().x;
		rect.top = text.getPosition().y + rect.height / 3.f;
		
		if (!rect.contains(pos.x, pos.y))
			return true;

		int x = (pos.x - rect.left) / (rect.width / 11);
		int y = (pos.y - rect.top) / (rect.height / 4);

		if (x < 0 || y < 0)
			return true;
		if (x == 11)
			x = 10;
		if (y == 3)
			y = 2;
		if (x > 11 || y > 3)
			return true;


		int ind = x + 12 * y + resWord.getSize() + 1;

		return NextSymvol(text.getString()[ind]);
	}

	bool IsFull() const
	{
		for (const auto& i : curentWord)
			if (i == '.')
				return false;
		return true;
	}

	void SetNewWord(const sf::String& txt)
	{
		countPop = 0;
		resWord = txt;
		useAlphabet = curentWord = "";
		for (const auto& i : txt)
			curentWord += ".";
		text.setString(curentWord + '\n' + alphabet);
	}

	void SetPos(const sf::Vector2f& pos)
	{
		text.setPosition(pos);
	}

	void Draw(sf::RenderWindow& window) const
	{
		window.draw(text);
	}

	const sf::String& GetUseAlphabet() const
	{
		return useAlphabet;
	}
	unsigned GetCountPop() const
	{
		return countPop;
	}
	const sf::String& GetWord() const
	{
		return resWord;
	}

private:

	unsigned countPop;

	sf::Font font;
	sf::Text text;

	sf::String resWord;
	sf::String curentWord;
	sf::String alphabet;

	sf::String useAlphabet;

private:
	void FillAlphabet()
	{
		alphabet = L"¿¡¬√ƒ≈®∆«»…\n ÀÃÕŒœ–—“”‘\n’÷◊ÿŸ⁄€‹›ﬁﬂ";
	}
	bool ClearFromALphabet(const wchar_t c)
	{
		for(auto& i : alphabet)
			if (i == c && i != ' ')
			{
				useAlphabet += i;
				i = ' ';
				return true;
			}
		return false;
	}

};