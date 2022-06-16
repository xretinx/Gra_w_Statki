#include "Game.h"
#include <iostream>
void Game::initializerVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "Statki", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

void Game::initShip()
{
	if (shipNumber < 9) {
		this->shipNumber++;
		Statki ship(shipSizes[shipNumber], shipNumber);
		ships.push_back(ship);
	}
	else {

	}
	
}

void Game::initBackground()
{
	//T³o pierwsze
	this->background.setSize(sf::Vector2f(500, 500));
	this->background.setPosition(90.f, 10.f);
	//Za³adowanie tekstury t³a
	if (!this->backgroundTexture.loadFromFile("assets/MAP.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla t³a
	this->background.setTexture(&backgroundTexture);
	//T³o drugie
	this->background2.setSize(sf::Vector2f(500, 500));
	this->background2.setPosition(690.f, 10.f);
	//Za³adowanie tekstury t³a
	if (!this->backgroundTexture2.loadFromFile("assets/MAP.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla t³a
	this->background2.setTexture(&backgroundTexture2);
	//T³o trzecie
	this->background3.setSize(sf::Vector2f(1280, 720));
	this->background3.setPosition(0.f, 0.f);
	//Za³adowanie tekstury t³a
	if (!this->backgroundTexture3.loadFromFile("assets/BCK.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla t³a
	this->background3.setTexture(&backgroundTexture3);
}

Game::Game() : shipSizes{ 1,1,1,1,2,2,2,3,3,4 }
{
	this->initializerVariables();
	this->initWindow();
	this->initShip();
	this->initBackground();
	this->isEnterPressed = false;
}

Game::~Game()
{
	delete this->window;
}

bool Game::running()
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}
	}
}

bool Game::isInside(sf::Vector2i mouse, sf::FloatRect rect)
{
	return rect.contains(mouse.x, mouse.y);
}

void Game::updateMousePosition()
{
	//Aktualizuje pozycje myszy wzglêdem okienka
	this->mousePos = sf::Mouse::getPosition(*this->window);
}
//do usuniecia
void Game::updateShipPosition()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (this->isEnterPressed == false) {
			this->initShip();
			this->isEnterPressed = !this->isEnterPressed;
		}
	}
	else{
		for (auto& obj : ships) {
			obj.updateShip(this->mousePos, this->mousePosReference);
		}
		this->isEnterPressed = false;
	}
	
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePosition();
	this->updateShipPosition();
}

void Game::renderShip()
{
	for (auto& obj : ships) {
		this->window->draw(obj.ship);
	}

}

void Game::renderBackground()
{
	this->window->draw(this->background3);
	this->window->draw(this->background);
	this->window->draw(this->background2);
	
}

void Game::render()
{
	//czyszczenie okna
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderBackground();
	//rysowanie obiektów
	this->renderShip();
	
	//pokazanie na ekran
	this->window->display();
}
