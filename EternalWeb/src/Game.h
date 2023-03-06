#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Platform.h"

using namespace sf;
using namespace std;

struct point
{
	float x;
	float y;
};

class Game
{
private:
	
	//Variables
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	//Vector position
	Vector2i mousePosWindow;

	//clock
	Clock clock;

	//Fonts
	Font font;

	//Game object

	//Enemy
	Texture t0;
	Sprite enemy;
	bool b_enemy;
	point enemy_p;

	//Score
	Texture t_1;
	Sprite fly_score;
	point score_p;

	bool b_score_fly;
	int score;
	Text scoreText;
	
	//Platform

	Texture t1;
	Sprite simple_p;

	Texture t2;
	Sprite crash_p;

	Texture t3;
	Sprite half_crash_p;

	Texture t4;
	Sprite move_p;

	Texture t5;
	Sprite trampoline_p;

	Player *player;

	Texture bg_texture;
	Sprite bg;

	point plat_simple[10];
	point plat_crash[10];
	point plat_half_crash[10];
	point plat_move[10];
	point plat_trampoline[10];

	int h;

	float x, y;
	
	bool b_crash;
	bool b_half_crash;

	//Restart

	Texture t6;
	Sprite restart_s;

	Texture t7;
	Sprite menuR_s;

	Texture t8;
	Sprite gameOver_s;

	int RestartNum;
	bool b_restart;

	//Menu
	bool b_menu;

	Texture t9;
	Sprite play_s;

	Texture t10;
	Sprite exit_s;

	Texture t11;
	Sprite record_s;

	Texture t12;
	Sprite name_game_s;

	Texture t13;
	Sprite platform_menu;

	Texture t14;
	Sprite player_menu;

	int dy;
	int ym;
	//Record
	Text best_record;

	Texture t15;
	Sprite bestscore;

	bool b_record;

	//private functions
	void initializeVariables();
	void initWindow();
	void initeRecord();
	void initEnemys();
	void initeRestart();
	void initeMenu();
	void initeBg();
	void initePlayers();
	void initePlatform();
	void initeScore();
	void generatePlatform();


public:
	//Constructor
	Game();
	//Destructor
	~Game();

	//Accsessors
	const bool runing() const;

	//Functions

	void teleport(float in_x, float& out_x);

	void polleEvents();
	void ubdateMousePosition();
	void update();
	void render();
};
