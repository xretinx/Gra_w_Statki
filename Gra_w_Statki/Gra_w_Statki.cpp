// Gra_w_Statki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
#include"Game.h"
int main()
{
    Game game;

    while (game.running()) {
        
        game.update();

        game.render();
    }
}
