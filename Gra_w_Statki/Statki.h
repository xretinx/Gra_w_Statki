#pragma once
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
class Statki
{
public:
	Statki(int size);
	~Statki();
	void updateShip(sf::Vector2i &mousePos, sf::Vector2i &mousePosReference, bool &dragging);
	void renderShip();
	sf::RectangleShape ship;

private:
	
	static bool horizontalDirection;
};

