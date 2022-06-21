#pragma once
#include "Statki.h"
#include "Plansze.h"
#include "Game.h"
#include <iostream>
Statki::Statki(int _size, int num) : shipNumber(num), size(_size)
{
	this->horizontalDirectionStatic = !this->horizontalDirectionStatic;
	this->horizontalDirection = this->horizontalDirectionStatic;
	if (this->horizontalDirection) { 
		this->ship.setSize(sf::Vector2f(_size * 47.5, 47.5));
	}
	else {
		this->ship.setSize(sf::Vector2f(47.5, _size * 47.5));
	}
	this->ship.setFillColor(sf::Color::Cyan);
	this->ship.setPosition(104.0, 24.0);
	this->x = 0;
	this->y = 0;
	this->old_x = 0;
	this->old_y = 0;
	this->positionChange = false;
	this->goodPosition();
	if (this->horizontalDirection)
	{
		this->offsideX = (this->size - 1) * 47.5;
		this->offsideY = 0;
	}
	else
	{
		this->offsideX = 0;
		this->offsideY = (this->size - 1) * 47.5;
	}
	//std::cout << this->horizontalDirection;
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
				this->positionChange = true;
				if (x >= 35 || x <= -35) {
					if (x >= 35) {
						if (this->ship.getGlobalBounds().left < 531.0 - this->offsideX) {
							std::cout << this->ship.getGlobalBounds().left << "  ";
							this->ship.move(47.5, 0);
							mousePosReference.x += 47.5;
							this->x++;
						}
					}
					else {
						if (this->ship.getGlobalBounds().left > 104) {
							std::cout << this->ship.getGlobalBounds().left << "  ";
							mousePosReference.x -= 47.5;
							this->ship.move(-47.5, 0);
							this->x--;
						}
					}
				}
				else {
					if (y >= 35) {
						if (this->ship.getGlobalBounds().top < 451.0 - this->offsideY) {
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
				if (this->horizontalDirection) {
					for (int i = 0; i < this->size; i++) {
						Game::board1[this->old_x + i][this->old_y] = 0;
					}
				}
				else {
					for (int i = 0; i < this->size; i++) {
						Game::board1[this->old_x][this->old_y + i] = 0;
					}
				}
				this->goodPosition();
			}
		}
		else {
			mousePosReference = mousePos;
			this->dragging = -1;
		}
	}
	else {
		if (this->positionChange == true) {
			if (this->horizontalDirection) {
				for (int i = 0; i < this->size; i++) {
					Game::board1[this->x + i][this->y] = this->size;
					//Game::board1[this->old_x + i][this->old_y] = 0;
				}
			}
			else {
				for (int i = 0; i < this->size; i++) {
					Game::board1[this->x][this->y + i] = this->size;
					//Game::board1[this->old_x][this->old_y + i] = 0;
				}
			}
			this->old_x = this->x;
			this->old_y = this->y;
		}
		this->positionChange = false;
	}
}

void Statki::goodPosition()
{
	if (this->horizontalDirection) {
		for (int i = 0; i < this->size; i++) {
			if (this->sprawdzPole(x + i, y) == 0) {
;				this->goodPos = false;
				this->ship.setFillColor(sf::Color::Red);
				Game::isShipSet = false;
				return;
			}
		}
		this->goodPos = true;
		Game::isShipSet = true;
		this->ship.setFillColor(sf::Color::Cyan);
	}
	else {
		for (int i = 0; i < this->size; i++) {
			if (this->sprawdzPole(x, y + i) == 0) {
				this->goodPos = false;
				this->ship.setFillColor(sf::Color::Red);
				Game::isShipSet = false;
				return;
			}
		}
		this->goodPos = true;
		Game::isShipSet = true;
		this->ship.setFillColor(sf::Color::Cyan);
	}
}

bool Statki::sprawdzPole(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++) {
		if (i < 0 || i > 9) continue;
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j < 0 || j > 9) continue;
			if (Game::board1[i][j] > 0) 
			{
				return 0;
			}
		}
	}
	return 1;
}

void Statki::renderShip()
{
	
}

bool Statki::horizontalDirectionStatic = false;