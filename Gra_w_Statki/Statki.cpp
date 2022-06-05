#include "Statki.h"
Statki::Statki(int size)
{
	if (this->horizontalDirection) { 
		this->ship.setSize(sf::Vector2f(size * 47.5, 47.5));
	}
	else {
		this->ship.setSize(sf::Vector2f(47.5, size * 47.5));
	}
	!this->horizontalDirection;
	this->ship.setFillColor(sf::Color::Cyan);
	this->ship.setPosition(104.0, 24.0);
}

Statki::~Statki(){}

void Statki::updateShip(sf::Vector2i &mousePos, sf::Vector2i &mousePosReference, bool &dragging)
{
	if (this->ship.getGlobalBounds().contains(mousePos.x, mousePos.y) || dragging) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			float x = mousePos.x - mousePosReference.x;
			float y = mousePos.y - mousePosReference.y;
			dragging = true;
			if (x >= 35 || x <= -35 || y >= 35 || y <= -35) {
				if (x >= 35 || x <= -35) {
					if (x >= 35) {
						mousePosReference.x += 47.5;
						this->ship.move(47.5, 0);
					} else {
						mousePosReference.x -= 47.5;
						this->ship.move(-47.5, 0);
					}
				}
				else {
					if (y >= 35) {
						mousePosReference.y += 47.5;
						this->ship.move(0, 47.5);
					} else {
						mousePosReference.y -= 47.5;
						this->ship.move(0, -47.5);
					}
				}
			}

		}
		else {
			mousePosReference = mousePos;
			dragging = false;
		}
	}
}

void Statki::renderShip()
{
	
}

bool Statki::horizontalDirection = true;