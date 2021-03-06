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

void Game::initFont()
{
	if (!font.loadFromFile("Fonts/pixelmix.ttf"))
	{
		std::cout << "Error";
	}
}

void Game::initText()
{
	for (int i = 0; i < 3; i++)
	{
		buttonsText[i].setFont(font);
		buttonsText[i].setCharacterSize(40);
		buttonsText[i].setFillColor(sf::Color(255, 255, 255, 200));
	}

	end.setFont(font);
	end.setCharacterSize(100);
	end.setPosition(sf::Vector2f((float)((int)(background3.getGlobalBounds().left + (background3.getGlobalBounds().width - end.getGlobalBounds().width) / 2)), 100.f));
	end.setFillColor(sf::Color(255, 255, 255, 255));
}

void Game::initMenu()
{
	menu.setOutlineThickness(2.f);
	menu.setSize(sf::Vector2f(450.f, 300.f));
	menu.setPosition(sf::Vector2f((background3.getGlobalBounds().width + 2 * background3.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (background3.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));
	menu.setFillColor(sf::Color(0, 0, 0, 0));
	menu.setOutlineColor(sf::Color::White);

	buttonsText[0].setString("New Game");
	buttonsText[1].setString("Quit");

	for (int i = 0; i < 3; i++)
	{
		buttons[i].setSize(sf::Vector2f(400.f, 80.f));
		buttons[i].setFillColor(sf::Color(0, 0, 0, 255));
		buttons[i].setPosition(sf::Vector2f((background3.getGlobalBounds().width + 2 * background3.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 2 * 120 + 39) / 2 + i * 120));
		buttonsText[i].setPosition(sf::Vector2f((float)((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2)), (float)((int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height / 2 - buttonsText[i].getGlobalBounds().height / 2 - 6.f))));
	}
	buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
}

void Game::initScore() 
{
	score.setFont(font);
	score.setString(std::to_string(wynik));
	score.setFillColor(sf::Color::White);
	score.setStyle(sf::Text::Bold);
	score.setCharacterSize(200);
	score.setPosition(sf::Vector2f(700.f, 500.f));
}

Game::Game() : shipSizes{ 1,1,1,1,2,2,2,3,3,4 }
{
	boards.set(Game::board1, Game::board2);
	this->initializerVariables();
	this->initWindow();
	this->initShip();
	this->initBackground();
	this->isEnterPressed = false;

	this->initText();
	this->initFont();
	this->initMenu();
	this->initScore();
}

Game::~Game()
{
	delete this->window;
}

bool Game::running()
{
	return this->window->isOpen();
}

void Game::pauseMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (prevKey != sf::Keyboard::Escape && mainMenu != 1)
		{
			temp = 0;
			buttons[0].setFillColor(sf::Color(20, 20, 20, 255));
			buttons[1].setFillColor(sf::Color(0, 0, 0, 255));
			buttonsText[0].setString("New Game");
			buttonsText[1].setString("Quit");

			menu.setSize(sf::Vector2f(450.f, 300.f));
			menu.setPosition(sf::Vector2f((background3.getGlobalBounds().width + 2 * background3.getOutlineThickness() + 2 * menu.getOutlineThickness() - menu.getGlobalBounds().width) / 2, (background3.getGlobalBounds().height - menu.getGlobalBounds().height + 20) / 2));

			for (int i = 0; i < 2; i++)
			{
				buttons[i].setPosition(sf::Vector2f((background3.getGlobalBounds().width + 2 * background3.getOutlineThickness() - buttons[i].getGlobalBounds().width) / 2, menu.getGlobalBounds().top + (menu.getGlobalBounds().height + menu.getOutlineThickness() * 2 - 2 * 120 + 39) / 2 + i * 120));
				buttonsText[i].setPosition(sf::Vector2f((float)((int)(buttons[i].getGlobalBounds().left + (buttons[i].getGlobalBounds().width - buttonsText[i].getGlobalBounds().width) / 2)), (float)((int)(buttons[i].getGlobalBounds().top + buttons[i].getGlobalBounds().height / 2 - buttonsText[i].getGlobalBounds().height / 2 - 6.f))));
			}

			if (stop == 0)
			{
				stop = 1;
			}
			else
			{
				stop = 0;
			}
		}
		prevKey = sf::Keyboard::Escape;
	}
	else
	{
		prevKey = 0;
	}
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
			if (stop == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					//Zatwierdzanie opcji
					if (buttons[0].getFillColor() == sf::Color(20, 20, 20, 255))
					{
						this->gameReset();
						last = 0;
					}
					else if (buttons[1].getFillColor() == sf::Color(20, 20, 20, 255))
					{
						window->close();
					}
					//----------------------------------------------------------
				}

				//Poruszanie sie po menu
				int key = 0;
				int help = 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					key = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					key = -1;
					help = 0;
				}

				buttons[temp].setFillColor(sf::Color(0, 0, 0, 255));
				if (temp == help * (key))
				{
					temp = abs((help - 1)) * (temp + 1);
					buttons[temp].setFillColor(sf::Color(20, 20, 20, 255));
				}
				else
				{
					temp = temp + key;
					buttons[temp].setFillColor(sf::Color(20, 20, 20, 255));
				}
				//------------------------------------------------------------
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left && stop == 0 && round != 0)
			{
				if (boards.click(window) == true)
				{
					round = 2;
				}
			}
		}
	}

	if (round == 2 && stop == 0)
	{
		bot();
		round = 1;
	}
}

bool Game::isInside(sf::Vector2i mouse, sf::FloatRect rect)
{
	return rect.contains(mouse.x, mouse.y);
}


void Game::updateScore()
{
	polaspudlowane = 0;
	polatrafione = 0;
	for (int i{}; i < 10; i++) {
		for (int j{}; j < 10; j++) {
			if (board2[i][j] == -2) {
				polaspudlowane++;
			}
			if (board2[i][j] <= -3) {
				polatrafione++;
			}
		}
	}
	wynik = (polatrafione * 1000) - (polaspudlowane * 100);
	score.setString(std::to_string(wynik));
	std::cout << polaspudlowane << "   " << polatrafione << std::endl;
	score.setPosition(sf::Vector2f((float)((int)(background3.getGlobalBounds().left + (background3.getGlobalBounds().width - score.getGlobalBounds().width) / 2)), 500.f));
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
	else if (board1[x_target][y_target] > 0)
	{
		board1[x_target][y_target] = -3;
		polatrafione++;
	}
}

void Game::updateMousePosition()
{
	//Aktualizuje pozycje myszy wzgl璠em okienka
	this->mousePos = sf::Mouse::getPosition(*this->window);
}
//do usuniecia
void Game::updateShipPosition()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->isShipSet == true) {
		if (this->isEnterPressed == false) {
			this->initShip();
			this->isEnterPressed = !this->isEnterPressed;
			shipcount++;
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
	
	this->pauseMenu();
	this->pollEvents();
	this->updateMousePosition();

	if (stop == 0)
	{
		wynik = 0;
		this->updateScore();
	}

	if (stop == 0 && round == 0)
	{
		this->updateShipPosition();
		if (shipcount > 10)
		{
			round = 1;
		}
	}

	if (polatrafione == 20)
	{
		gameReset();
		end.setString("You Won");
		mainMenu = 1;
		stop = 1;
	}
	else if (polatrafione2 == 20)
	{
		gameReset();
		end.setString("You Lost");
		mainMenu = 1;
		stop = 1;
	}
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

void Game::renderScore()
{
	this->window->draw(this->score);

}

void Game::render()
{
	//czyszczenie okna
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderBackground();

	//rysowanie obiekt闚
	if (stop == 0)
	{
		this->renderShip();
		boards.renderBoard1(window);
		boards.renderBoard2(window);
		
	}
	else if (stop == 1)
	{
		window->draw(menu);
		for (int i = 0; i < 2; i++)
		{
			window->draw(buttons[i]);
			window->draw(buttonsText[i]);
		}
	}
	this->renderScore();
	std::cout << last << std::endl;
	if (last == 1)
	{
		window->draw(end);
	}
	//pokazanie na ekran
	this->window->display();
}

void Game::gameReset()
{
	if (polatrafione == 20 || polatrafione2 == 20)
	{
		last = 1;
	}
	shipNumber = -1;
	round = 0;
	shipcount = 1;
	stop = 0;
	mainMenu = 0;
	prevKey = 0;
	boards.initBoard1();
	boards.initBoard2();
	ships.clear();
	this->initShip();

	this->initText();
}
