#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	Sprite sprite;
	Texture texture;
	float dx;
	float dy;
	String type_platform;
	bool death;
	bool onPlatform;

	bool bLeft;
	bool bRight;
	///private functions
	void initSprite();

	void initVariables();

	void initTexture();
	//звук

public:
	Player();
	~Player();

	Vector2f getPos() const;
	Vector2f getSize() const;

	void setPosition(Vector2f pos);
	void setPosition(float x, float y);

	void setDeath(bool death);

	void setAcceleration(float dx);
	void setForseJump(float dy);


	void setPlatform(String type_platform);
	void render(RenderTarget* target);
};
