#include "Game.h"

void Game::initializerVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Statki", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initializerVariables();
	this->initWindow();
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

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->window->display();
}
