#pragma once
#include "Statki.h"
#include "Plansze.h"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <vector>
class Game
{
private:
	//Obiekt window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	//Obiekt event
	sf::Event ev;

	//Pozycja myszy
	sf::Vector2i mousePos;
	sf::Vector2i mousePosReference;

	//Przycisk enter
	bool isEnterPressed;

	//Obiekty Gry
	int shipSizes[10]; 
	int shipNumber=-1;
	std::vector <Statki> ships;
	int board1[10][10]{0};
	int board2[10][10]{0};
	Plansze boards;

	//T³a
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::RectangleShape background2;
	sf::Texture backgroundTexture2;
	sf::RectangleShape background3;
	sf::Texture backgroundTexture3;

	//Czy przesuwamy obiekt

	//Funkcje prywatne, wywo³ywane raz na pocz¹tku gry
	void initializerVariables();
	void initWindow();
	void initShip();
	void initBackground();

public:
	//Konstruktory
	Game();
	~Game();

	//Akcesoria
	bool running();

	//Funkcje
	void pollEvents();
	bool isInside(sf::Vector2i mouse, sf::FloatRect rect);
	void updateMousePosition();
	void updateShipPosition();

	void update();
	
	void renderShip();
	void renderBackground();
	void render();
};

