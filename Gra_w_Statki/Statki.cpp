#pragma once
#include "Statki.h"
#include "Plansze.h"
#include "Game.h"
#include <iostream>
Statki::Statki(int _size, int num) : shipNumber(num), size(_size)
{
	if (this->horizontalDirection) { 
		this->ship.setSize(sf::Vector2f(_size * 47.5, 47.5));
	}
	else {
		this->ship.setSize(sf::Vector2f(47.5, _size * 47.5));
	}
	this->horizontalDirection = !this->horizontalDirection;
	this->ship.setFillColor(sf::Color::Cyan);
	this->ship.setPosition(104.0, 24.0);
	this->x = 0;
	this->y = 0;
}

Statki::~Statki(){}

int Statki::dragging = -1;

void Statki::updateShip(sf::Vector2i &mousePos, sf::Vector2i &mousePosReference)
{
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
							this->x++;
						}
					}
					else {
						if (this->ship.getGlobalBounds().left > 104) {
							mousePosReference.x -= 47.5;
							this->ship.move(-47.5, 0);
							this->x--;
						}
					}
				}
				else {
					if (y >= 35) {
						if (this->ship.getGlobalBounds().top < 451.5) {
							mousePosReference.y += 47.5;
							this->ship.move(0, 47.5);
							this->y++;
						}

					}
					else {
						if (this->ship.getGlobalBounds().top > 24) {
							mousePosReference.y -= 47.5;
							this->ship.move(0, -47.5);
							this->y--;
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
	goodPosition();
	if(this->goodPos == false) this->ship.setFillColor(sf::Color::Red);
	else {
		if (this->horizontalDirection) {
			for (int i = 0; i < this->size; i++) {
				Game::board1[this->x + 1][this->y] = this->size;
			}
		}
		else {
			std::cout << this->size;
			for (int i = 0; i < this->size; i++) {
				Game::board1[this->x][this->y + i] = this->size;
			}
		}
	}
	//std::cout << this->x << "  " << this->y << std::endl << "board1: " << Game::board1[6][0] << std::endl;
}

void Statki::goodPosition()
{
	if (this->horizontalDirection) {
		for (int i = 0; i < this->size; i++) {
			if (Plansze::sprawdz_pole(Game::board1, x + i, y) == 0) {
				this->goodPos = false;
				return;
			}
		}
		this->goodPos = true;
	}
	else {
		for (int i = 0; i < this->size; i++) {
			if (Plansze::sprawdz_pole(Game::board1, x, y + i) == 0) {
				this->goodPos = false;
				return;
			}
		}
		this->goodPos = true;
	}
}

void Statki::renderShip()
{
	
}

bool Statki::horizontalDirection = true;