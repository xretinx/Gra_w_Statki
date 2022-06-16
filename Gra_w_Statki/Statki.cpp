#include "Statki.h"
#include<iostream>
Statki::Statki(int size, int num) : shipNumber(num)
{
	if (this->horizontalDirection) { 
		this->ship.setSize(sf::Vector2f(size * 47.5 + (size-1) * 3, 47.5));
	}
	else {
		this->ship.setSize(sf::Vector2f(47.5, size * 47.5 + (size-1) * 3));
	}
	this->horizontalDirection = !this->horizontalDirection;
	this->ship.setFillColor(sf::Color::Cyan);
	this->ship.setPosition(104.0, 24.0);
}

Statki::~Statki(){}

int Statki::dragging = -1;

void Statki::updateShip(sf::Vector2i &mousePos, sf::Vector2i &mousePosReference)
{
	std::cout << this->dragging << " " << this->shipNumber << std::endl;
	if (this->dragging == this->shipNumber || (this->ship.getGlobalBounds().contains(mousePos.x, mousePos.y) && this->dragging == -1)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			float x = mousePos.x - mousePosReference.x;
			float y = mousePos.y - mousePosReference.y;
			this->dragging = this->shipNumber;
			if (x >= 35 || x <= -35 || y >= 35 || y <= -35) {
				if (x >= 35 || x <= -35) {
					if (x >= 35) {
						if (this->ship.getGlobalBounds().left < 531.5) {
							this->ship.move(47.5, 0);
							mousePosReference.x += 47.5;
						}
					}
					else {
						if (this->ship.getGlobalBounds().left > 104) {
							mousePosReference.x -= 47.5;
							this->ship.move(-47.5, 0);
						}
					}
				}
				else {
					if (y >= 35) {
						if (this->ship.getGlobalBounds().top < 451.5) {
							mousePosReference.y += 47.5;
							this->ship.move(0, 47.5);
						}

					}
					else {
						if (this->ship.getGlobalBounds().top > 24) {
							mousePosReference.y -= 47.5;
							this->ship.move(0, -47.5);
						}
					}
				}
			}
		}
		else {
			mousePosReference = mousePos;
			this->dragging = -1;
		}
	}
}

void Statki::renderShip()
{
	
}

bool Statki::horizontalDirection = true;