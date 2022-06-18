#pragma once
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <iostream>
#include <random>
#include <ctime>

class Plansze
{
public:
	//plansze
	int (*board1)[10]{};
	sf::RectangleShape tiles1;
	int board1Pos_x = 104;
	int board1Pos_y = 24;
	int (*board2)[10]{};
	sf::RectangleShape tiles2;
	int board2Pos_x = 704;
	int board2Pos_y = 24;

	//init
	Plansze();
	~Plansze();

	void set(int plansza1[10][10], int plansza2[10][10]);
	void initBoard1();
	void initBoard2();
	bool sprawdz_pole(int plansza[10][10], int x, int y);
	void obrysuj(int plansza[10][10], int x, int y);

	//update
	bool click(sf::RenderWindow* window);

	//render
	void renderBoard1(sf::RenderWindow* window);
	void renderBoard2(sf::RenderWindow* window);

	//inne
	int winning();
};

