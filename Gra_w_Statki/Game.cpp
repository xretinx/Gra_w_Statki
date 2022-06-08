#include "Game.h"
#include <iostream>
void Game::initializerVariables()
{
	this->window = nullptr;
	this->dragging = false;
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
	Statki ship(1);
	ships.push_back(ship);
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

Game::Game()
{
	this->initializerVariables();
	this->initWindow();
	this->initShip();
	this->initBackground();
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
	//usunac
	std::cout << (sf::Mouse::getPosition(*this->window).x - 704) / 47 << " " << (sf::Mouse::getPosition(*this->window).y - 24) / 47 << std::endl;

	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			switch (ev.key.code)
			{
			case sf::Mouse::Left:
				boards.click(window);
			}
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
	ships[0].updateShip(this->mousePos, this->mousePosReference, dragging);
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePosition();
	this->updateShipPosition();
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
	this->window->draw(this->ships[0].ship);
	boards.renderBoard1(window);
	boards.renderBoard2(window);	
	
	//pokazanie na ekran
	this->window->display();
}
