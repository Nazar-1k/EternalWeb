#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Platform
{
private:
	Texture texture;

	Sprite sprite;

	String type_platform;
	
	//private functions
	
	void initTextur(String string);
	void initeSprite();

public:
	Platform(String string);
	~Platform();

	//Functions 

	void setPosition(Vector2f pos);
	void setPosition(float x, float y);

	Vector2f getPosition();
	
};

