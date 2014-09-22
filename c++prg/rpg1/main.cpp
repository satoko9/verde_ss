#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    char name[20];
    std::cout << "あなたの名前は？";
    std::cin >> name;

    char sex;
    std::cout << "あなたは男の子(male)ですか？ 女の子(female)ですか？ mかfで答えてね。 ";
    std::cin >> sex;
    while(sex != 'm'){
    if(sex == 'f'){
        std::cout << "現在お取り扱いしておりません。\n";
        std::cout << "あなたは男の子(male)ですか？ 女の子(female)ですか？ ";
        std::cin >> sex;
        //std::cout << "\n";
    }else{
        std::cout << "入力が間違っています\n";
        std::cout << "あなたは男の子(male)ですか？ 女の子(female)ですか？ ";
        std::cin >> sex;
        //std::cout << "\n";
    }
    }

    std::cout << "ようこそ" << name << "さん。\n";

    char mode[10];
    int num = 0;
    std::cout << "モードを入力してね。<easy nomal hard> ";
    std::cin >> mode;
    if(!strcmp(mode,"easy")){
        num = 1;
        std::cout << mode << "モードですね。それではゲームスタート!\n";
    }else if(!strcmp(mode,"nomal")){
        num = 2;
        std::cout << mode << "モードですね。それではゲームスタート!\n";
    }else if(!strcmp(mode,"hard")){
        num = 3;
        std::cout << mode << "モードですね。それではゲームスタート!\n";
    }else if(!strcmp(mode,"tksm")){
        num = 4;
        std::cout << "takashimaモードで遊べるドン!\n";
        std::cout << "では、ゲームスタート!!\n";
    }

    int point = 0;
    char nomal[100];

    char easy1[] = "if";
    char easy2[] = "while";
    char easy3[] = "int";
    char easy4[] = "char";
    char easy5[] = "for";
    char easy6[] = "double";
    char easy7[] = "switch";

    char nomal1[] = "monster_energy";
    char nomal2[] = "burn";
    char nomal3[] = "red_bull";
    char nomal4[] = "rockstar";
    char nomal5[] = "regain";
    char nomal6[] = "dr_pepper";
    char nomal7[] = "mountain_dew";

    char hard1[] = "mbed" ;
    char hard2[] = "arduino";
    char hard3[] = "rx62n";
    char hard4[] = "rx62g";
    char hard5[] = "discovery";
    char hard6[] = "nucleo";
    char hard7[] =  "raspberry_pi";

    char tksm1[] = "jkit";
    char tksm2[] = "speeed";
    char tksm3[] = "dddeg";
    char tksm4[] = "poskyori";
    char tksm5[] = "moji";
    char tksm6[] = "soutput";
    char tksm7[] = "outpuut";

    switch (num){
    case 1:
        std::cout << easy1 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy1)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy2 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy2)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy3 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy3)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy4 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy4)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy5 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy5)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy6 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy6)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << easy7 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,easy7)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }
        break;
    case 2:
/*        char nomal1[] = "monster_energy";
        char nomal2[] = "burn";
        char nomal3[] = "red_bull";
        char nomal4[] = "rockstar";
        char nomal5[] = "regain";
        char nomal6[] = "dr_pepper";
        char nomal7[] = "mountain_dew";
*/
        //char nomal[100];

        std::cout << nomal1 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal1)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal2 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal2)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal3 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal3)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal4 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal4)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal5 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal5)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal6 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal6)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << nomal7 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,nomal7)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }
        break;
    case 3:
        std::cout << hard1 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard1)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard2 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard2)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard3 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard3)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard4 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard4)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard5 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard5)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard6 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard6)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << hard7 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,hard7)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }
        break;
    case 4:
        std::cout << tksm1 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm1)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm2 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm2)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm3 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm3)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm4 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm4)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm5 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm5)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm6 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm6)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }

        std::cout << tksm7 << "\n";
        std::cin >> nomal;
        if(!strcmp(nomal,tksm7)){
            std::cout << "success\n";
            point++;
        }else{
            std::cout << "You failed.\n";
        }
        break;

        break;
    }

    if(point >= 5){
            std::cout << "おめでとう\n";
            if (num != 4){
                std::cout << "パスワードは「tksm」\n";
            }
        }else{
            std::cout << "ゲームオーバー...\n";
            std::cout << "あと" << 5-point << "点で合格です\n";

        }


    return 0;
}
