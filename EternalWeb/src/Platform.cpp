#include "Platform.h"

void Platform::initTextur(String string)
{
	this->texture.loadFromFile(string);
}

void Platform::initeSprite()
{
	this->sprite.setTexture(this->texture);
}

Platform::Platform(String string)
{
	this->initTextur(string);
	this->initeSprite();
}

Platform::~Platform() = default;

void Platform::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Platform::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

Vector2f Platform::getPosition()
{
	return this->sprite.getPosition();
}
