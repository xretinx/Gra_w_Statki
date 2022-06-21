#include "Plansze.h"

Plansze::Plansze()
{
    t1.loadFromFile("assets/X.png");
    t2.loadFromFile("assets/O.png");
    t3.loadFromFile("assets/W.png");
    t4.loadFromFile("assets/X-.png");
}

Plansze::~Plansze()
{

}

//-------------------------------------------------------
//Init
//-------------------------------------------------------
void Plansze::set(int plansza1[10][10], int plansza2[10][10])
{
    board1 = plansza1;
    board2 = plansza2;
    this->initBoard1();
    this->initBoard2();
}

void Plansze::initBoard1()
{

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board1[i][j] = 0;
        }
    }
}

void Plansze::initBoard2()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board2[i][j] = 0;
        }
    }

    int typ_statku = 4;
    int statek[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    int statek_nr = 0;

    //int x = time(nullptr);
    //std::mt19937 generator(x);
    //std::uniform_int_distribution<int> kierunek(0, 3);
    //std::uniform_int_distribution<int> pozycja(0, 9);

    /*int kierunek = rand() % 4;
    int pozycja = rand() % 10;*/


    while (typ_statku > 0)
    {
        // = kierunek(generator)
        int x = rand() % 10;
        int y = rand() % 10;
        int xu = x;
        int yu = y;

        int kier = rand() % 4;
        bool ustaw_statek = 1;

        if (kier == 0 && x - typ_statku > -1)
        {
            for (int i = 0; i < typ_statku; i++)
            {
                if (sprawdz_pole(board2, x, y) == 1)
                {
                    x--;
                }
                else
                {
                    ustaw_statek = 0;
                }
            }
        }
        else if (kier == 1 && x + typ_statku < 9)
        {
            for (int i = 0; i < typ_statku; i++)
            {
                if (sprawdz_pole(board2, x, y) == 1)
                {
                    x++;
                }
                else
                {
                    ustaw_statek = 0;
                }
            }
        }
        else if (kier == 2 && y - typ_statku > 0)
        {
            for (int i = 0; i < typ_statku; i++)
            {
                if (sprawdz_pole(board2, x, y) == 1)
                {
                    y--;
                }
                else
                {
                    ustaw_statek = 0;
                }
            }
        }
        else if (kier == 3 && y + typ_statku < 9)
        {
            for (int i = 0; i < typ_statku; i++)
            {
                if (sprawdz_pole(board2, x, y) == 1)
                {
                    y++;
                }
                else
                {
                    ustaw_statek = 0;
                }
            }
        }
        else
        {
            ustaw_statek = 0;
        }

        if (ustaw_statek == 1)
        {
            if (kier == 0)
            {
                for (int i = 0; i < typ_statku; i++)
                {
                    board2[xu][yu] = typ_statku;
                    obrysuj(board2, xu, yu);
                    xu--;
                }
            }
            else if (kier == 1)
            {
                for (int i = 0; i < typ_statku; i++)
                {
                    board2[xu][yu] = typ_statku;
                    obrysuj(board2, xu, yu);
                    xu++;
                }
            }
            else if (kier == 2)
            {
                for (int i = 0; i < typ_statku; i++)
                {
                    board2[xu][yu] = typ_statku;
                    obrysuj(board2, xu, yu);
                    yu--;
                }
            }
            else if (kier == 3)
            {
                for (int i = 0; i < typ_statku; i++)
                {
                    board2[xu][yu] = typ_statku;
                    obrysuj(board2, xu, yu);
                    yu++;
                }
            }
            statek_nr++;
            typ_statku = statek[statek_nr];
        }
    }
}
//-------------------------------------------------------
//Update
//-------------------------------------------------------
bool Plansze::click(sf::RenderWindow* window)
{
    int x = (sf::Mouse::getPosition(*window).x - board2Pos_x) / 47;
    int y = (sf::Mouse::getPosition(*window).y - board2Pos_y) / 47;
    if (x >= 0 && x <= 9 && y >= 0 && y <= 9 && sf::Mouse::getPosition(*window).x - board2Pos_x >=0 && sf::Mouse::getPosition(*window).y - board2Pos_y >= 0)
    {
        if (board2[x][y] == 0 || board2[x][y] == -1)
        {
            board2[x][y] = -2;
            //game.wynikdec();
            return true;
        }
        else if (board2[x][y] > 0 && board2[x][y] < 5)
        {
            board2[x][y] = -3;
            //game.wynikinc();
            return true;
        }
    }
    return false;
}
//-------------------------------------------------------
//Render
//-------------------------------------------------------
void Plansze::renderBoard1(sf::RenderWindow* window)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board1[i][j] == 0 || board1[i][j] == -1)
            {
                tiles1.setFillColor(sf::Color(0, 0, 80, 0));
                tiles1.setTexture(&t3);
            }
            else if (board1[i][j] > 0 && board1[i][j] < 5)
            {
                tiles1.setFillColor(sf::Color(120, 120, 120, 0));
                tiles1.setTexture(&t3);
            }
            else if (board1[i][j] == -2)
            {
                tiles1.setFillColor(sf::Color(255, 255, 255, 255));
                tiles1.setTexture(&t2);
            }
            else if (board1[i][j] == -3)
            {
                tiles1.setFillColor(sf::Color(255, 255, 255, 255));
                tiles1.setTexture(&t1);
            }
            else if (board2[i][j] == -4)
            {
                tiles2.setFillColor(sf::Color(255, 255, 255, 255));
                tiles2.setTexture(&t4);
            }

            tiles1.setSize(sf::Vector2f(47.5, 47.5));
            tiles1.setPosition(sf::Vector2f(board1Pos_x + i * 47.5, board1Pos_y + j * 47.5));

            window->draw(tiles1);
        }
    }
}

void Plansze::renderBoard2(sf::RenderWindow* window)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board2[i][j] == 0 || board2[i][j] == -1)
            {
                tiles2.setFillColor(sf::Color(120, 120, 120, 0));
                tiles2.setTexture(&t3);
            }
            else if (board2[i][j] > 0 && board2[i][j] < 5)
            {
                tiles2.setFillColor(sf::Color(120, 120, 120, 0));
                tiles2.setTexture(&t3);
            }
            else if (board2[i][j] == -2)
            {
                tiles2.setFillColor(sf::Color(255, 255, 255, 255));
               
                tiles2.setTexture(&t2);
            }
            else if (board2[i][j] == -3)
            {
                tiles2.setFillColor(sf::Color(255, 255, 255, 255));
                tiles2.setTexture(&t1);
            }
            else if (board2[i][j] == -4)
            {
                tiles2.setFillColor(sf::Color(255, 255, 255, 255));
                tiles2.setTexture(&t4);
            }
            tiles2.setSize(sf::Vector2f(47.5, 47.5));
            tiles2.setPosition(sf::Vector2f(board2Pos_x + i * 47.5, board2Pos_y + j * 47.5));

            window->draw(tiles2);
        }
    }
}
//-------------------------------------------------------
//Inne
//-------------------------------------------------------
int Plansze::winning()
{
    int x = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board1[i][j] > 0)
            {
                x = 1;
            }
        }
    }
    if (x == 0)
    {
        return 2;
    }
    x = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board2[i][j] > 0)
            {
                x = 1;
            }
        }
    }
    if (x == 0)
    {
        return 1;
    }

    return 0;
}

bool Plansze::sprawdz_pole(int plansza[10][10], int x, int y)
{
    if (plansza[x][y] == 0)
    {
        for (int i = x - 1; i <= x + 1; i++)
        {
            if (i < 0 || i > 9)
            {
                continue;
            }

            for (int j = y - 1; j <= y + 1; j++)
            {
                if (j < 0 || j > 9)
                {
                    continue;
                }
                if (plansza[i][j] > 0)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

void Plansze::obrysuj(int plansza[10][10], int x, int y)
{
    for (int i = x - 1; i <= x + 1; i++)
    {
        if (i < 0 || i > 9)
        {
            continue;
        }
        else
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (j < 0 || j > 9)
                {
                    continue;
                }
                if (plansza[i][j] == 0)
                {
                    plansza[i][j] = -1;
                }
            }
        }
    }
}