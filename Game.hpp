#pragma once

#include<fstream>

#include"Helper.hpp"

#include"Gallow.hpp"
#include"Word.hpp"
#include"Statistick.hpp"

#define MAIN_MENU_FILE "main_menu.png"
#define ICON_FILE "icon.png"

namespace Helper
{
	float GetFactorVideoMode()
	{
		return sf::VideoMode::getDesktopMode().height / 200.f;
	}

	sf::VideoMode GetMinVideofMode()
{
	auto pr = sf::VideoMode::getDesktopMode();
	sf::Vector2f res = {(float)pr.width, (float)pr.height};

	float factor = pr.height / 200.f;



	return sf::VideoMode{unsigned(pr.width / factor), unsigned(pr.height / factor)};
}

	bool MouseIsClicked()
	{
		static bool wasPressed = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return !(wasPressed = true);
		else
			return wasPressed ? !(wasPressed = false) : (wasPressed = false);
	}

	sf::Vector2f GetMousePosATRealWindow(const sf::RenderWindow& window)
	{
		auto pos = sf::Mouse::getPosition(window);

		float factorX = (float)window.getSize().x / (float)Helper::GetMinVideofMode().width;
		float factorY = (float)window.getSize().y / (float)Helper::GetMinVideofMode().height;

		sf::Vector2f res = { pos.x / factorX, pos.y / factorY };

		return res;

	}

	sf::Vector2f GetCenterPosOf(const sf::Sprite& sprite)
	{
		auto pos = sprite.getPosition();

		pos.x += sprite.getTextureRect().width / 2.f;
		pos.y += sprite.getTextureRect().height / 2.f;

		return pos;
	}

}

class MainGame
{
public:
	MainGame(sf::RenderWindow& window) : window(window)
	{
		word.SetPos({0.f, 60.f});
	}

	Statistick Run(const sf::String& txt)
	{
		sf::Clock clock;
		word.SetNewWord(txt);
		while (window.isOpen() && !isBrake)
		{
			GetEvents();
			Update();
			window.clear();
			MyDraw();
			FInalizeDraw();
		}
		Statistick res;
		res.time = clock.getElapsedTime();
		res.countPop = word.GetCountPop();
		res.useAlphabet = word.GetUseAlphabet();
		res.word = word.GetWord();

		wairPres();

		return res;
	}

private:
	Gallow glw;
	Word word;
	sf::RenderWindow& window;

	bool isBrake = false;

private://Методы

	void GetEvents()
	{
		static sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		if (Helper::MouseIsClicked() && !glw.IsUpdateing())
		{
			if (!word.NextSymbolAtMousePosition(Helper::GetMousePosATRealWindow(window)))
				glw.NextLine();

		}
		
	}

	void Update()
	{
		glw.Update();
		if (glw.IsEnd() || word.IsFull())
			isBrake = true;
	}

	void MyDraw()
	{
		glw.Draw(window);
		word.Draw(window);
	}

	void FInalizeDraw()
	{
		window.display();
	}

	void wairPres() const
	{
		sf::Event event;
		while(window.isOpen())
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
				return;
	}
};

class Menu
{
public:
	Menu(sf::RenderWindow& window) : window{ window }
	{
		texture.loadFromFile(MAIN_MENU_FILE);
		sprite.setTexture(texture);

		auto pr = window.getView().getCenter();

		sprite.setPosition(pr - sf::Vector2f{texture.getSize().x / 2.f, texture.getSize().y / 2.f});

		font.loadFromFile(FONT_FILE);
		text.setFont(font);
		text.setPosition({170 + sprite.getPosition().x, 80});
		text.setString("3");
		text.setCharacterSize(20);
	}

	int Run()
	{
		while (window.isOpen() && !isBreak)
		{
			GetEvent();
			Update();

			window.clear();

			window.draw(sprite);
			window.draw(text);


			window.display();
		}
		return coundLetters;
	}

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	static char coundLetters;
	sf::Text text;

	sf::RenderWindow& window;

	bool isBreak = false;

private:

	void Update()
	{
		if (PosMouseInStartButton() && Helper::MouseIsClicked())
			isBreak = true;
		if (PosMouseInUpButton() && Helper::MouseIsClicked())
			coundLetters++;
		if(PosMouseInDownButton() && Helper::MouseIsClicked())
			coundLetters--;
		if (coundLetters > 5)
			coundLetters = 3;
		else if (coundLetters < 3)
			coundLetters = 5;
		text.setString(std::to_string(coundLetters));
	}

	void GetEvent()
	{
		static sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	bool PosMouseInStartButton() const
	{
		const auto pos = Helper::GetMousePosATRealWindow(window);

		auto othpos = sprite.getPosition();

		othpos.x += 80;
		othpos.y += 120;

		if (othpos.x > pos.x || othpos.y > pos.y)
			return false;

		othpos.x += 90;
		othpos.y += 20;

		if (othpos.x < pos.x || othpos.y < pos.y)
			return false;
		return true;
	}

	bool PosMouseInUpButton() const
	{
		const auto pos = Helper::GetMousePosATRealWindow(window);

		auto othpos = sprite.getPosition();

		othpos.x += 205;
		othpos.y += 70;

		if (othpos.x > pos.x || othpos.y > pos.y)
			return false;

		othpos.x += 20;
		othpos.y += 20;

		if (othpos.x < pos.x || othpos.y < pos.y)
			return false;
		return true;
	}
	bool PosMouseInDownButton() const
	{
		const auto pos = Helper::GetMousePosATRealWindow(window);

		auto othpos = sprite.getPosition();

		othpos.x += 205;
		othpos.y += 90;

		if (othpos.x > pos.x || othpos.y > pos.y)
			return false;

		othpos.x += 20;
		othpos.y += 20;

		if (othpos.x < pos.x || othpos.y < pos.y)
			return false;
		return true;
	}

};
char Menu::coundLetters = 5;

class StatistickMenu
{
public:
	StatistickMenu(sf::RenderWindow& window) : window{ window }
	{
		font.loadFromFile(FONT_FILE);
		text.setFont(font);
		text.setCharacterSize(25);
	}

	void Run(const Statistick& stat)
	{
		SetText(stat);
		while (window.isOpen() && !isBreak)
		{
			GetEvent();
			window.clear();

			window.draw(text);

			window.display();
		}
	}

private:
	sf::RenderWindow& window;

	sf::Font font;
	sf::Text text;

	bool isBreak = false;

	void SetText(const Statistick& stat)
	{
		sf::String str = L"Искомое слово - " + stat.word + '\n' +
			L"Ваше время:\n" + std::to_string((int)stat.time.asSeconds() / 60) + L" минут, " +
			std::to_string((int)stat.time.asSeconds() % 60) + L" секунд\nИСпользуемый алфавит:\n" + stat.useAlphabet + L"\nКоличество попыток:\n" + std::to_string(stat.countPop);
		text.setString(str);
	}

	void GetEvent()
	{
		static sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
				isBreak = true;
	}

};

class Program
{
public:
	Program() : window{ Helper::GetMinVideofMode(),  L"Моя игра" }
	{
		std::srand(std::time(nullptr));
		sf::Image icon;
		icon.loadFromFile(ICON_FILE);
		window.setIcon(128, 128, icon.getPixelsPtr());
	}
	
	void Run()
	{
		int pr;
		while (window.isOpen())
		{
			Menu menu(window);
			pr = menu.Run();
			auto str = GetRandomStingFromFile(pr);
			MainGame game(window);
			auto stat = game.Run(str);
			StatistickMenu statMenu(window);
			statMenu.Run(stat);
		}
	}

private:
	sf::RenderWindow window;

	sf::String GetRandomStingFromFile(const int n)
	{
		std::string fileName = "words\\" + std::to_string(n) + ".txt";
		std::ifstream read(fileName);
		int count;
		read >> count;
		int nomer = rand() % (count + 1);


		for (unsigned i = 1; i < nomer; ++i)
			std::getline(read, fileName);

		sf::String res;

		for (int i = 0; i < n; ++i)
		{
			read >> count;
			res += sf::Uint32(count);
		}
		return res;
	}

};
