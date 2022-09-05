#pragma once
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
public:
	//Конструктори
	TextBox()
	{
	}
	TextBox(int size, sf::Color color, bool sel)
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		IsSelected = sel;
		if (sel)
		{
			textbox.setString("No name");
		}
		else
		{
			textbox.setString("");
		}
	}

	//Встановити позцію
	void setPosition(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
	}

	void setPosition(int a,int b)
	{
		textbox.setPosition(a, b);
	}

	// Seterи
	void setLimit(bool Tof)
	{
		hasLimite = Tof;
	}
	void setLimit(bool Tof, int lim)
	{
		hasLimite = Tof;
		limite = lim - 1;
	}
	void setSelected(bool sel)
	{
		IsSelected = sel;
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	//Встановити Шрифт
	void sentFont(sf::Font& font)
	{
		textbox.setFont(font);
	}

	// geter
	std::string getText()
	{
		return text.str();
	}

	//Draw намалюватти
	void drawTo(sf::RenderWindow& window)
	{
		window.draw(textbox);
	}

	void typedOn(sf::Event input)
	{
		if (IsSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (hasLimite)
				{
					if (text.str().length() <= limite)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limite && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

	void addStr(std::string str)
	{

		if (text.str() == "0")
		{
			deleteLastChar();
			text << str;
			textbox.setString(text.str());
		}
		else
		{
			text << str;
			textbox.setString(text.str());
		}
	}

	void backspase()
	{
		if (!text.str().empty())
			deleteLastChar();
	}

	void clear()
	{
		if (!text.str().empty())
		{
			text.str("");
			text << "";

			textbox.setString(text.str());
		}
	}

	bool empty()
	{
		if (text.str().empty())
			return true;
		else
			return false;
	}

private:
	sf::Text textbox;
	std::ostringstream text;
	bool IsSelected = false;
	bool hasLimite = false;
	int limite;

	//логіка введення
	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}

		}
		textbox.setString(text.str());
	}

	//Видалити останій символ
	void deleteLastChar()
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}

};