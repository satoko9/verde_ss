#include <iostream>
#include <stdio.h>

using namespace std;

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

    int n = 5;

    for(int i=1; i<=n; i++){
        for(int x=n; x>=i; x--){
            printf(" ");
        }
        for(int y=1; y<=2*i-1; y++){
            printf("A");
        }
        printf("\n");
    }

    int today = 0;
    int &tomorrow = today;

    today = 919;
    cout <<"today is..." << today << endl;
    cout << tomorrow << endl;

    tomorrow = 920;
    cout << "tomorrow is..." << today << endl;
    cout << tomorrow << endl;

    char name[20];
    std::cout << "Please write your name.\n";
    std::cin >> name;
    std::cout << "Hello," << name << ". Welcome to my computer!\n";

    int old;
    std::cout << "How old are you?\n";
    std::cin >> old;

    if(old >= 20){
        std::cout << "you are adult.\n";
    }else{
        std::cout << old << "? You are too young.\n";
    }



    return 0;
}
