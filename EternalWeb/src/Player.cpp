#include "Player.h"


void Player::initVariables()
{
	this->dx = 0;
	this->dy = 0;
	this->sprite.setPosition(0.f, 300.f);
	this->death = false;
}

void Player::initTexture()
{
	this->texture.loadFromFile("img/Player/player.png");
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.15,0.15);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player() = default;

Vector2f Player::getPos() const
{
	return this->sprite.getPosition();
}

Vector2f Player::getSize() const
{
	return this->sprite.getOrigin();
}

void Player::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setDeath(bool death)
{
	this->death = death;
}

void Player::setAcceleration(float dx)
{
	this->dx = dx;
	if (this->dx > 0.15)
		this->dx = 0.15;
}

void Player::setForseJump(float dy)
{
	this->dy = dy;
}

void Player::setPlatform(String type_platform)
{
	this->type_platform = type_platform;
}

void Player::render(RenderTarget* target) {
	target->draw(this->sprite);
}
