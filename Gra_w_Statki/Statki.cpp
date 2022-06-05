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
			if (x >= 47.5 || x <= -47.5 || y >= 47.5 || y <= -47.5) {
				if (x >= 47.5 || x <= -47.5) {
					if (x >= 47.5) {
						mousePosReference.x = mousePos.x - (x-47.5);
						this->ship.move(47.5, 0);
					} else {
						mousePosReference.x = mousePos.x + (47.5 + x);
						this->ship.move(-47.5, 0);
					}
				}
				else {
					if (y >= 47.5) {
						mousePosReference.y = mousePos.y - (y - 47.5);
						this->ship.move(0, 47.5);
					} else {
						mousePosReference.y = mousePos.y + (47.5 + y);
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