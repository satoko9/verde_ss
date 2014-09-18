#include <iostream>
#include <stdio.h>

class Game{
    int tend;
    int result;
public:
//    void Empty();
    void Start();
    void Play1(int cardputa);
    void Play2(int cardputb);
    int Result(){
        return result;
    }
};

void Game::Play1(int cardputa)
{
    result -= cardputa;
}

void Game::Play2(int cardputb)
{
    result -= cardputb;
    if(result < 0){
    result = 0;
    }
}

//void Game::Empty()
//{
//    result = 0;
//}

void Game::Start()
{
    result = 13;
}

int main()
{
    Game game;

//    game.Empty();
    game.Start();
    game.Play1(6);
    game.Play2(3);
    if(game.Result() == 0){
        printf("you lose\n");
    }else{
        printf("%d card is staying. you are cleared\n",game.Result());
    }

    return 0;
}
