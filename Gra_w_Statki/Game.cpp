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
	this->window = new sf::RenderWindow(this->videoMode, "Statki", sf::Style::Titlebar | sf::Style::Close);
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

bool Game::isShipSet = true;

void Game::initBackground()
{
	//Tlo pierwsze
	this->background.setSize(sf::Vector2f(500, 500));
	this->background.setPosition(90.f, 10.f);
	//Zaldowanie tekstury tla
	if (!this->backgroundTexture.loadFromFile("assets/MAP.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla tla
	this->background.setTexture(&backgroundTexture);
	//tlo drugie
	this->background2.setSize(sf::Vector2f(500, 500));
	this->background2.setPosition(690.f, 10.f);
	//Zaldowanie tekstury tla
	if (!this->backgroundTexture2.loadFromFile("assets/MAP.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla tla
	this->background2.setTexture(&backgroundTexture2);
	//T這 trzecie
	this->background3.setSize(sf::Vector2f(1280, 720));
	this->background3.setPosition(0.f, 0.f);
	//Za豉dowanie tekstury tla
	if (!this->backgroundTexture3.loadFromFile("assets/BCK.png")) std::cout << "Error with  loading background texture\n";
	//Ustawienie tekstury dla tla
	this->background3.setTexture(&backgroundTexture3);
}

int Game::board1[10][10]{ 0 };
int Game::board2[10][10]{ 0 };

Game::Game() : shipSizes{ 1,1,1,1,2,2,2,3,3,4 }
{
	boards.set(Game::board1, Game::board2);
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
	//usunac
	//std::cout << (sf::Mouse::getPosition(*this->window).x - 704) / 47 << " " << (sf::Mouse::getPosition(*this->window).y - 24) / 47 << std::endl;

	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				if (boards.click(window) == true)
				{
					round = 2;
				}
			}
		}
	}

	if (round == 2)
	{
		bot();
		round = 1;
	}
}

bool Game::isInside(sf::Vector2i mouse, sf::FloatRect rect)
{
	return rect.contains(mouse.x, mouse.y);
}

void Game::updateMousePosition()
{
	//Aktualizuje pozycje myszy wzgl璠em okienka
	this->mousePos = sf::Mouse::getPosition(*this->window);
}
//do usuniecia
void Game::updateShipPosition()
{
	std::cout << this->isShipSet;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->isShipSet == true) {
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

void Game::bot()
{
	srand(time(0));
	int random = rand() % 100;
	for (int i = 0; i < 100; i++)
	{
		if (tiles[i] == random)
		{
			i = 0;
			random = rand() % 100;
		}
	}
	tiles[pos] = random;
	pos++;
	int x_target = random / 10;
	int y_target = random % 10;
	if (board1[x_target][y_target] == 0 || board1[x_target][y_target] == -1)
	{
		board1[x_target][y_target] = -2;
	}
	else if(board1[x_target][y_target] > 0)
	{
		board1[x_target][y_target] = -3;
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
	//rysowanie obiektow

	boards.renderBoard1(window);
	boards.renderBoard2(window);	
	this->renderShip();
	
	//pokazanie na ekran
	this->window->display();
}
