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
	bool sprawdzPole(int x, int y);
	sf::RectangleShape ship;

private:
	int offsideX;
	int offsideY;
	int shipNumber;
	static int dragging;
	static bool horizontalDirectionStatic;
	bool horizontalDirection;
	int size;
	int x, y;
	int old_x, old_y;
	bool goodPos;
	bool positionChange;
};

