#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
	//Конструктори
	Button() {}

	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
	{
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setFillColor(bgColor);
	}

	//Встановити Шрифт
	void sentFont(sf::Font& font)
	{
		text.setFont(font);
	}

	//колір фону
	void setBackColor(sf::Color color)
	{
		button.setFillColor(color);
	}

	//колір тексту
	void setTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	//Позиція
	void setPosition(sf::Vector2f pos)
	{
		button.setPosition(pos);

		float xPos = (pos.x + button.getGlobalBounds().width / 3.f - (text.getGlobalBounds().width / 2));
		float yPos = (pos.y + button.getGlobalBounds().height / 3.f - (text.getGlobalBounds().height / 2));
		text.setPosition({ xPos , yPos });
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window)
	{
		if (button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			return true;
		}
		else return false;
	}

private:
	sf::RectangleShape button;
	sf::Text text;
};
