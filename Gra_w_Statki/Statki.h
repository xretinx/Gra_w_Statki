#pragma once
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
class Statki
{
public:
	Statki(int size, int num);
	~Statki();
	void updateShip(sf::Vector2i &mousePos, sf::Vector2i &mousePosReference);
	void renderShip();
	void goodPosition();
	sf::RectangleShape ship;

private:
	int shipNumber;
	static int dragging;
	static bool horizontalDirection;
	int size;
	int x, y;
	bool goodPos;
};

