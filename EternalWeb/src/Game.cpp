#include "Game.h"
#include <iostream>
#include <fstream>



int get_best_points() {
	ifstream file;
	file.open("Best_points.txt", ios::in);
	int file_points = 0;
	file >> file_points;
	file.close();
	return file_points;
}

void update_best_points(int score) {
	fstream file;
	file.open("Best_points.txt", ios::in | ios::out);
	int file_points = 0;
	file >> file_points;
	file.seekg(SEEK_SET);
	if (file_points < score)
		file << score;
	file.close();
}

//Private function
void Game::initializeVariables()
{
	this->window = nullptr;
	this->b_restart = false;
	this->b_menu = true;

	//scale restart img
	this->restart_s.scale(0.1, 0.1);
	this->menuR_s.scale(0.1, 0.1);
	this->gameOver_s.scale(0.4, 0.4);

	//scale menu img
	this->exit_s.scale(0.12, 0.12);
	this->record_s.scale(0.1, 0.1);
	this->play_s.scale(0.15, 0.15);
	this->name_game_s.scale(0.2, 0.2);
	this->platform_menu.scale(0.2, 0.2);
	this->player_menu.scale(0.15, 0.15);
	this->player_menu.setPosition(250, 550);
	//font
	font.loadFromFile("font/arial.ttf");

	//score
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color(255, 170, 255));

	score = 0;
	this->dy = 0;

	this->b_record = false;
}

void Game::initWindow()
{
	//size window
	this->videoMode.height = 800;
	this->videoMode.width = 600;

	this->window = new RenderWindow(this->videoMode, "Eternal Web", Style::Titlebar | Style::Close);
}

void Game::initEnemys()
{
	this->t0.loadFromFile("img/Enemy/enemy.png");
	this->enemy.setTexture(this->t0);
	this->enemy.scale(0.2, 0.2);

	this->enemy_p.x =800;
	this->enemy_p.y = 800;
	this->b_enemy = true;
}

void Game::initePlayers()
{
	this->player = new Player;
	this->player->setPosition(300,0);
}

void Game::initeScore() 
{
	this->t_1.loadFromFile("img/Score/fly_score.png");
	this->fly_score.setTexture(this->t_1);
	this->fly_score.scale(0.2, 0.2);

	this->score_p.x = rand() % 500;
	this->score_p.y = rand() % 733;
	this->b_score_fly = true;
}

void Game::initeRecord()
{
	this->t15.loadFromFile("img/Menu/bestScore.png");
	this->bestscore.setTexture(this->t15);
	this->bestscore.scale(0.6, 0.6);

	this->bestscore.setPosition(50, 300);

	this->best_record.setFillColor(Color::Black);
	this->best_record.setFont(font);
	this->best_record.setCharacterSize(40);
	this->best_record.setPosition(400, 350);
}

void Game::generatePlatform()
{
	//Generate simple platform
	for (int i = 0; i < 10; i++)
	{
		this->plat_simple[i].x = rand() % 500;
		this->plat_simple[i].y = rand() % 733;
	}

	//Generate crash platform
	for (int i = 0; i < 1; i++)
	{
		this->plat_crash[i].x = rand() % 500;
		this->plat_crash[i].y = rand() % 733;
	}

	//Generate half_crash platform
	for (int i = 0; i < 1; i++)
	{
		this->plat_half_crash[i].x = rand() % 500;
		this->plat_half_crash[i].y = rand() % 733;
	}

	//Generate move platform
	for (int i = 0; i < 1; i++)
	{
		this->plat_move[i].x = rand() % 500;
		this->plat_move[i].y = rand() % 733;
	}

	//Generate tranpoline platform
	for (int i = 0; i < 1; i++)
	{
		this->plat_trampoline[i].x = rand() % 500;
		this->plat_trampoline[i].y = rand() % 733;
	}
}
void Game::initePlatform()
{
	//Start set simple platform
	this->t1.loadFromFile("img/Platform/simple_p.png");
	this->simple_p.setTexture(this->t1);
	this->simple_p.scale(0.2, 0.2);

	//Start set crash platform
	this->t2.loadFromFile("img/Platform/crash_p.png");
	this->crash_p.setTexture(this->t2);
	this->crash_p.scale(0.2, 0.2);

	this->b_crash = true;

	//Start set half_crash platform
	this->t3.loadFromFile("img/Platform/half_crash_p.png");
	this->half_crash_p.setTexture(this->t3);
	this->half_crash_p.scale(0.2, 0.2);

	this->b_half_crash = true;

	//Start set move platform
	this->t4.loadFromFile("img/Platform/move_p.png");
	this->move_p.setTexture(this->t4);
	this->move_p.scale(0.2, 0.2);

	//Start set tranpoline platform
	this->t5.loadFromFile("img/Platform/trampoline_p.png");
	this->trampoline_p.setTexture(this->t5);
	this->trampoline_p.scale(0.2, 0.2);

	//hight jump player in scrin
	this->h = 250;

	//Generate Platform
	this->generatePlatform();
}

void Game::initeBg()
{
	this->bg_texture.loadFromFile("img/Bg/Bg.png");
	this->bg.setTexture(this->bg_texture);
	this->bg.setPosition(0,0);
	this->bg.scale(0.25f, 0.25f);
}
	
void Game::initeRestart()
{
	this->t6.loadFromFile("img/Restart/restart.png");
	this->restart_s.setTexture(this->t6);
	

	this->t7.loadFromFile("img/Restart/menuR.png");
	this->menuR_s.setTexture(this->t7);
	
	this->t8.loadFromFile("img/Restart/gameOver.png");
	this->gameOver_s.setTexture(this->t8);

	this->restart_s.setPosition(350, 500);
	this->menuR_s.setPosition(150, 500);
	this->gameOver_s.setPosition(90, 100);
	
}

void Game::initeMenu()
{
	this->t9.loadFromFile("img/Menu/play.png");
	this->play_s.setTexture(this->t9);

	this->t10.loadFromFile("img/Menu/exit.png");
	this->exit_s.setTexture(this->t10);

	this->t11.loadFromFile("img/Menu/rec.png");
	this->record_s.setTexture(this->t11);

	this->t12.loadFromFile("img/Menu/name_game.png");
	this->name_game_s.setTexture(this->t12);

	this->t13.loadFromFile("img/Menu/platform_menu.png");
	this->platform_menu.setTexture(this->t13);

	this->t14.loadFromFile("img/Menu/player_menu.png");
	this->player_menu.setTexture(this->t14);
}

//Constructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initePlayers();
	this->initeBg();
	this->initePlatform();
	this->initeScore();
	this->initEnemys();
	this->initeMenu();
	this->initeRecord();
	this->initeRestart();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;
}

//Accsessors
const bool Game::runing() const
{
	return this->window->isOpen();
}

//Functions
void Game::polleEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::ubdateMousePosition() 
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
}

void Game::teleport(float in_x, float& out_x)
{
	out_x = in_x;

	if (in_x <= -100.0f)	out_x = in_x + (float)this->window->getSize().x;
	if (in_x >= (float)this->window->getSize().x)	out_x = in_x - (float)this->window->getSize().x  - 50;
}

bool collision(float object1_x, float object1_y, float object2_x, float object2_y, float radius_object1, float radius_object2)
{
	float len;
	len = sqrt((pow(object1_x - object2_x, 2)) + (pow(object1_y - object2_y, 2)));

	if (len < radius_object1 + radius_object2)
		return true;
	else
		return false;
}

void Game::update()
{
	this->polleEvents();
	this->ubdateMousePosition();


	update_best_points(this->score);
	//time
	int time = clock.getElapsedTime().asSeconds();

	//Menu
	if (this->b_menu == true)
	{
		this->ym = this->player_menu.getPosition().y;

		this->dy += 1;
		this->ym += this->dy;

		this->player_menu.setPosition(250, this->ym);

		if (this->ym > 700 - 1019 * 0.15)
			this->dy = -25;
	}
	
	
	//menu
	if (this->b_menu == true)
	{
		RestartNum = 0;
		this->record_s.setPosition(350, 500);
		this->exit_s.setPosition(150, 500);
		this->play_s.setPosition(220, 300);
		this->name_game_s.setPosition(100, 100);
		this->platform_menu.setPosition(240, 700);

		this->play_s.setColor(Color::White);
		this->record_s.setColor(Color::White);
		this->exit_s.setColor(Color::White);

		if (IntRect(220, 300, 1085 * 0.15, 1085 * 0.15).contains(Mouse::getPosition(*window)))
		{
			this->play_s.setColor(Color(186, 85, 211));
			this->RestartNum = 1;
		}

		if (IntRect(150, 500, 566 * 0.12, 448 * 0.12).contains(Mouse::getPosition(*window)))
		{
			this->exit_s.setColor(Color(186, 85, 211));
			this->RestartNum = 2;
		}

		if (IntRect(350, 500, 1075 * 0.1, 534 * 0.1).contains(Mouse::getPosition(*window)))
		{
			this->record_s.setColor(Color(186, 85, 211));
			this->RestartNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (RestartNum == 1)
			{
				this->b_menu = false;
				this->b_restart = false;
				this->player->death = false;
				this->player->dx = 0;
				this->player->dy = 0;
				this->x = 300;
				this->y = 0;
				this->score = 0;
			}

			if (RestartNum == 2)
			{
				this->window->close();
			}

			if (RestartNum == 3)
			{
				this->b_record = true;
				this->best_record.setString(to_string(get_best_points()));
			}
		}
	}
	else
	{
		//Restart
		if (this->player->death == true && b_restart == true)
		{
			this->menuR_s.setColor(Color::White);
			this->restart_s.setColor(Color::White);

			

			if (IntRect(150, 500, 1250 * 0.1, 1250 * 0.1).contains(Mouse::getPosition(*window)))
			{
				this->menuR_s.setColor(Color(186, 85, 211));
				this->RestartNum = 1;
			}

			if (IntRect(350, 500, 1250 * 0.1, 1250 * 0.1).contains(Mouse::getPosition(*window)))
			{
				this->restart_s.setColor(Color(186, 85, 211));
				this->RestartNum = 2;
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (RestartNum == 1)
				{
					this->b_restart = false;
					this->b_menu = true;
				}
				if (RestartNum == 2)
				{
					this->b_restart = false;
					this->player->death = false;
					this->player->dx = 0;
					this->player->dy = 0;
					this->x = 300;
					this->y = 0;
					this->score = 0;
					this->generatePlatform();
				}
			}
		}
		else
		{
			
			//Control player
			this->x = this->player->getPos().x;
			this->y = this->player->getPos().y;

			teleport(this->x, this->x);

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				this->player->dx += 1.5f;
				if (this->player->dx > 20)
					this->player->dx = 20;
				this->player->sprite.setTextureRect(sf::IntRect(874, 0, -874, 1019));
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				this->player->dx -= 1.5f;
				if (this->player->dx < -20)
					this->player->dx = -20;
				this->player->sprite.setTextureRect(sf::IntRect(0, 0, 874, 1019));
			}

			this->x += this->player->dx;

			this->player->dy += 0.4f;
			this->y += this->player->dy;

			this->player->setPosition(this->x, this->y);

			//Set platform
			if (this->player->death == false)
			{
				if (this->y > 850 )
				{
					this->player->death = true;
					this->b_restart = true;
				}

				//Spawn platform

				this->y = this->player->getPos().y;
				this->x = this->player->getPos().x;

				if (this->y < h)
				{
					//Simple platform
					for (int i = 0; i < 8; i++)
					{
						this->y = h;
						plat_simple[i].y = plat_simple[i].y - this->player->dy;

						// if the platform is below the screen
						if (plat_simple[i].y > 833 && this->player->death == false)
						{
							plat_simple[i].y = -50;
							plat_simple[i].x = rand() % 600;
						}
					}

					//Crash platform
					for (int i = 0; i < 1; i++)
					{
						this->y = h;
						plat_move[i].y = plat_move[i].y - this->player->dy;

						if (plat_crash[i].y > 833 && time % 3 == 0 && this->player->death == false)
						{
							plat_crash[i].y = -50;
							plat_crash[i].x = rand() % 600;
							b_crash = true;
						}
					}

					//Half_crash platform
					for (int i = 0; i < 1; i++)
					{
						this->y = h;
						plat_crash[i].y = plat_crash[i].y - this->player->dy;

						if (plat_half_crash[i].y > 833 && time % 4 == 0 && this->player->death == false)
						{
							plat_half_crash[i].y = -50;
							plat_half_crash[i].x = rand() % 600;
							b_half_crash = true;
						}
					}

					//move platform
					for (int i = 0; i < 1; i++)
					{
						this->y = h;
						plat_half_crash[i].y = plat_half_crash[i].y - this->player->dy;

						if (plat_move[i].y > 833 && time % 7 == 0 && this->player->death == false)
						{
							plat_move[i].y = -50;
							plat_move[i].x = rand() % 600;
						}
					}

					//trampoline platform
					for (int i = 0; i < 1; i++)
					{
						this->y = h;
						plat_trampoline[i].y = plat_trampoline[i].y - this->player->dy;

						if (plat_trampoline[i].y > 833 && time % 12 == 0 && this->player->death == false)
						{
							plat_trampoline[i].y = -50;
							plat_trampoline[i].x = rand() % 600;
						}
					}
					//score
					this->y = h;
					score_p.y = score_p.y - this->player->dy;
					if (score_p.y > 833 && time % 24 == 0 && this->player->death == false)
					{
						score_p.y = -50;
						score_p.x = rand() % 600;
						b_score_fly = true;
					}
					enemy_p.y = enemy_p.y - this->player->dy;
					if (enemy_p.y > 833 && time % 36 == 0 && this->player->death == false)
					{
						enemy_p.y = -50;
						enemy_p.x = rand() % 600;
						b_enemy = true;
					}

				}
				bool side = false;
				
				//move platform
				
				for (int i = 0; i < 1; i++)
				{
					if (side == false)
						plat_move[i].x++;
					else
						plat_move[i].x--;

					if (time % 3 == 0)
						side = true;
					else
						side = false;

					teleport(plat_move[i].x, plat_move[i].x);
				}



				//set simple platform
				const int  PLAYER_RIGHT_BOUNDING_BOX = 795 * 0.15;

				const int  PLAYER_LEFT_BOUNDING_BOX = 70 * 0.15;

				const int  PLAYER_BOTOM_BOUNDING_BOX = 1019 * 0.15;

				for (int i = 0; i < 8; i++)
				{
					if ((x + PLAYER_RIGHT_BOUNDING_BOX > plat_simple[i].x) && (x + PLAYER_LEFT_BOUNDING_BOX < plat_simple[i].x + this->t1.getSize().x * 0.2)
						&& (y + PLAYER_BOTOM_BOUNDING_BOX > plat_simple[i].y) && (y + PLAYER_BOTOM_BOUNDING_BOX < plat_simple[i].y + this->t1.getSize().y * 0.2)
						&& (this->player->dy > 0))
					{
						this->player->dy = -15.f;
						std::cout << "simple\n";
					}
				}

				//set crash platform
				for (int i = 0; i < 1; i++)
				{
					if ((x + PLAYER_RIGHT_BOUNDING_BOX > plat_crash[i].x) && (x + PLAYER_LEFT_BOUNDING_BOX < plat_crash[i].x + this->t2.getSize().x * 0.2)
						&& (y + PLAYER_BOTOM_BOUNDING_BOX > plat_crash[i].y) && (y + PLAYER_BOTOM_BOUNDING_BOX < plat_crash[i].y + this->t2.getSize().y * 0.2)
						&& (this->player->dy > 0))
					{
						b_crash = false;
						std::cout << "crash";
					}
				}

				//set half_crash platform
				for (int i = 0; i < 1; i++)
				{
					if ((x + PLAYER_RIGHT_BOUNDING_BOX > plat_half_crash[i].x) && (x + PLAYER_LEFT_BOUNDING_BOX < plat_half_crash[i].x + this->t3.getSize().x * 0.2)
						&& (y + PLAYER_BOTOM_BOUNDING_BOX > plat_half_crash[i].y) && (y + PLAYER_BOTOM_BOUNDING_BOX < plat_half_crash[i].y + this->t3.getSize().y * 0.2)
						&& (this->player->dy > 0))
					{
						if (b_half_crash)
						{
							this->player->dy = -15.f;
							b_half_crash = false;
							std::cout << "half_crash";
						}
					}
				}

				//set move platform
				for (int i = 0; i < 1; i++)
				{
					if ((x + PLAYER_RIGHT_BOUNDING_BOX > plat_move[i].x) && (x + PLAYER_LEFT_BOUNDING_BOX < plat_move[i].x + this->t4.getSize().x * 0.2)
						&& (y + PLAYER_BOTOM_BOUNDING_BOX > plat_move[i].y) && (y + PLAYER_BOTOM_BOUNDING_BOX < plat_move[i].y + this->t4.getSize().y * 0.2)
						&& (this->player->dy > 0))
					{
						this->player->dy = -15.f;
						std::cout << "move\n";
					}
				}
				//set trampoline platform
				for (int i = 0; i < 1; i++)
				{
					if ((x + PLAYER_RIGHT_BOUNDING_BOX > plat_trampoline[i].x) && (x + PLAYER_LEFT_BOUNDING_BOX < plat_trampoline[i].x + this->t5.getSize().x * 0.2)
						&& (y + PLAYER_BOTOM_BOUNDING_BOX > plat_trampoline[i].y) && (y + PLAYER_BOTOM_BOUNDING_BOX < plat_trampoline[i].y + this->t5.getSize().y * 0.2)
						&& (this->player->dy > 0))
					{
						this->player->dy = -30.f;
						std::cout << "trampoline";
					}
				}
			}

			//Score
			if (this->y == this->h && this->player->dy < (-1.62))
			{
				score += 1;
				scoreText.setString("Score: " + std::to_string(score));
			}

			if (collision(this->x + 874 * 0.15 , this->y + 1019 * 0.15, this->score_p.x + 272* 0.2, this->score_p.y + 261 * 0.2 , (874 * 0.15)/2, (261 * 0.2)/2) == true  && this->b_score_fly == true)
			{
				score += 500;
				scoreText.setString("Score: " + std::to_string(score));
				this->b_score_fly = false;
			}
			//fly_score move
			bool side = false;

			if (side == false)
				score_p.x++;
			else
				score_p.x--;

			if (time % 3 == 0)
				side = true;
			else
				side = false;

			teleport(score_p.x, score_p.x);

			fly_score.setPosition(score_p.x, score_p.y);

			//Enemy
			if (collision(this->x + 874 * 0.15, this->y + 1019 * 0.15, this->enemy_p.x + 821 * 0.2, this->enemy_p.y + 518 * 0.2, (874 * 0.15) / 2, (518 * 0.2) / 2) == true && this->b_enemy == true)
			{
				this->player->death = true;
				this->b_restart = true;
			}
			//enemy move

			if (side == false)
				enemy_p.x++;
			else
				enemy_p.x--;

			if (time % 3 == 0)
				side = true;
			else
				side = false;

			teleport(enemy_p.x, enemy_p.x);

			enemy.setPosition(enemy_p.x, enemy_p.y);
		}
	}
	cout << b_record;
	if (this->b_record == true)
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			this->b_record = false;
		}
	if (this->player->death == true)
	{
		score_p.y = -50;
		score_p.x = rand() % 600;
		b_score_fly = true;

		enemy_p.y = -1000;
		enemy_p.x = rand() % 600;
		b_enemy = true;
	}
}

void Game::render()
{
	this->window->setFramerateLimit(60);
	//Reanders the game objects.
	this->window->clear();
	this->window->draw(this->bg);
	if (this->b_menu == false)
	{
		//Draw game object
		this->player->setPosition(this->x, this->y);

		//Draw platform

		//Draw simple platform
		for (int i = 0; i < 8; i++)
		{
			this->simple_p.setPosition(this->plat_simple[i].x, this->plat_simple[i].y);
			this->window->draw(this->simple_p);
		}

		//Draw move platform

		for (int i = 0; i < 1; i++)
		{
			if (this->player->death == false)
			{
				this->move_p.setPosition(this->plat_move[i].x, this->plat_move[i].y);
				this->window->draw(this->move_p);

			}
		}

		//Draw crash platform
		if (this->b_crash)
			for (int i = 0; i < 1; i++)
			{
				if (this->player->death == false)
				{
					this->crash_p.setPosition(this->plat_crash[i].x, this->plat_crash[i].y);
					this->window->draw(this->crash_p);
				}
			}

		//Draw half_crash platform
		if (this->b_half_crash)
			for (int i = 0; i < 1; i++)
			{
				if (this->player->death == false)
				{
					this->half_crash_p.setPosition(this->plat_half_crash[i].x, this->plat_half_crash[i].y);
					this->window->draw(this->half_crash_p);
				}
			}

		//Draw trampoline platform
		for (int i = 0; i < 1; i++)
		{
			if (this->player->death == false)
			{
				this->trampoline_p.setPosition(this->plat_trampoline[i].x, this->plat_trampoline[i].y);
				this->window->draw(this->trampoline_p);
			}
		}

		this->fly_score.setPosition(this->score_p.x, this->score_p.y);
		if (this->b_score_fly == true)
		{
			this->window->draw(fly_score);
		}
		this->enemy.setPosition(this->enemy_p.x, this->enemy_p.y);
		
		if (this->b_enemy == true)
		{
			this->window->draw(enemy);
		}
		
		this->player->render(this->window);
		this->window->draw(scoreText);

		if (this->b_restart == true)
		{
			this->window->draw(restart_s);
			this->window->draw(menuR_s);
			this->window->draw(gameOver_s);
		}
	} 
	else
	{
		//menu sprite
		this->window->draw(this->player_menu);
		this->window->draw(this->platform_menu);

		this->window->draw(this->play_s);
		this->window->draw(this->exit_s);
		this->window->draw(this->record_s);
		this->window->draw(this->name_game_s);
		
		if (this->b_record == true)
		{
			this->window->draw(this->bestscore);
			this->window->draw(this->best_record);
		}
	}
	
	this->enemy.setPosition(this->enemy_p.x, this->enemy_p.y);

	this->window->display();
}
